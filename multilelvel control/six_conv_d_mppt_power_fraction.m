clear; 
close all; 
N = 6; 
load VI_Curve.mat
load balanced_6_conv_sys.mat
t = linspace(0,2*pi,100);
Vg = 300;

Vg1_t = Vg*sin(t);
Vg2_t = Vg*sin(t+2*pi/3); 
Vg3_t = Vg*sin(t-2*pi/3); 

Vstring = [250,260,255];
Istring = interp1(Vs,Is,Vstring); 
Ps = Vstring.*Istring; 
Ptot = sum(Vstring.*Istring); 
Ig_orig = 2*Ptot/Vg/3; % Per phase current
Ig1_t = Ig_orig*sin(t);
Ig2_t = Ig_orig*sin(t+2*pi/3); 
Ig3_t = Ig_orig*sin(t-2*pi/3); 

% arbitrary point in time 
for theta =11:10:100%round(100*rand); 
% theta = 20; 

Vg1 = Vg1_t(theta); Vg2 = Vg2_t(theta); Vg3 = Vg3_t(theta); 
Ig1 = Ig1_t(theta); Ig2 = Ig2_t(theta); Ig3 = Ig3_t(theta); 
Pg1 = Vg1*Ig1; Pg2 = Vg2*Ig2; Pg3 = Vg3*Ig3; 

Avo = [1,1,0,0,0,0;
       0,0,1,1,0,0;
       0,0,0,0,1,1;
       Ig1 0 Ig2 0 0 0;
       0 0 0 Ig2 Ig3 0
       0 Ig1 0 0 0 Ig3;
  ];
   
bvo = [Vg1 Vg2 Vg3 Ps]';

cvx_begin
variables Vout_orig(N)

minimize norm (Vout_orig )
subject to 
    Avo*Vout_orig == bvo; 
cvx_end


% x = x_log(:,theta); % retrieve the nominal operating point! (Incorrect) 
% Vout_orig = x(1:N); 

Vin_orig = Vstring([1,3,1,2,2,3])';
D_orig   = Vout_orig ./ Vin_orig; 
Vin_orig = Vstring; %we only truly have 3 independent voltage variables (once the duty cycles are fixed) 
dI_dV    = interp1(Vs(2:end),dI_dVs,Vin_orig); %IV Curve linearization 
Is_orig  = interp1(Vs,Is,Vin_orig); 


% perturb V (initially)
Vin_new = Vin_orig+randn(1,N/2); %new vin setpoint
Perr = ones(N/2,1); 
dV = 0.5; 
dD_base = 0.001; 
D = D_orig;%+dD_base*randn(N,1);
% D(1) = D(1) + 0.001; 
% D(3) = (Is_orig(1)-D(1)*Ig(1))/(Ig(2));
D(D>1) = 1; 
D(D<-1) = -1;  % saturation

Kpv = 0.00001;
Kiv = 0;% 0.0000001;

Kpi = 0.001;
Kii = 0;%0.0000001;

Verr_int = [0,0,0]';
Vd = [254,256,259]'; %new voltage setpoint 
%Vd = [250 260 255]';
%desired grid current 
Iind = interp1(Vs,Is,Vd);
Pd = sum( Vd.*Iind );
Igd = Pd*2 / 3 / (Vg); 
Ierr_int = [0,0,0]';

Vg_phi = [Vg1;Vg2;Vg3];
Ig = [Ig1;Ig2;Ig3]; 
Igd = Igd/Ig_orig * Ig; 

% desired input current
Id = interp1(Vs,Is,Vd); 
Pds = Vd.*Id; 
Pphi_frac = Vg_phi.^2/(sum(Vg_phi.^2)); 
Pdphi = sum(Pds) *Pphi_frac; 

cvx_begin
variables Ps_frac(N)

minimize 0
subject to 
    Ps_frac(1)*Pds(1) + Ps_frac(2)*Pds(3) == Pdphi(1);
    Ps_frac(3)*Pds(1) + Ps_frac(4)*Pds(2) == Pdphi(2);
    Ps_frac(5)*Pds(2) + Ps_frac(6)*Pds(3) == Pdphi(3);
    Ps_frac(1) + Ps_frac(3) == 1;
    Ps_frac(2) + Ps_frac(6) == 1;
    Ps_frac(4) + Ps_frac(5) == 1;
    
    Ps_frac>=0;
    Ps_frac<=1;
cvx_end

Ps_frac_mat = [Ps_frac(1),0,0;
          0,0,Ps_frac(2);
          Ps_frac(3),0,0;
          0,Ps_frac(4),0
          0,Ps_frac(5),0
          0,0,Ps_frac(6)
          ];
      
Ic_d =  Ps_frac_mat *Id;
      
