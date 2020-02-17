%state space control design
clear
close all

printK = 1; 

Nin = 2; %2 input 2 output system
Nstate = 2; 
Nout = 2; 
% assume a nominal condition 
Lout = 300e-6; 
Cin= 20e-6; 

% Nominal Condition
Vin = 30; 
Vout = 40; 
Io = 3; 
D1 = 0.4; 
D2 = 0.6; 

% State Equation (add dummy state for the pv current input)
A = [0, -D1/Cin-D2/Cin; 
     D1/Lout+D2/Lout, 0];
     
B = [-Io/Cin,-Io/Cin; Vin/Lout, Vin/Lout;];


C =[1 0;0 D1];
%C = eye(size(A));
D = [0 0;Io 0;] ;

Ai = [zeros(Nout+Nstate,2),[-C;A]];
Bi = [-D;B];
Ci = [zeros(Nout,Nout),C];
Di = D;

Gol  = ss(A,B,C,D); 
Goli = ss(Ai,Bi,Ci,Di);
pol  = pole(Goli);

pcl = pol - 10000*ones(Nstate+Nout,1);

% Pole Prototypes
% p_itae = [-2.99+12.192j, -2.99-12.192j,-5.602+7.554j,-5.602-7.554j,-7.089+2.772j,-7.089-2.772j];
% p_bess = [-4.217+7.530j,-4.217-7.530j,-6.261+4.402j,-6.261-4.402j, -7.121+1.454j, -7.121-1.454j];
% pcl_itae = p_itae*1000;
% pcl_bess = p_bess*1000; 
% figure; plot(pcl_itae,'x','markersize',12,'linewidth',2); 
% hold on; plot(pcl_bess,'x','markersize',12,'linewidth',2); 
% state feedback with integral
K = place(Ai,Bi,pcl);
Ki = K(:,1:2); 
Kp = K(:,3:end); 

Cx = eye(size(A));
Dx = zeros(size(B)); 

Golx = ss(A,B,Cx,Dx); 
s = tf('s');
%Kp = place(A,B,pole(Gol)-1000); 
Gclx = C*feedback(Golx,Kp)+D;%*note that this need to rethink about the pole locations! 
Gcl = feedback(-Gclx*Ki/s,ss(eye(2)));
figure; 
hold on; plot(pol,'d','markersize',12,'linewidth',2);
hold on; plot(pcl,'d','markersize',12,'linewidth',2); 
pzmap(Gcl); 
%% feedforward term (can do so much, you will need integral action in general to account for all kinds of uncertainty) 
% yss = [0,0]';
% Nxu = ([A,B;C,D])\[zeros(4,2);eye(2)];
% Nx = Nxu(1:4,:); Nu = Nxu(5:6,:);
% Nff = Nu+Kp*Nx; % feedforward term
% uss = Nu*yss;


load SPICE_IV.mat
% Initial conditons
Vg = 40; 
Vin = 40; 
I1 = 0; I2 = 0; 
Vo1 = 10; Vo2 =25; 
x0 = [Vin;0];  %  initial condition
xnom = [32; 3.2];
x  = x0;
yd = [32,2.5]'; %  desired output


D0 = [D1;D2];
D = D0; 
solver_options = odeset('RelTol',1e-9);

% Simulation Setup
fsw = 100e3; 
tcy = 1/fsw; 
tspan = 60e-3;
tstep = linspace(0,tspan,tspan/tcy); 

err_int = [0 0]'; 

Vg = abs(40*sin(60*tstep));%grid voltage moving 

for ii = 1:length(tstep)-1
    
[t,x] = ode45(@(t,x) sim_dynamics_2d(t,x,IV_curve,D,Vg(ii)),[0,tstep(2)],x,solver_options);
x = x(end,:)'; 
y = [x(1);D(1)*x(2)]; 

state = x - xnom; 
err = yd - y; 
err_int = err*tcy+err_int;

D = D0 - Kp*state - Ki*err_int; % pay close attention to the sign! 
D = max(min(D,0.999),0.001); % avoid saturation

ylog(:,ii) = y; 
% Ilog(:,ii) = x0(2:3)';
Dlog(:,ii) = D; 
end

figure; 
subplot(2,1,1);
h(1) = plot(tstep(1:end-1),ylog(1,:)); 
xlabel('Time');ylabel('Voltage (V)'); 
yyaxis right; 
h(2) = plot(tstep(1:end-1),ylog(2,:));
ylabel('Current (A)'); legend('Vin','Ip1'); 
my_plot_setting(h);

subplot(2,1,2);
h = plot(tstep(1:end-1),Dlog); 
xlabel('Time'); 
ylabel('Duty Ratio'); legend('D1','D2'); 
my_plot_setting(h);

% subplot(3,1,3);
% h = plot(tstep(1:end-1),Ilog); 
% xlabel('Time'); 
% ylabel('Current'); legend('I_{L1}','I_{L2}'); 
% my_plot_setting(h);


if printK == 1
   for ii = 1:Nin
       for jj = 1:Nstate
       mat_index = [num2str(ii),num2str(jj)];
       fprintf(['.param kp', mat_index,'=',num2str(Kp(ii,jj)),'\n']); 
       end
   end
   
   for ii = 1:Nin
       for jj = 1:Nout
           mat_index = [num2str(ii),num2str(jj)];
           fprintf(['.param ki', mat_index,'=',num2str(Ki(ii,jj)),'\n']); 
       end
   end
end








