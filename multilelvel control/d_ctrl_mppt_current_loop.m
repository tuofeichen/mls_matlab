clear; 
N = 12; 
load x_temp.mat
load VI_Curve.mat
Vout_orig = x(1:N); 
Vin_orig = Vmpps([1,2,5,6,1,2,3,4,3,4,5,6])';
Ig_orig = [Ig1;Ig2;Ig3];
Vn_orig = x(13);
D_orig = Vout_orig ./ Vin_orig; 
Vin_orig = Vmpps; %we only truly have 6 independent voltage variables (once the duty cycles are fixed) 
dI_dV = interp1(Vs(2:end),dI_dVs,Vin_orig); %IV Curve linearization 
Is_orig = interp1(Vs,Is,Vin_orig); 
Vg = [Vg1;Vg2;Vg3];
Vg_mag = 1000; 
theta = Vg/Vg_mag; 


% perturb V (initially)
Vin_new = Vin_orig+randn(1,N/2); %new vin setpoint
Perr = ones(N/2,1); 
dV = 0.5; 
dD = 0.0001; 
D = D_orig;
D(1) = D(1)+0.005;%0.01*randn; 
D(D>1) = 1; 
D(D<-1) = -1;  % saturation

cnt = 1; 
x_prev = [Vin_orig';Vn_orig;Ig_orig]; 
    
while (max(abs(Perr))>1e-6)

x_new = plant_transfer_function(D,x_prev,Vg); %how to we get from D -> x   

Vin_new = x_new(1:N/2); % extract useful state info 
Vin_prev = x_prev(1:N/2);
Ig = x_new(end-2:end); 
x_prev = x_new; 
%% Update States
Is_new  = interp1(Vs,Is,Vin_new);
dI_dV   = interp1(Vs(2:end),dI_dVs,Vin_new); %update state
Is_prev = interp1(Vs,Is,Vin_prev);

P_new  = Vin_new .*Is_new;
P_phase = sum(P_new) * theta.^2/sum(theta.^2); 

P_prev = Vin_prev.*Is_prev;

%% control law
% update new duty cycle setpoint using incremental conductance
for ii = 1:length(Vin_new)
            
    ci = find_converter_index (ii);    
    sign_D = sign(D(ci));
    Vout_prev(ci) = Vin_new(ii)*D(ci); % keep track of last output voltage
    if dI_dV(ii)>(-Is_new(ii)/Vin_new(ii))
        D(ci) = sign_D.*(abs(D(ci))-dD);  % ? ! ?
    else
        D(ci) = sign_D.*(abs(D(ci))+dD);      
    end    
    Vout_new(ci) = Vin_new(ii)*D(ci); % new projected Vout

end

KI = 0.1; % proportional gain for current controller

Vtot_set = sum(Vout_prev(1:4)) + KI*(Ig_set(1) - Ig(1)); %phase 1 current
Vout1_set = Vtot_set - sum(Vout_new(2:4));  %subtraction
D(1) = Vout1_set/Vin_new(1);  % This is quite arbitrary


%% Control Saturation
D(D>1) = 1; 
D(D<-1) = -1;  % saturation
    
% Log the duty cycle count
D_log(:,cnt) = D;
V_log(:,cnt) = Vin_new; 
P_log(:,cnt) = P_new; 
I_log(1,cnt) = Ig(1); 
I_log(2,cnt) = Ig_set(1); 
cnt = cnt + 1; 

Perr = P_new-P_prev;
P_new'

end


figure;
subplot(3,1,1)
plot(I_log'); title('Grid Current vs Current Setpoint'); 
% 
subplot(3,1,2);
plot(V_log'); title('Voltage'); 
subplot(3,1,3); 
plot(P_log');  title('Power'); 
% figure; plot(D_log'); title('Duty Ratio'); 