cnt = 1; 
x_prev = [Vin_orig';0;Ig]; 
cvt_vid = [1;4;6]; %converters to control voltage
cvt_iid = [2;3;5]; %converters to control voltage

for tstep = 1:1000


x_new = six_conv_plant_transfer_function(D,x_prev,Vg_phi); %how do we get from D -> x   

Vin_new  = x_new(1:N/2); % extract useful state info 
Vin_prev = x_prev(1:N/2);
Ig_new   = x_new(end - 2:end); 

x_prev = x_new; 

%% Update States
Is_new  = interp1(Vs,Is,Vin_new);
dI_dV   = interp1(Vs(2:end),dI_dVs,Vin_new); %update state
Is_prev = interp1(Vs,Is,Vin_prev);
Ic_new  = [D(1),0,0;D(2),0,0,;0,D(3),0;0,D(4),0;0,0,D(5);0,0,D(6)]*Ig_new;           % converter current

P_new  = Vin_new .*Is_new;
P_prev = Vin_prev.*Is_prev;

% update target string current to avoid saturate actuator 
%Ic_d = solvePowerFraction(Vs,Is,Vd,Vg_phi,N);

%% control law
%PI controller for string voltage control
D_sign = sign(D); 
D = abs(D); 
Verr = Vd-Vin_new ; 
Verr_int = Verr_int + Verr; 
 
Ierr = Ic_d(cvt_iid) - Ic_new(cvt_iid); 
Ierr_int = Ierr_int + Ierr; 

for ii = 1:N/2    
    dD = -(Kpv*Verr(ii) + Kiv*Verr_int(ii));     
%     dD = min(dD,0.0005);
%     dD = max(dD,0.0001);
    D(cvt_vid(ii)) = D(cvt_vid(ii))+dD;
%     if one converter is shut off the other converter has to take on the
%     responsibility 
    if D(cvt_vid(ii)) <0
         D(cvt_iid(ii)) = D(cvt_iid(ii))+dD;
    end
end


% PI controller for converter current  control 
for ii = 1:N/2
    dD = (Kpi*Ierr(ii) + Kii*Ierr_int(ii));     
%     dD = min(dD,0.0005);
%     dD = max(dD,0.0001);    
    D(cvt_iid(ii)) = D(cvt_iid(ii))+dD;
    
%     if one converter is shut off the other converter has to take on the
%     responsibility
    if D(cvt_iid(ii)) <0
         D(cvt_vid(ii)) = D(cvt_vid(ii))-dD;
    end
    
end

D(D>1) = 1; 
D(D<0) = 0;  % saturation

D = D.*D_sign; 
%% Control Saturation
%D(abs(D)<1e-3) = 0; %prevent crossover

    
% Log the duty cycle count
D_log(:,cnt) =D;
V_log(:,cnt) =Vin_new-Vd; 
P_log(:,cnt) = P_new;
Ig_log(:,cnt) = Ig_new - Igd; 
Ic_log(:,cnt) = Ic_new - Ic_d;
Vn_log(cnt) = x_new(end-3); 
cnt = cnt + 1; 


% Perr = P_new-P_prev;
% P_new'
if mod(cnt,100)==0
 tstep
end

end

figure; 
subplot(3,1,1); 
h = plot(V_log');  title('String Voltage Error'); my_plot_setting(h); legend('S1','S2','S3')
% subplot(4,1,2);
% h = plot(P_log');  title('String Power'); my_plot_setting(h); 
subplot(3,1,2);
h = plot(Ig_log');  title('Grid Current Error'); my_plot_setting(h); legend('Phi1','Phi2','Phi3')
subplot(3,1,3); 
h = plot(Ic_log');  title('Conv Current Error'); my_plot_setting(h); legend('I1','I2','I3','I4','I5','I6')


figure; 

V_log_per_conv = [V_log(1,:); V_log(3,:); V_log(1,:);V_log(2,:);V_log(2,:);V_log(3,:)];
for ii = 1:N
    subplot(N,1,ii);
    h = plot(D_log(ii,:));
    if ii == 1
    title('Converesion Ratio of Converter N')
    end
%     yyaxis right; 
%     h(2) = plot(V_log_per_conv(ii,:).*D_log(ii,:));
    my_plot_setting(h); 
end


figure; subplot(2,2,1);
h=plot(V_log(1,:));
title('V1')
my_plot_setting(h)

subplot(2,2,2)
h=plot(Ic_log(3,:));
title('Ic3')
my_plot_setting(h)

subplot(2,2,3)
h= plot(D_log(1,:));
title('D1')
my_plot_setting(h)

subplot(2,2,4); 
h = plot(D_log(3,:));
title('D3')

my_plot_setting(h)

end
%end