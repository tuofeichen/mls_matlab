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
Nstate = 5;   % Number of states
Nin    = 6;   % Number of inputs 
Nout   = 5;   % Number of outputs (last output is not used)

%assume a nominal condition 
Lout = 100e-6; 
Cin  = 10e-6; 

% Some nominal values 
Vpv     = 50; 
Ipv    = 3; 

%% Simulation
load SPICE_IV.mat
load Dnom.mat
load Knom.mat
tlen = 1:length(K_log); 


% Initial conditons
Vin  = 40; 
x0   = [Vin,Vin,Vin,0,0,0]'; %haven't connected to the grid yet 
x    = x0; 
x_nom = [Vpv,Vpv,Vpv,4,4,4]'; % six states to compensate

% Need to have a sensible setpoint
Vd     = [50,50,50];
Pd     = sum(Vd*Ipv); 
Vg_mag = 40; 
Ig_mag = 2*Pd/Vg_mag/3;

% DQ frame current setpoint (PF = 1)
Id_amp = Ig_mag*3/2; 
Iq_amp = 0; 


ttest  = pi/2;
Vgs    = [Vg_mag*sin(ttest),Vg_mag*sin(ttest+2*pi/3),Vg_mag*sin(ttest-2*pi/3)]; 
Igd    = [Ig_mag*sin(ttest),Ig_mag*sin(ttest+2*pi/3),Ig_mag*sin(ttest-2*pi/3)]; 
yd     = [Vd,Igd(1:2)]'; % last point is not tracked (5 measurements to track)

D0     = 0.5*ones(Nin,1); 
D      = D0; 
solver_options = odeset('RelTol',1e-9);

% Simulation Setup
fsw = 100e3;  % 100kHz
tcy = 1/fsw;  % control bandwidth

err_int = zeros(Nout,1); 
fline = 60; 
wline = fline*2*pi; %line frequency
tspan = 0.1/fline;
tstep = linspace(0,tspan,tspan/tcy+1); 

% allocate log variables 
yd_log = zeros(length(tstep),Nstate)'; 
ylog   = zeros(length(tstep),Nout)'; 
err_int_log = ylog; 
xlog = zeros(length(tstep),Nstate)'; 
Dlog = zeros(length(tstep),Nin)'; 
dDlog = Dlog; 
Vn_log = zeros(length(tstep),0)'; 


Kclark = [1,-0.5,-0.5;0 -sqrt(3)/2 sqrt(3)/2;1/3,1/3,1/3]; %clark transform for ABC 

for ii = 1:length(tstep)

%     New grid current setpoint
% Vgs    = [Vg_mag*sin(wline*tstep(ii)),Vg_mag*sin(wline*tstep(ii)+2*pi/3),Vg_mag*sin(wline*tstep(ii)-2*pi/3)];  
% Igd    = [Ig_mag*sin(wline*tstep(ii)),Ig_mag*sin(wline*tstep(ii)+2*pi/3),Ig_mag*sin(wline*tstep(ii)-2*pi/3)]; 
% yd     = [Vd,Igd(1:2)]'; % last point is not tracked (5 measurements to track)
% xd     = [Vd,Igd]';


[t,x]  = ode45(@(t,x) sim_dynamics_6d_bidirection(t,x,IV_curve,D,Vgs),[0,tstep(2)],x,solver_options);
x      = x(end,:)' ;

% Vn = getVn(D,Vgs,x);
% theta        = -pi/2 + wline*tstep(ii); % get the instantenous grid angle 
theta          =  -pi/2 + ttest; 
Kpark          =  [cos(theta),sin(theta),0; -sin(theta), cos(theta),0;0,0,1];

T              =   Kpark*Kclark;
x_dq           =   [x(1:3);T(1:end-1,:)*x(4:end)]; % DQ transformation

tnom_step      =   ceil(interp1(phi,tlen,theta,'linear','extrap'));
x_nom          =   xnom_log(tnom_step,1:3)';
x_nom          =   [x_nom;Id_amp;Iq_amp]; 

state          =   x_nom - x_dq; 
err_int        =   state*tcy  + err_int;

K  = K_log   (tnom_step,:,:); 
K  = reshape (K,Nin,Nstate+Nout);
Ki = K       (:,1:Nout); 
Kp = K       (:,Nout+1:end); 

dDi      =   Ki*err_int;
dDs      =   Kp*state;
dD       =   dDi + dDs; 

D0            =   [D1(tnom_step),D2(tnom_step),D3(tnom_step),D4(tnom_step),D5(tnom_step),D6(tnom_step)]';
D0(isnan(D0)) =   0; 
D             =   D0+dD;  % pay close attention to the sign!
D             =   max(min(D,1),-1); % saturation

yd_log(:,ii) = [Vd,Id_amp,Iq_amp]'; 
xlog(:,ii) = x_dq;
Dlog(:,ii) = D; 
dDlog(:,ii) = dD;
err_int_log(:,ii) = err_int;
% Vn_log(ii)= Vn; 
end


figure; 
subplot(3,1,1);hold on;
h = plot(tstep,xlog(1:3,:)); 
xlabel('Time');ylabel('PV Voltage (V)'); 
my_plot_setting(h);

subplot(3,1,2);
h = plot(tstep,Dlog); 
xlabel('Time'); 
ylabel('Duty Ratio');
my_plot_setting(h);
legend('D1','D2','D3','D4','D5','D6')

subplot(3,1,3);
%figure
%subplot(2,1,1)
h= plot(tstep,xlog(4:end,:),':'); 
hold on; 
h2 = plot(tstep,yd_log(4:end,:)); 
xlabel('Time');ylabel('Grid Current(A)'); 
my_plot_setting(h);
my_plot_setting(h2);
legend({'Id Sim','Iq Sim', 'Id Ref','Iq Ref'})
% legend('Ig_1','Ig_2','Ig_3','Ig_{ref1}','Ig_{ref2}','Ig_{ref3}')


figure
h(1) = plot(tstep,err_int_log(end-1,:),'linewidth',2);
hold on; 
h(2) = plot(tstep,err_int_log(end,:),'linewidth',2);
h(3) = plot(tstep,0*tstep);
my_plot_setting(h); 
