%state space control design
clear
close all


printK = 1; 

Nin = 2; %2 input 2 output system
Nstate = 4; 
Nout = 2; 
% assume a nominal condition 
Lout = 300e-6; 
Cin= 20e-6; 
Cout = 10e-6;
% Nominal Condition
Vin = 30; 
Vout = 40; 
Io = 3; 
D1 = 0.4; 
D2 = 0.6; 

% State Equation (add dummy state for the pv current input)
A = [0, -D1/Cin -D2/Cin 0 ; 
     D1/Lout 0   0 -1/Lout  ;
     D2/Lout 0   0  1/Lout  ; 
     0  0.5/Cout  -0.5/Cout   0]; 
 
B = [-Io/Cin,-Io/Cin; Vin/Lout 0 ;0 Vin/Lout; 0 0 ;];


C =[1 0 0 0 ;  0 0 0 1];
%C = eye(size(A));
D = zeros(Nin,Nin); 

K1 = linspace(-0.1,0.1,10); 
K2 = K1; 
figure;
max_damp = -1500; 
for ii = 1:length(K1)
    for jj = 1:length(K1)
        K = [K1(ii) 0 0 0; 0 0 0 K2(jj)];
        A_diag = A+B*K;
        pole_diag = eig(A_diag);
        if (max(real(pole_diag))<max_damp)
            max_damp = max(real(pole_diag));
            K_target = K; 
            plot(real(pole_diag),imag(pole_diag),'x','markersize',10,'linewidth',2);
            hold on;
        end
    end
end
K_diag =  - [ 0.0459         0         0         0;
         0         0         0   -0.0123];

  
Ai = [zeros(6,2),[-C;A]];
Bi = [-D;B];
Ci = [zeros(2,2),C];
Di = D;

Gol  = ss(A,B,C,D); 
Goli = ss(Ai,Bi,Ci,Di);
pol  = pole(Goli);

pcl(1:2) = [-10000;-10000];
pcl(3:6) = pol(1:4) - 10000*ones(4,1);

p_itae = [-2.99+12.192j, -2.99-12.192j,-5.602+7.554j,-5.602-7.554j,-7.089+2.772j,-7.089-2.772j];
p_bess = [-4.217+7.530j,-4.217-7.530j,-6.261+4.402j,-6.261-4.402j, -7.121+1.454j, -7.121-1.454j];
pcl_itae = p_itae*1000;
pcl_bess = p_bess*1000; 

figure; plot(pcl_itae,'x','markersize',12,'linewidth',2); 
hold on; plot(pcl_bess,'x','markersize',12,'linewidth',2); 
hold on; plot(pol,'x','markersize',12,'linewidth',2);
hold on; plot(pcl,'x','markersize',12,'linewidth',2); 
% state feedback with integral
K = place(Ai,Bi,pcl_bess);
Ki = K(:,1:2); 
Kp = K(:,3:end); 

Kp = place(A,B,pol(1:4) - 10000*ones(4,1)); 

Cx = eye(size(A));
Dx = zeros(size(B)); 

Golx = ss(A,B,Cx,Dx); 
s = tf('s');
%Kp = place(A,B,pole(Gol)-1000); 
Gclx = C*feedback(Golx,Kp);
pole(Gclx); 
Gcl = feedback(-Gclx*Ki/s,ss(eye(2)));
% figure; pzmap(Gcl); 

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
x0 = [Vin;I1;I2;Vo1];
xd = [32,3,3,13]';
D0 = [0.5;0.8333];
D = D0; 
solver_options = odeset('RelTol',1e-9);

% Simulation Setup
fsw = 100e3; 
tcy = 1/fsw; 
tspan = 1e-3;
tstep = linspace(0,tspan,tspan/tcy); 



err_int = [0 0]'; 

for ii = 1:length(tstep)-1
    
[t,x] = ode45(@(t,x) sim_dynamics(t,x,IV_curve,D),[0,tstep(2)],x0,solver_options);
y = C*x'; 
x0 = x(end,:)'; 
err = x0-xd; 
err_int = C*err*tcy+err_int; 
D = D0 - Kp*err ;%+ Ki*err_int; % pay close attention to the sign! 
D = max(min(D,0.999),0.001); % avoid saturation

ylog(:,ii) = C*err;%y(:,end); 
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
% Gcl = inv(eye(size(Nin)) + GLoop)*GLoop; 
% 
% figure; 
% step(Gcl)








