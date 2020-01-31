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
theta  = 100;
theta1 = Vg1(theta)/Vg; theta2 = Vg2(theta)/Vg;  
% current grid condition
Vg = [Vg1(theta);Vg2(theta)];
Ig = [Ig1(theta);Ig2(theta)]; 


Vin_new  = Vin_init; %we only truly have 3 independent voltage variables (once the duty cycles are fixed) 
dI_dV    = interp1(Vs(2:end),dI_dVs,Vin_new); %IV Curve linearization 
Iin_new  = Iin_init; 
Iin_prev = Iin_new; 
Ps = Vin_init.*Iin_init;
Vout_new(1) = Vg1(theta)*Ps(1)/sum(Ps); 
Vout_new(2) = Vg1(theta)*Ps(2)/sum(Ps); 
Vout_new(3) = Vg2(theta)*Ps(1)/sum(Ps); 
Vout_new(4) = Vg2(theta)*Ps(2)/sum(Ps); 
Ic(1) = Ig(1)*Vout_new(1)/Vin_new(1);
Ic(2) = Ig(1)*Vout_new(2)/Vin_new(2);
Ic(3) = Ig(2)*Vout_new(3)/Vin_new(1);
Ic(4) = Ig(2)*Vout_new(4)/Vin_new(2);
Ic = Ic'; 

D_new = Vout_new'./Vin_new([1 2 1 2]); 
D_orig = D_new; 

%% New Setpoint 
Vd = [299,298]'; %new voltage setpoint 
Iin_d = interp1(Vs,Is,Vd);
Pd = sum( Vd.*Iin_d ); 
Psd = Vd.*Iin_d; 
Pphid = [Pd * Vg1(theta)^2/(Vg1(theta)^2+Vg2(theta)^2);
         Pd * Vg2(theta)^2/(Vg1(theta)^2+Vg2(theta)^2)];

Igd = Pd / (Vg_orig);
Igd_truth = [Igd*theta1, Igd*theta2]';


x  = [Vin_new;Ig]; % retrieve the nominal operating point 
x_prev = x;

Kv = 0.0001; %voltage proportional gain
Ki = 0.001;  %current proportional gain 
cnt = 1; 

cvt_vid = [1;2;]; %converters to control voltage
cvt_iid = [3;4;]; %converters to control current/power

for tstep = 1:100


Psd = Vd.*Iin_d; 
Pd = sum(Psd); 
Pphid = [Pd * Vg1(theta)^2/(Vg1(theta)^2+Vg2(theta)^2);
        Pd * Vg2(theta)^2/(Vg1(theta)^2+Vg2(theta)^2)];
    
Ap = [1 0 1 0; 0 1 0 1; 1 1 0 0 ; 0 0 1 1]; 
bp = [Psd;Pphid];

cvx_begin 

variables P(4)
minimize norm(P(1) - P(2))
subject to 
    Ap*P == bp;
    P >= 0; 
cvx_end

Icd = P ./ (Vin_new([1,2,1,2]')); 
% Input Voltage Control

for ii = 1:N/2
    D_new(cvt_vid(ii)) = D_new(cvt_vid(ii))+(Vin_new(ii)- Vd(ii)) * Kv; 
end

% Input Current Control 
for ii = 1:N/2     
    D_new(cvt_iid(ii)) = D_new(cvt_iid(ii))+(Icd(cvt_iid(ii)) - Ic(cvt_iid(ii))) * Ki; 
end

Axv = [D_new(1), D_new(2);D_new(3), D_new(4)];
Axi = [diag(dI_dV) [D_new(1) D_new(3);D_new(2) D_new(4)]];
bxv = [Vg(1) ; Vg(2);];
bxi = [Iin_new(1)-Vin_new(1)*dI_dV(1); Iin_new(2)-Vin_new(2)*dI_dV(2)];

x_new_v = linsolve(Axv,bxv);

Vin_new = x_new(1:N/2); % extract useful state info 
Vin_prev = x_prev(1:N/2);
Ig_new = x_new(end - 1: end); 
Ic = D_new .* Ig_new([1 1 2 2]'); 

x_prev = x_new; 


%% Update States
Iin_new  = interp1(Vs,Is,Vin_new);
dI_dV    = interp1(Vs(2:end),dI_dVs,Vin_new); %update state
Iin_prev = interp1(Vs,Is,Vin_prev);
P_new    = Iin_new .*Vin_new; 
    
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

