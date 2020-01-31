%state space control design
clear
close all

N = 2; %2 input 2 output system
% assume a nominal condition 
Lout = 300e-6; 
Cin= 20e-6; 
Cout = 10e-6;
% Nominal Condition
Vin = 30; 
Vout = 40; 
Io = 3; 
D1 = 0.5; 
D2 = 0.8333; 

% State Equation (add dummy state for the pv current input)
A = [0, -D1/Cin -D2/Cin 0 ; 
     D1/Lout 0   0 -1/Lout  ;
     D2/Lout 0   0  1/Lout  ; 
     0  0.5/Cout  -0.5/Cout   0]; 
 
B = [-Io/Cin,-Io/Cin; Vin/Lout 0 ;0 Vin/Lout; 0 0 ;];


C =[1 0 0 0 ;  0 0 0 1];
%C = eye(size(A));
D = zeros(N,N); 
Gol = ss(A,B,C,D);
pol = pole(Gol);

csys = canon(Gol, 'companion'); 
% state feedback
Kp = place(A,B,pol-10000*ones(4,1));
% feedforward term (can do so much, you will need integral action in general to account for all kinds of uncertainty) 
yss = [3,1]';
Nxu = ([A,B;C,D])\[zeros(4,2);eye(2)];
Nx = Nxu(1:4,:); Nu = Nxu(5:6,:);
Nff = Nu+Kp*Nx; % feedforward term
uss = Nu*yss;


load SPICE_IV.mat

% Initial conditons
Vg = 50; 
Vin = 30; 
I1 = 0; I2 = 0; 
Vo1 = 25; Vo2 =25; 
x0 = [Vin;I1;I2;Vo1];
xd = [30,3,3,15]';
D0 = [0.5;0.8333];
D = D0; 
solver_options = odeset('RelTol',1e-9);

% Simulation Setup
fsw = 100e3; 
tcy = 1/fsw; 
tspan = 1e-3;
tstep = linspace(0,tspan,tspan/tcy); 

for ii = 1:length(tstep)-1
    
[t,x] = ode45(@(t,x) sim_dynamics(t,x,IV_curve,D),[0,tstep(2)],x0,solver_options);
y = C*x'; 
x0 = x(end,:)'; 
D = D0 +(uss- Kp*(x0-xd)); 
D = max(min(D,0.999),0.001); % avoid saturation

ylog(:,ii) = y(:,end); 
Ilog(:,ii) = x0(2:3)';
Dlog(:,ii) = D; 
end

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


% Cx = eye(size(A));
% Dx = zeros(size(B)); 
% 
% Golx = ss(A,B,Cx,Dx); 
% Loop_tf = Golx*Kp; 
% 
% % desired steady state 

% 
% Gclx = C*inv(eye(4)+Loop_tf)*Golx*Nff;%*note that this need to rethink about the pole locations! 
% figure; step(Gol); 
% figure; step(Gclx)


% Integral Control if needed
% Ki = [0.1 0 ; 0 0.01];
% Gcl = inv(eye(size(N)) + GLoop)*GLoop; 
% 
% figure; 
% step(Gcl)








