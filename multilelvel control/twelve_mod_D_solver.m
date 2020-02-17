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
dI_dV= interp1(Vs(2:end),dI_dV,Vin_orig); %IV Curve linearization 
Is_orig = interp1(Vs,Is,Vin_orig); 

% perturb D1
D = D_orig; 
D(1) = D(1) + 0.01; 

%% Vout/grid voltage constraint 
A_v = [D(1:2)',0,0,D(3:4)',-1;
       D(5:8)',0,0,-1;
       0,0,D(9:12)',-1];
    
%%  Current per string constraint
% Current Block Matrix
A_II = [D(1),D(5),0; D(2),D(6),0; 0,D(7),D(9); 0,D(8),D(10);D(3),0,D(11);D(4),0,D(12)];

% Voltage Block Matrix
A_IV = diag(dI_dV); 

A_I = [-A_IV,zeros(N/2,1),A_II];

A_Ig = [zeros(1,N/2+1),1,1,1]; 

A = [[A_v,zeros(3,3)];A_I;A_Ig];
bI = Is_orig - dI_dV.*Vin_orig; 

b = [Vg1;Vg2;Vg3; bI';  0];
%%

x_est = [Vin_orig';Vn_orig;Ig_orig]; 

cvx_begin
variables x(N/2+4)

minimize norm(x_est - x)
subject to 
    A*x==b;
cvx_end

if strcmp(cvx_status,'Solved')
    figure; 
    x = A\b; 
    bar([x,x_est]); 
    legend('New State','Prev State'); 
else    
    
disp('Solver Failed');
    

end





