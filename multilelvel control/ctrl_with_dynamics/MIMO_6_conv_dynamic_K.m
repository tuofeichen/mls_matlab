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

%% Simulation
load SPICE_IV.mat
load Dnom.mat
load Knom.mat
tlen = 1:length(K_log); 
% 

% Initial conditons
Vin  = 40; 
x0   = [Vin,Vin,Vin,0,0,0]'; %haven't connected to the grid yet 
x    = x0; 
xnom = [Vpv,Vpv,Vpv,4,4,4]'; % six states to compensate

% Static Setpoint Test
Ipv    = 3; 
Vd     = [50,50,50];
Pd     = sum(Vd*Ipv); 
Vg_mag = 40; 
Ig_mag = 2*Pd/Vg_mag /3;
ttest  = pi/2;
Vgs    = [Vg_mag*sin(ttest),Vg_mag*sin(ttest+2*pi/3),Vg_mag*sin(ttest-2*pi/3)]; 
Igd    = abs([Ig_mag*sin(ttest),Ig_mag*sin(ttest+2*pi/3),Ig_mag*sin(ttest-2*pi/3)]); 
yd     = [Vd,Igd(1:2)]'; % last point is not tracked (5 measurements to track)

D0     = 0.3*ones(Nin,1); 
D      = D0; 
solver_options = odeset('RelTol',1e-9);

% Simulation Setup
fsw = 100e3;  % 100kHz
tcy = 1/fsw;  % control bandwidth

err_int = zeros(Nout,1); 
fline = 60; 
wline = fline*2*pi; %line frequency
tspan = 0.5/fline;
tstep = linspace(0,tspan,tspan/tcy+1); 

% allocate log variables 
yd_log = zeros(length(tstep),Nstate)'; 
ylog   = zeros(length(tstep),Nout)'; 
err_int_log = ylog; 
xlog = zeros(length(tstep),Nstate)'; 
Dlog = zeros(length(tstep),Nin)'; 
dDlog = Dlog; 
Vn_log = zeros(length(tstep),0)'; 

for ii = 1:length(tstep)

%     New grid current setpoint
  Vgs    = [Vg_mag*sin(wline*tstep(ii)),Vg_mag*sin(wline*tstep(ii)+2*pi/3),Vg_mag*sin(wline*tstep(ii)-2*pi/3)];  
  Igd    = abs([Ig_mag*sin(wline*tstep(ii)),Ig_mag*sin(wline*tstep(ii)+2*pi/3),Ig_mag*sin(wline*tstep(ii)-2*pi/3)]); 
  yd     = [Vd,Igd(1:2)]'; % last point is not tracked (5 measurements to track)
  xd     = [Vd,Igd]';
   

[t,x]  = ode45(@(t,x) sim_dynamics_6d(t,x,IV_curve,D,Vgs),[0,tstep(2)],x,solver_options);
x      = x(end,:)' ;
y      = C*x;

Vn = getVn(D,Vgs,x);

phi_inst      = mod(wline*tstep(ii),pi); 
% phi_inst      = ttest;
tnom_step     = ceil(interp1(phi,tlen,phi_inst));
xnom          = xnom_log(tnom_step,:)'; 

state   =   x - xnom; 
err     =   yd - abs(y);                 % only care about absolute value 
err_int =   err*tcy  + err_int;

K  = K_log   (tnom_step,:,:); 
K  = reshape (K,Nstate,Nstate+Nout);
Ki = K       (:,1:Nout); 
Kp = K       (:,Nout+1:end); 


dDi           = - Ki*err_int;
dDs           = - Kp*state;
dD            =   dDi + dDs; 

D             =   D0+dD;  % pay close attention to the sign!
D             =   max(min(D,1),-1); % saturation


yd_log(:,ii) = [Vd,Igd]'; 
ylog(:,ii) = y; 
xlog(:,ii) = x;
Dlog(:,ii) = D; 
dDlog(:,ii) = dD;
err_int_log(:,ii) = err_int;
Vn_log(ii)= Vn; 
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
h= plot(tstep,xlog(4:6,:),':'); 
hold on; 
h2 = plot(tstep,yd_log(4:6,:)); 
xlabel('Time');ylabel('Grid Current(A)'); 
my_plot_setting(h);
my_plot_setting(h2);

legend('Ig_1','Ig_2','Ig_3','Ig_{ref1}','Ig_{ref2}','Ig_{ref3}')


figure
h(1) = plot(tstep,err_int_log(end-1,:),'linewidth',2);
hold on; 
h(2) = plot(tstep,err_int_log(end,:),'linewidth',2);
h(3) = plot(tstep,0*tstep);
% my_plot_setting(h); 

% figure; 
% h = plot(tstep,err_int_log(end,:)); 



% if printK == 1
%    for ii = 1:Nin
%        for jj = 1:Nstate
%        mat_index = [num2str(ii),num2str(jj)];
%        fprintf(['.param kp', mat_index,'=',num2str(Kp(ii,jj)),'\n']); 
%        end
%    end
%    
%    for ii = 1:Nin
%        for jj = 1:Nout
%            mat_index = [num2str(ii),num2str(jj)];
%            fprintf(['.param ki', mat_index,'=',num2str(Ki(ii,jj)),'\n']); 
%        end
%    end
% end




