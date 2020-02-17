% MIMO combined state estimator design
% no optimality for poles just pole placement

clear
close all
%% Setup System
Nin = 2; %2 input 2 output system
Nstate = 4; 
Nout = 2; 
% Component Values
Lout = 300e-6; 
Cin= 20e-6; 
Cout = 10e-6;
% Nominal Condition
Vin = 30; 
Vout = 40; 
Io = 3; 
D1 = 0.4; 
D2 = 0.6; 

% SS model
A = [0, -D1/Cin -D2/Cin 0 ; 
     D1/Lout 0   0 -1/Lout  ;
     D2/Lout 0   0  1/Lout  ; 
     0  0.5/Cout  -0.5/Cout   0]; 
 
B = [-Io/Cin,-Io/Cin; Vin/Lout 0 ;0 Vin/Lout; 0 0 ;];
C =[1 0 0 0 ;  0 0 0 1];
D = zeros(Nin,Nin); 

Gol = ss(A,B,C,D); 

Ai = [zeros(6,2),[C;A]];
Bi = [D;B];
Ci = [eye(Nin),zeros(Nin,Nstate)];
Di = D;
Goli = ss(Ai,Bi,Ci,Di); 


%% Pole Placement for L estimator
pole_ol  = pole(Gol); 
pole_cl  = pole_ol-ones(Nstate,1)*10000;
fsw = 100e3; 
tcy = 1/fsw; 

pole_cl_disc = exp(pole_cl*tcy);%poles in z-domain
% Gi_disc = ss(A,B,C,D,tcy); 
G_disc = c2d(Gol,tcy); 
L = place(G_disc.A',G_disc.C',pole_cl_disc)'; %discrete time gain

% Integral Estimator
pole_i_ol = pole(Goli); 
pole_i_cl = pole_i_ol-ones(Nstate+Nin,1)*100000;
pole_i_cl_disc = exp(pole_i_cl*tcy);%poles in z-domain
Gi_disc = c2d(Goli,tcy); 
Li = place(Gi_disc.A',Gi_disc.C',pole_i_cl_disc)'; %discrete time gain


%% Simulation
% Simulation Setup
tspan = 2e-3;
tstep = linspace(0,tspan,tspan/tcy+1); 
solver_options = odeset('RelTol',1e-9);

load SPICE_IV.mat
% Initial conditons
Vg = 40; 
Vin = 40; 
I1 = 0; I2 = 0; 
Vo1 = 10; Vo2 =25; 
x0 = [Vin;I1;I2;Vo1];
x  = x0; 
D0 = [0.4;0.8];
Din = D0; 

% Controller Setup
xd = [32,3,3,13]'; %Desired output
err_int = [0 0]';  %initial integral error
K =[ 304.9054 -463.9802   -0.0485    0.2284   -0.0866    0.0367;
  434.1617  385.9187   -0.0564   -0.0702    0.2142   -0.0215]; %control gain
Ki = K(:,1:2); 
Kp = K(:,3:end); 


% Estimator Setup 
xhat = zeros(Nstate,1); %first two states are the y integral 
xhati = zeros(Nstate+Nin,1); 
x_est = x0; 
x_esti = x0;
y_i_est = [0;0];
y_i = [0;0];

for ii = 1:length(tstep)-1
    
[t,x] = ode45(@(t,x) sim_dynamics(t,x,IV_curve,Din),[tstep(1),tstep(2)],x,solver_options);
% obtain output
x = x(end,:)'; 
y = C*x;

if (ii == 150)
    
end

% State Estimator Action
y_est = C*x_est; 
xhat  = G_disc.A * xhat + G_disc.B*(Din-D0)+ L*(y-y_est); %predict and then correct
x_est = x0 + xhat; 
est_err = x - x_est; 

% Integral Estimator Action
y_i = y*tcy + y_i;
y_i_est = xhati(1:2) + C*x0*tcy*ii; 
xhati =  Gi_disc.A * xhati + Gi_disc.B*(Din-D0)+ Li*(y_i-y_i_est);
x_esti = x0 + xhati(3:end); 

% Controller Action
state_err = x_est-xd; 
err_int = (y-C*xd)*tcy+err_int; 
Din = D0 - Kp*state_err + Ki*err_int; % pay close attention to the sign! 
Din = max(min(Din,0.999),0.001); % avoid saturation

% Log Variables
ylog(:,ii) = y; 
Ilog(:,ii) = x(2:3)';
xhat_log(:,ii)   = x_est;
xhati_log(:,ii) = x_esti ;
yint_err_log(:,ii) = y_i-y_i_est; 
x_log(:,ii) = x; 
Dlog(:,ii) = Din; 
end

figure; 
subplot(2,1,1)
h(1)=plot(tstep(1:end-1),xhat_log(1,:)); %state estimate
hold on;  
h(2) = plot(tstep(1:end-1),x_log(1,:)); %truth
h(3) = plot(tstep(1:end-1),xhati_log(1,:)); %integral estimate
my_plot_setting(h);
legend('x state estimate','x truth','x integral estimate');

subplot(2,1,2); 
h = plot(tstep(1:end-1),yint_err_log); 
my_plot_setting(h); 

figure; 
subplot(3,1,1);
h = plot(tstep(1:end-1),ylog); 
xlabel('Time'); 
ylabel('Voltage'); legend('Vin','Vo1'); 
my_plot_setting(h);

subplot(3,1,2);
h = plot(tstep(1:end-1),Dlog); 
xlabel('Time'); 
ylabel('Duty Ratio'); legend('D1','D2'); 
my_plot_setting(h);

subplot(3,1,3);
h = plot(tstep(1:end-1),Ilog); 
xlabel('Time'); 
ylabel('Current'); legend('I_{L1}','I_{L2}'); 
my_plot_setting(h);










