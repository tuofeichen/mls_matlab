clear; 
load VI_Curve.mat; %MPP ~ 280V
Vg = 400; 
V1 = 300; 
V2 = 250;
I1 = interp1(Vs,Is,V1);
I2 = interp1(Vs,Is,V2); 
Ig = (V1*I1+V2*I2)/Vg; 
V1o = V1*I1/Ig; 
V2o = V2*I2/Ig; 
D1_prev = V1o/V1; 
D2_prev = V2o/V2; 
dI_dV1 = interp1(Vs(2:end),dI_dVs,V1); 
dI_dV2 = interp1(Vs(2:end),dI_dVs,V2);

dD = 0.00001; 
D1 = D1_prev + dD*randn; 
D2 = D2_prev + dD*randn;

% 100 timestep
for ii = 1:500
   
    V1_log(ii) = V1; 
    V2_log(ii) = V2; 
    D1_log(ii) = D1; 
    D2_log(ii) = D2; 
    Ig_log(ii) = Ig; 
    A = [D1, D2, 0; [-diag([dI_dV1,dI_dV2]),[D1,D2]']];
    b = [Vg, I1-dI_dV1*V1,I2-dI_dV2*V2]';
    x = A\b; % solving the linear equation
    
    V1_prev = V1; V2_prev = V2; I1_prev = I1; I2_prev = I2; 
    P1_prev = V1_prev*I1_prev; 
    P2_prev = V2_prev*I2_prev;    
    V1 = x(1); V2 = x(2); Ig = x(3); 

%     two step solution is not correct 
    for jj = 1:1000
    V1_2_step = V1_log(1) + Ig_log(1)/dI_dV1*D1 - I1/dI_dV1; 
    V2_2_step = V2_log(1) + Ig_log(1)/dI_dV2*D2 - I2/dI_dV2; 
    Ig_2_step_from_V1 = interp1(Vs,Is,V1_2_step)/D1;
    Ig_2_step_from_V2 = interp1(Vs,Is,V2_2_step)/D2;
    Ig_log(1) = (Ig_2_step_from_V1+Ig_2_step_from_V2)/2;
    x_2_step = [V1_2_step;V2_2_step;Ig_2_step_from_V1;Ig_2_step_from_V2];
    x2_log(:,jj) = x_2_step;
    end
    
    D2 - D2_prev
    D1 - D1_prev
    
end


% This is possible since you don't have to worry about grid current 

