clear
close all
%% consider the following topology
% P1    P2   P3
% |     |    |
% C1-S1-C3   |
% |     |    |
% |    C4-S2-C5   
% |          |
% C2---S3----C6

%% Setup the linear system
Nstate = 6; % Number of states
Nin    = 6;    % Number of inputs 
Nout   = 5;   % Number of outputs (last output is not used)

%assume a nominal condition 
Lout = 400e-6; 
% Cout = 5e-6;
Cin  = 20e-6; 

% Some nominal values 
Vpv  = 30; 
Ig = [12,6,6]';
D = 0.5*ones(Nin,1); 

Aiv = [-D(1),-D(3),0; 0 -D(4) -D(5); -D(2) 0 -D(6)]/Cin;
Avi = [D(1) 0 D(2); D(3) D(4) 0 ; 0 D(5) D(6)]/Lout;
A = [zeros(3,3), Aiv; Avi zeros(3,3)];

Bv = [-Ig(1) 0 -Ig(2) 0 0 0; 
     0 0 0 -Ig(2) -Ig(3) 0; 
     0 -Ig(1) 0 0 0 -Ig(3)]/Cin;

Bi = [Vpv Vpv 0   0   0  0; 
       0  0  Vpv Vpv  0  0;
       0  0  0   0  Vpv Vpv]/Lout;
   
B = [Bv; Bi];

C = [eye(Nout), zeros(Nout,Nstate-Nout)];
D = zeros(Nout,Nin); 

%% Augment for integral control for 5 of the states (system should solve for the sixth) 
Ai = [zeros(Nout+Nstate,Nout),[-C;A]];
Bi = [-D;B];
Ci = [zeros(Nout,Nout),C];
Di = D;

%% Pole Placement
 Gol = ss(A,B,C,D); 
 Goli = ss(Ai,Bi,Ci,Di); % Open loop transfer function
 pol  = pole(Goli);
 pcl = pol - 5000*ones(Nstate+Nout,1);
%  pcl (7:end) = -8000; 
%  pcl(11:12) = 0; % Avoid pole placement problem
 
Vin_max = 40; 
Ig_max  = 15;
u_max = 1; 
Q = sqrt(1/Nstate)*eye(Nstate);
Q(6,6) = 0; % don't control last state
Q(1:3,1:3) = Q(1:3,1:3)/  (Vin_max^2);
Q(4:6,4:6)  = Q(4:6,4:6)/ (Ig_max^2);

R = sqrt(1/Nin)*eye(Nin); 

 K = lqr(Ai,Bi,Q,R);
%  K = place(Ai,Bi,pcl);
 Ki = K(:,1:Nout); 
 Kp = K(:,Nout+1:end); 

Cx = eye(size(A));
Dx = zeros(size(B)); 

Golx = ss(A,B,Cx,Dx); 
s = tf('s');
% Kp = place(A,B,pole(Gol)-1000); 
Gclx = C*feedback(Golx,Kp)+D; % *note that this need to rethink about the pole locations! 
Gcl = feedback(-Gclx*Ki/s,ss(eye(Nout)));

%% Simulation
load SPICE_IV.mat

% Initial conditons
Vin = 40; 
x0   = [Vin,Vin,Vin,12,6,6]'; %haven't connected to the grid yet 
x = x0; 
xnom = [Vpv,Vpv,Vpv,12,6,6]'; % six states to compensate

% Need to have a sensible setpoint
Ipv    = 4; 
Vd     = [30,30,30];
Pd     = sum(Vd*Ipv); 
Vg_mag = 20; 
Vgs    = [Vg_mag,-Vg_mag/2,-Vg_mag/2]; 
Ig_mag = 2*Pd/Vg_mag /3;
Igd    = [Ig_mag,Ig_mag/2,Ig_mag/2];
yd = [Vd,Igd(1:2)]'; % last point is not tracked (5 measurements to track)

D0 = 0.5*ones(Nin,1); 
D = D0; 
solver_options = odeset('RelTol',1e-9);

% Simulation Setup
fsw = 100e3; 
tcy = 1/fsw; 
tspan = 3e-3;
tstep = linspace(0,tspan,tspan/tcy+1); 

err_int = zeros(Nout,1); 

for ii = 1:length(tstep)-1
    
[t,x] = ode45(@(t,x) sim_dynamics_6d(t,x,IV_curve,D,Vgs),[0,tstep(2)],x,solver_options);
x   = x(end,:)' 
y   = C*x;

state = x - xnom; 

err =  yd - abs(y); % only care about absolute value 
err_int = err*tcy+err_int;
dD = - Kp*state - Ki*err_int;
D = D0+dD;  % pay close attention to the sign! 
D = max(min(D,0.999),0); % avoid saturation

ylog(:,ii) = y; 
xlog(:,ii) = x;
Dlog(:,ii) = D; 
end

figure; 
subplot(3,1,1);hold on;
h = plot(tstep(1:end-1),xlog(1:3,:)); 
xlabel('Time');ylabel('PV Voltage (V)'); 
my_plot_setting(h);

subplot(3,1,2);
h = plot(tstep(1:end-1),Dlog); 
xlabel('Time'); 
ylabel('Duty Ratio');
my_plot_setting(h);

subplot(3,1,3);
h= plot(tstep(1:end-1),xlog(4:6,:)); 
xlabel('Time');ylabel('Grid Current(A)'); 
my_plot_setting(h);






