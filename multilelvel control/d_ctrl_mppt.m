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



% perturb V (initially)
Vin_new = Vin_orig+randn(1,N/2); %new vin setpoint
Perr = ones(N/2,1); 
dV = 0.5; 
dD = 0.0001; 
D = D_orig+0.01*randn(N,1); 
D(D>1) = 1; 
D(D<-1) = -1;  % saturation

cnt = 1; 
x_prev = [Vin_orig';Vn_orig;Ig_orig]; 
    
while (max(abs(Perr))>1e-6)

x_new = plant_transfer_function(D,x_prev,Vg); %how do we get from D -> x   

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
%update new duty cycle setpoint using incremental conductance
for ii = 1:length(Vin_new)
            
    ci = find_converter_index (ii);    
    sign_D = sign(D(ci));
    
    if dI_dV(ii)>(-Is_new(ii)/Vin_new(ii))
        D(ci) = sign_D.*(abs(D(ci))-dD); 
    else
        D(ci) = sign_D.*(abs(D(ci))+dD);      
    end
    

end
%% Control Saturation
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



figure; plot(V_log'); 
figure; plot(P_log');  
figure; plot(D_log'); 


