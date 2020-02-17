clear; close all;
load VI_Curve.mat; %MPP ~ 280V

%

t = linspace(pi/2,5*pi/2,100);
Vgt = 400*sin(t); 
Vg_amp = 400; %amplitude of grid voltage
Vg = 400; 
V1 = 300; 
V2 = 250;

I1 = interp1(Vs,Is,V1);
I2 = interp1(Vs,Is,V2); 
Ig = (V1*I1+V2*I2)/Vg_amp; 

V1o = V1*I1/Ig; 
V2o = V2*I2/Ig; 
D1 = V1o/V1; 
D2 = V2o/V2; 
dI_dV1 = interp1(Vs(2:end),dI_dVs,V1); 
dI_dV2 = interp1(Vs(2:end),dI_dVs,V2);

dD = 0.0005; 

V1_d = 280; 
V2_d = 280; 

D1 = D1 + dD*randn; 
D2 = D2 + dD*randn;

Kpv = 0.01; 
Kiv = 0.0001; 
Kpi = 1;
V1_err_int = 0; 
V2_err_int = 0; 
cnt = 1; 
x_state  = [V1,V2,Ig]; 
ts = 1/60/(100*100); 
ode_opts = odeset('AbsTol',1e-9, 'MaxStep',1e-9); 

% 100 timestep
for jj = 1:100
    Vg = Vgt(jj); %new grid voltage
    theta = Vg/Vg_amp; 
    for ii = 1:100

        V1_log(cnt) = V1; 
        V2_log(cnt) = V2; 
        D1_log(cnt) = D1; 
        D2_log(cnt) = D2; 
        Ig_log(cnt) = Ig;  
        I_log(cnt,:) = [I1,I2]; 
        
        cnt = cnt + 1; 
        V1_err = (V1-V1_d) ;
        V1_err_int = V1_err_int + V1_err; 
        I_d1 =  Ig + Kpv*V1_err + Kiv*V1_err_int; 
        
        V2_err = (V2-V2_d) ; 
        V2_err_int = V2_err_int + V2_err; 
        I_d2 = Ig + Kpv*V2_err + Kiv*V2_err_int; 
        
        I_d1_inst = I_d1 * theta; 
        I_d2_inst = I_d2 * theta; 
        
        I_d1_err = I_d1_inst - Ig; 
        I_d2_err = I_d2_inst - Ig; 
        
        Vtot1 = Kpi*I_d1_err;
        Vtot2 = Kpi*I_d2_err; 
        
        D1 = D1+Vtot1/V1_d; 
        D2 = D2+Vtot2/V2_d; 
        

        D1 = max(D1,0);D1 = min(D1,1); 
        D2 = max(D2,0); D2 = min(D2,1); 
        
%         A = [D1, D2, 0; [-diag([dI_dV1,dI_dV2]),[D1,D2]']];
%         b = [Vg, I1-dI_dV1*V1,I2-dI_dV2*V2]';
%         x = A\b; 
%         
        [t,x_state] = ode45(@(t,x) conv_dynamics(t,x,[D1,D2],Vg,[I1,I2]),[0,ts/2,ts],x_state,ode_opts); 
        %figure; plot(t,x_state(:,3))
        x_state = x_state(end,:); 
        V1_prev = V1; V2_prev = V2; I1_prev = I1; I2_prev = I2; 

        V1 = x_state(1); V2 = x_state(2); Ig = x_state(3); 
    %     I1 = I1 +dI_dV1*(V1-V1_prev); %assume the local linearization is exact (avoid resolving system)
    %     I2 = I2 +dI_dV2*(V2-V2_prev); 

        I1 = interp1(Vs,Is,V1);
        I2 = interp1(Vs,Is,V2); 
    %     update linearization
        dI_dV1 = interp1(Vs(2:end),dI_dVs,V1); 
        dI_dV2 = interp1(Vs(2:end),dI_dVs,V2);

        %fprintf('V1 is %f, V2 is %f\r\n',V1,V2); 


    end
    subplot(3,1,1); plot(V1_log); hold on; plot(V2_log); hold off
    subplot(3,1,2); plot(Ig_log); 
    subplot(3,1,3); plot(D1_log); hold on; plot(D2_log); hold off; 
end
figure; plot(V1_log); hold on; plot(V2_log); yyaxis right; plot(Ig_log); 

% This is possible since you don't have to worry about grid current 

