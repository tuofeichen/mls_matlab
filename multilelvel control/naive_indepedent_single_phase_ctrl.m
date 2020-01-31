clear; 
load VI_Curve.mat; %MPP ~ 280V
Vg = 400; 
V1 = 250; 
V2 = 250;
I1 = interp1(Vs,Is,V1);
I2 = interp1(Vs,Is,V2); 
Ig = (V1*I1+V2*I2)/Vg; 
V1o = V1*I1/Ig; 
V2o = V2*I2/Ig; 
D1 = V1o/V1; 
D2 = V2o/V2; 
dI_dV1 = interp1(Vs(2:end),dI_dVs,V1); 
dI_dV2 = interp1(Vs(2:end),dI_dVs,V2);

dD = 0.0005; 
D1 = D1 + dD*randn; 
D2 = D2 + dD*randn;

% 100 timestep
for ii = 1:500
   
    V1_log(ii) = V1; 
    V2_log(ii) = V2; 
    D1_log(ii) = D1; 
    D2_log(ii) = D2; 
    Ig_log(ii) = Ig; 
    A = [D1, D2, 0; [-diag([dI_dV1,dI_dV2]),[D1,D2]']];
    b = [Vg, I1-dI_dV1*V1,I2-dI_dV2*V2]';
    x = A\b; 
    
    V1_prev = V1; V2_prev = V2; I1_prev = I1; I2_prev = I2; 
    P1_prev = V1_prev*I1_prev; 
    P2_prev = V2_prev*I2_prev; 
   
    V1 = x(1); V2 = x(2); Ig = x(3); 
%     I1 = I1 +dI_dV1*(V1-V1_prev); %assume the local linearization is exact (avoid resolving system)
%     I2 = I2 +dI_dV2*(V2-V2_prev); 
    
    I1 = interp1(Vs,Is,V1);
    I2 = interp1(Vs,Is,V2); 
%     update linearization
    dI_dV1 = interp1(Vs(2:end),dI_dVs,V1); 
    dI_dV2 = interp1(Vs(2:end),dI_dVs,V2);

    P1 = V1*I1; P2 = V2*I2;
    
    if P1>P1_prev
        if V1>V1_prev
            D1 = D1-dD; 
        else
            D1 = D1+dD; 
        end
    else
        if V1>V1_prev
            D1 = D1+dD; 
        else
            D1 = D1-dD; 
        end
    end
    
    if P2>P2_prev
        if V2>V2_prev
            D2 = D2-dD; 
        else
            D2 = D2+dD; 
        end
    else
        if V2>V2_prev
            D2 = D2+dD; 
        else
            D2 = D2-dD; 
        end
    end
    
    D1 = max(D1,0);D1 = min(D1,1); 
    D2 = max(D2,0); D2 = min(D2,1); 
    %fprintf('V1 is %f, V2 is %f\r\n',V1,V2); 
    
    
end

figure; plot(V1_log); hold on; plot(V2_log); yyaxis right; plot(Ig_log); 

% This is possible since you don't have to worry about grid current 

