clear; 

Vg = 1000; 
N = 12; 
load x_temp.mat
load VI_Curve.mat
Vout_orig = x(1:N); 
Vin_orig = Vmpps([1,2,5,6,1,2,3,4,3,4,5,6])';
Ig_orig = [Ig1;Ig2;Ig3];
Vn_orig = x(13);
D_orig = Vout_orig ./ Vin_orig; 
Vin_orig = Vmpps; %we only truly have 6 voltage variables (once the duty cycles are fixed) 
dI_dV = interp1(Vs(2:end),dI_dVs,Vin_orig); %IV Curve linearization 
Is_orig = interp1(Vs,Is,Vin_orig); 
Vg = [Vg1;Vg2;Vg3];



% perturb V (initially)
Vin_new = Vin_orig+randn(1,N/2); %new vin setpoint
Perr = ones(N/2,1); 
dV = 0.5; 
D_orig = [D_orig;Vn_orig]; 
cnt = 1; 
x_prev = [Vin_orig';Vn_orig;Ig_orig]; 
    
while (max(abs(Perr))>1e-2)

Is_new = Is_orig + dI_dV.*(Vin_new-Vin_orig); %linearized guess of new input current  
Ptot = sum(Vin_new.*Is_new); 
Ig = Ptot/(Vg1^2+Vg2^2+Vg3^2).*([Vg1,Vg2,Vg3]); %current setpoint

%% Vout/grid voltage constraint 
%  voltage constraint, the last one is the neutral point voltage 
 A_v = [Vin_new([1,2,5,6]),zeros(1,2*N/3),-1;
        zeros(1,N/3),Vin_new([1,2,3,4]),zeros(1,N/3),-1;
        zeros(1,2*N/3),Vin_new([3,4,5,6]),-1];
    
    
%%  Current per string constraint
% Current Block Matrix
A_II = zeros(N/2, N+1); 
A_II(1,1) = Ig(1); A_II(1,5)=Ig(2); 
A_II(2,2) = Ig(1); A_II(2,6)=Ig(2);

A_II(3,7) = Ig(2); A_II(3,9) =Ig(3); 
A_II(4,8) = Ig(2); A_II(4,10)=Ig(3);

A_II(5,3) = Ig(1); A_II(5,11)=Ig(3); 
A_II(6,4) = Ig(1); A_II(6,12)=Ig(3);


% Voltage Block Matrix
A = [A_v;A_II];

b = [Vg; Is_new'];

%  do we really need to solve opt? (sounds like heavy machinery)
cvx_begin quiet
variables D(N+1)

minimize norm(D - D_orig)
subject to 
    A*D==b;
    abs(D(1:N))<=1;
cvx_end

if strcmp(cvx_status,'Solved')
%     figure; 
%     bar([D-D_orig]); 
%     legend('New State','Prev State'); 
    disp(cnt); 
else    
    disp('Solver Failed');
end

% stepping the state variable 
x_new = plant_transfer_function(D,x_prev,Vg); %how to we get from D -> x

x_prev = x_new;     

%% Update States
Is_new = interp1(Vs,Is,Vin_new);
dI_dV = interp1(Vs(2:end),dI_dVs,Vin_new); %update state

P_new  = Vin_new.*Is_new;
P_prev = Vin_orig.*Is_orig;

% record the old value for MPP
Vin_orig = Vin_new; 
Is_orig = Is_new; 
D_orig = D; 

% Log the duty cycle count
D_log(:,cnt) = D;
V_log(:,cnt) = Vin_new; 
P_log(:,cnt) = P_new; 
cnt = cnt + 1; 

%update new Vin setpoint using incremental conductance
for ii = 1:length(Vin_new)
    
    if dI_dV(ii)>(-Is_new(ii)/Vin_new(ii))
        Vin_new(ii) = Vin_new(ii)+dV; 
    else
        Vin_new(ii) = Vin_new(ii)-dV;
    end
    
end

Perr = P_new-P_prev;
Vin_new


end


figure; plot(P_log'); legend(); 
figure; plot(D_log'); legend(); 




