clear;
% close all; 
% Simulation Setup
fsw = 100e3;  % 100kHz
tcy = 1/fsw;  % control bandwidth
tspan = 1e-3; % simulation time span
tstep = linspace(0,tspan,tspan/tcy+1);
%% Setup the linear system
Nstate = 3;   % Number of states
Nin    = 1;    % Number of inputs 
Nout   = 1;    % Number of outputs (last output is not used)

err_int = zeros(Nout,1); 
errIntConvRatio = 0; 
Kcnt = 1; 

Vin_range = 10:20:200; 
for Vin = Vin_range
Klut(:,:,Kcnt) = get3StateKMatrix(Vin); 
Kcnt = Kcnt + 1; 
end

Vpv = 180; 
K = get3StateKMatrix(Vpv); 

% xnom = [180,15,120,15]';
yd = 180;%, 15,120,15];
solver_options = odeset('RelTol',1e-9);
%  initialziation
x = [10 0 0];
xnom = [180,15,120]';
ConvRatio = 0.5; 
Ipv = 10; 
Vg  = 120; 

Dnom = 0.1; 
D = Dnom;
for ii = 1:length(tstep)

% [t,x]  = ode45(@(t,x) sim_dynamics_single(t,x,D,Vg,Ipv),[0,tstep(2)],x,solver_options);
[t,x]  = ode45(@(t,x) sim_dynamics_without_leakage_state(t,x,D,Vg,Ipv),[0,tstep(2)],x,solver_options);
x      = x(end,:)' ;
y      = x(1);    

% K = interp1(Vin_range, permute(Klut,[3,2,1]),x(1)); 

Ki = K       (:,1:Nout); 
Kp = K       (:,Nout+1:end); 

state   = x - xnom; 
err     = yd - y; 
err_int = err*tcy + err_int;
Di      =   -Ki*err_int;
Ds      =   -Kp*state;
D       =   Dnom + Di +  Ds; 
D       =   min(max(D,0),0.25);

% yd_log(:,ii) = xnom_log(tnom_step,:)'; 
xlog(:,ii) = x;
Dlog(:,ii) = D;
Dilog(ii) = Di; 
Dslog(ii) = Ds; 
err_int_log(:,ii) = err_int;
convLog(ii) = x(3)/x(1); 
% Klog(ii) = K(1,2); 
% Vn_log(ii)= Vn; 

end

figure; 
subplot(3,1,1); 
plot(tstep,xlog','linewidth',2);
legend('PV Voltage','Grid Current','Output Voltage','Leakage Current'); 
subplot(3,1,2); 
plot(tstep,Dlog,'linewidth',2);
hold on; 
% plot(tstep,Dilog,tstep,Dslog);
plot(tstep,err_int_log,'linewidth',2);
title('Duty'); 

subplot(3,1,3);
plot(tstep,convLog,'linewidth',2);
title('Voltage Gain');
max(xlog(1,:))


