clear; close all; 
N = 6; 
load VI_Curve.mat
load balanced_6_conv_sys.mat
t = linspace(0,2*pi,100);
Vg = 300;

Vg1 = Vg*sin(t);
Vg2 = Vg*sin(t+2*pi/3); 
Vg3 = Vg*sin(t-2*pi/3); 

Vstring = [300,300,300];
Istring = interp1(Vs,Is,Vstring); 
Ptot = sum(Vstring.*Istring); 
Ig = 2*Ptot/Vg/3; % Per phase current
Ig1 = Ig*sin(t);
Ig2 = Ig*sin(t+2*pi/3); 
Ig3 = Ig*sin(t-2*pi/3); 

% arbitrary point in time 
theta =51;%round(100*rand); 

Vg1 = Vg1(theta); Vg2 = Vg2(theta); Vg3 = Vg3(theta); 
Ig1 = Ig1(theta); Ig2 = Ig2(theta); Ig3 = Ig3(theta); 

x = x_log(:,theta); % retrieve the nominal operating point 
Vout_orig = x(1:N); 
Vin_orig = Vstring([1,3,1,2,2,3])';
D_orig   = Vout_orig ./ Vin_orig; 
Vin_orig = Vstring; %we only truly have 3 independent voltage variables (once the duty cycles are fixed) 
dI_dV    = interp1(Vs(2:end),dI_dVs,Vin_orig); %IV Curve linearization 
Is_orig  = interp1(Vs,Is,Vin_orig); 

Vg = [Vg1;Vg2;Vg3];
Ig = [Ig1;Ig2;Ig3];


% perturb V (initially)
Vin_new = Vin_orig+randn(1,N/2); %new vin setpoint
Perr = ones(N/2,1); 
dV = 0.5; 
dD_base = 0.001; 
D = D_orig+dD_base*randn(N,1); 
D(D>1) = 1; 
D(D<-1) = -1;  % saturation

cnt = 1; 
x_prev = [Vin_orig';0;Ig]; 
cvt_id = [1,3;4,5;2,6];
for tstep = 1:2000

x_new = six_conv_plant_transfer_function(D,x_prev,Vg); %how do we get from D -> x   

Vin_new = x_new(1:N/2); % extract useful state info 
Vin_prev = x_prev(1:N/2);
x_prev = x_new; 
%% Update States
Is_new  = interp1(Vs,Is,Vin_new);
dI_dV   = interp1(Vs(2:end),dI_dVs,Vin_new); %update state
Is_prev = interp1(Vs,Is,Vin_prev);

P_new  = Vin_new .*Is_new;
P_prev = Vin_prev.*Is_prev;

%% control law
%update new duty cycle setpoint using P&O

D_sign = sign(D); 

for ii = 1:length(Vin_new)
    D = abs(D);
    P_err = abs(P_new(ii)-P_prev(ii));
    dD = dD_base * P_err;
    dD = min(dD,0.0005);
    dD = max(dD,0.00005);
    
    if P_new(ii)>P_prev(ii)
        if Vin_new(ii)>Vin_prev(ii)
            D(cvt_id(ii,:)) = D(cvt_id(ii,:))-dD; 
        else
            D(cvt_id(ii,:)) = D(cvt_id(ii,:))+dD; 
        end
    else
        if Vin_new(ii)>Vin_prev(ii)
            D(cvt_id(ii,:)) = D(cvt_id(ii,:))+dD; 
        else
            D(cvt_id(ii,:)) = D(cvt_id(ii,:))-dD; 
        end
    end
end

D = D.*D_sign; 
%% Control Saturation
%D(abs(D)<1e-3) = 0; %prevent crossover
D(D>1) = 1; 
D(D<-1) = -1;  % saturation
    
% Log the duty cycle count
D_log(:,cnt) = D;
V_log(:,cnt) = Vin_new; 
P_log(:,cnt) = P_new; 
cnt = cnt + 1; 

Perr = P_new-P_prev;
P_new'

end



figure; plot(V_log'); title('String Voltage'); 
figure; plot(P_log');  title('String Power'); 
figure; plot(D_log'); title('Converter Ratio'); 


