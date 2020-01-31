function x_new = plant_transfer_function(D,x_prev,Vg)
% input the control, previous state and measurement

load VI_Curve.mat
N = 12; % 12 converter system 
Vs_prev = x_prev(1:N/2);

dI_dV   = interp1(Vs(2:end),dI_dVs,Vs_prev);
Is_prev = interp1(Vs,Is,Vs_prev); 



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
bI = Is_prev - dI_dV.*Vs_prev; 

b = [Vg; bI;  0];

x_new = A\b; 

end