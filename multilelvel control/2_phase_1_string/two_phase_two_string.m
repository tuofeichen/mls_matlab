clear; close all; 
N = 4; 
load ../VI_Curve.mat

t = linspace(0,2*pi,1000);
Vg = 250;
Vg_orig = 250; 
Vg1 = Vg*sin(t);
Vg2 = Vg*sin(t+pi/2); 

Vin_init = [300,299]';
Iin_init = interp1(Vs,Is,Vin_init); 
Ptot = sum(Vin_init.*Iin_init); 
Ig_orig = Ptot/Vg; % Per phase current

Ig1 = Ig_orig*sin(t);
Ig2 = Ig_orig*sin(t+pi/2); 

% arbitrary point in time 
theta  = 10;
theta1 = Vg1(theta)/Vg; theta2 = Vg2(theta)/Vg;  

Vin_new  = Vin_init; %we only truly have 3 independent voltage variables (once the duty cycles are fixed) 
dI_dV    = interp1(Vs(2:end),dI_dVs,Vin_new); %IV Curve linearization 
Iin_new  = Iin_init; 
Iin_prev = Iin_new; 


%% New Setpoint 
Vd = [299,298]'; %new voltage setpoint 
Iin_d = interp1(Vs,Is,Vd);
Pd = sum( Vd.*Iin_d ); 
Igd = Pd / (Vg);
Igd_truth = [Igd*theta1, Igd*theta2]';

Vg = [Vg1(theta);Vg2(theta)];
Ig = [Ig1(theta);Ig2(theta)]; 
x  = [Vin_new;Ig]; % retrieve the nominal operating point 
x_prev = x;
D_prev = [0.5 0.5 0.5 0.5]';

cnt = 1; 

cvt_vid = [1;4;6]; %converters to control voltage
cvt_iid = [2;3;5]; %converters to control current/power

for tstep = 1:100

% Iin_d = interp1(Vs,Is,Vd); % exact number 

Iin_d = Iin_new+(Vd-Vin_new).*dI_dV;

Pd = sum( Vd.*Iin_d );
Vg_meas = Vg_orig + randn; % measurement error on the grid voltage  

% Vg = [Vg1(theta+tstep),Vg2(theta+tstep)]';
Vg = [Vg1(theta),Vg2(theta)]';

Igd = Pd / (Vg_meas);
% vectorize phase voltages
Vg_meas = Vg_meas/Vg_orig*Vg;
% Ig = [Ig1(theta+tstep),Ig2(theta+tstep)]';
Ig = [Ig1(theta),Ig2(theta)]';

Igd = Ig* Igd/Ig_orig; 
    
  
Ad = [Vd(1),Vd(2),0,0; 
      0,0,Vd(1),Vd(2); 
      Igd(1),0,Igd(2),0;
      0,Igd(1),0,Igd(2)];
  
bd = [Vg_meas(1),Vg_meas(2),Iin_d(1),Iin_d(2)]';

cvx_begin quiet
variables D_new(4)

minimize norm(D_new - D_prev)
subject to 
    Ad*D_new==bd;
cvx_end
D_prev = D_new; 
if ~strcmp(cvx_status,'Solved')
    disp('CVX Error'); 
end

Ax = [D_new(1), D_new(2),0,0;D_new(3), D_new(4), 0,0;[-diag(dI_dV) [D_new(1) D_new(3);D_new(2) D_new(4)]]];
bx = [Vg(1) ; Vg(2); Iin_new(1)-Vin_new(1)*dI_dV(1); Iin_new(2)-Vin_new(2)*dI_dV(2)];

x_new = Ax\bx
Vin_new = x_new(1:N/2); % extract useful state info 
Vin_prev = x_prev(1:N/2);
Ig_new = x_new(end - 1: end); 
x_prev = x_new; 

%% Update States
Iin_new  = interp1(Vs,Is,Vin_new);
dI_dV   = interp1(Vs(2:end),dI_dVs,Vin_new); %update state
Iin_prev = interp1(Vs,Is,Vin_prev);
P_new = Iin_new .*Vin_new; 
    
% Log the duty cycle count
D_log(:,cnt) = D_new;
V_log(:,cnt) = Vin_new; 
P_log(:,cnt) = P_new;
I_log(:,cnt) = Ig_new;
Id_log(:,cnt) = Igd; 

cnt = cnt + 1; 
%Vd = Vd - 0.2;
end



figure; 
subplot(3,1,1); 
h = plot(V_log');  title('String Voltage'); my_plot_setting(h); 
subplot(3,1,2);
h = plot(P_log');  title('String Power'); my_plot_setting(h); 
subplot(3,1,3);
I_diff = [I_log(1,:) - I_log(1,1); I_log(2,:) - I_log(2,1)];
h = plot(1:length(I_log),I_log(1,:));yyaxis right;
 plot(1:length(I_log),I_log(2,:));
title('Phase Current'); my_plot_setting(h); 

% figure; 
% 
% V_log_per_conv = [V_log(1,:); V_log(3,:); V_log(1,:);V_log(2,:);V_log(2,:);V_log(3,:)];
% for ii = 1:N
%     subplot(N,1,ii);
%     h(1) = plot(D_log(ii,:));
%     yyaxis right; 
%     h(2) = plot(V_log_per_conv(ii,:).*D_log(ii,:));
%     my_plot_setting(h); 
% end
% 

