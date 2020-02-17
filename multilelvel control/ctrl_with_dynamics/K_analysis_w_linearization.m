% K gain analysis with sinusoidal steady state change 

%% consider the following topology
% P1    P2   P3
% |     |    |
% C1-S1-C3   |
% |     |    |
% |    C4-S2-C5   
% |          |
% C2---S3----C6
clear
close all; 
%% Setup the linear system
Nstate = 6; % Number of states
Nin    = 6;    % Number of inputs 
Nout   = 5;   % Number of outputs (last output is not used)

%assume a nominal condition 
Lout = 100e-6; 
Cin  = 10e-6; 
num_point = 2*3000; 
tstep = linspace(0,2*pi,num_point);

% Some nominal values 
Vpv  = 50; 
Iin  = 3;
Pin  = Vpv*Iin; 
Vg_amp = 40; 
Ig_amp = Pin*2/Vg_amp; 

Ig1 = (Ig_amp*(sin(tstep)));
Ig2 = (Ig_amp*(sin(tstep+2*pi/3))); 
Ig3 = (Ig_amp*(sin(tstep-2*pi/3))); 

getDOpenLoop(Vpv,Iin,Vg_amp,num_point/2);
load Dnom.mat; 

% LQR Loss Matrix (Bryson's Rule to Normalize the Value)
Vin_max = 60; 
Ig_max  = 10;
u_max   = 1; 

Qdiag  = [5e5*ones(1,3),5e6*ones(1,2),1/(Vin_max^2)*ones(1,3),1/(Ig_max^2)*ones(1,3)];
Qpdiag = [1/(Vin_max^2)*ones(1,3),1/(Ig_max^2)*ones(1,3)];
% Qdiag  = Qdiag*sqrt(1/(Nout+Nstate));
% Qpdiag = Qpdiag * sqrt(1/(Nstate)); 
Qp     = diag (Qpdiag); 


Q = diag(Qdiag); 
R = sqrt(1/Nin)*1*eye(Nin); 
for ii = 1:num_point
    
% Ig = [4,4,4]';
% D = .5*ones(Nin,1); 

D           = [D1(ii),D2(ii),D3(ii),D4(ii),D5(ii),D6(ii)];
D(isnan(D)) = 0; 
Dnom        = D; 
Ig          = [Ig1(ii),Ig2(ii),Ig3(ii)]; 

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
% 
% C(5,5) = 0; 
% C(5,6) = 1; 

D = zeros(Nout,Nin); 

%% Augment for integral control for 5 of the states (system should solve for the sixth) 
Ai = [zeros(Nout+Nstate,Nout),[-C;A]];
Bi = [-D;B];
Ci = [zeros(Nout,Nout),C];
Di = D;

Q(Nout+4,Nout+4) = 1/((Ig(1))^2+1);
Q(Nout+5,Nout+5) = 1/((Ig(2))^2+1);
Q(Nout+6,Nout+6) = 1/((Ig(3))^2+1);

% Qp(4,4) = 1/((Ig(1))^2+0.1);
% Qp(5,5) = 1/((Ig(2))^2+0.1);
% Qp(6,6) = 1/((Ig(3))^2+0.1);

% dD_max = abs(0.5- abs(abs(Dnom)-0.5)); 
dD_max = 0.1*ones(1,length(Dnom)); 

Rdiag = 1./(dD_max.^2);
R = diag(Rdiag); 

try
    K = lqr(Ai,Bi,Q,R);
    
    
catch
    K = reshape(K_log(ii-1,:,:),6,11); 
end


if sum(K)~=0
Cx = eye(size(A));
Dx = zeros(size(B)); 

Golx = ss(A,B,Cx,Dx); 
Ki = K       (:,1:Nout); 
Kp = K       (:,Nout+1:end); 
s = tf('s');
Gclx = C*feedback(Golx,Kp)+D; % *note that this need to rethink about the pole locations! 
Gcl = feedback(-Gclx*Ki/s,ss(eye(Nout)));
% pole(Gcl)
stable = 1; 
if sum(real(pole(Gcl))>-10)
    stable = 0;
    disp('Warning, unstable'); 
end
end

% Kp = lqr(A,B,Qp,R);
%     
% Kp_log(ii,:,:) = Kp;
K_log(ii,:,:)  = K; 
rC_log(ii) = rank(ctrb(A,B)); 
rA_log(ii) = rank(A); 
rB_log(ii) = rank(B);
cl_pole_log(ii) = max(real(pole(Gcl))); 
stable_log(ii) = stable; 
xnom_log(ii,:) = [Vpv,Vpv,Vpv,Ig(1),Ig(2),Ig(3)];
end

figure; 
subplot(3,1,1); 
h(1) = plot(tstep,D1);
my_plot_setting(h); 
ylabel('Duty Cycle of C1');

subplot(3,1,2); 
h(1) = plot(tstep,Ig1);
hold on; 
h(2) = plot(tstep,Ig2);
h(3) = plot(tstep,Ig3); 
my_plot_setting(h); 
ylabel('Grid Current');

subplot(3,1,3); 
h(3) = plot(tstep,Vpv*ones(1,length(tstep)));
my_plot_setting(h); 
ylabel('PV Voltage');


% plot(K_log(:,1,4))
K11 = K_log(:,2,1);
K12 = K_log(:,2,2);
K13 = K_log(:,2,3);
K14 = K_log(:,2,4);
K15 = K_log(:,2,5);

phi = (tstep(1:length(K11)));

figure; 
subplot(2,1,1);
h(1) = plot(phi, K11);
hold on; h(2)=plot(phi,K12); 
hold on; h(3)=plot(phi,K13); 
hold on; h(4)=plot(phi,K14); 
hold on; h(5)=plot(phi,K15); 
legend('V1','V2','V3','I1','I2')
ylabel('Integral Gain (K_{2,1}-K_{2,5})'); 

K21 = K_log(:,2,6);
K22 = K_log(:,2,7);
K23 = K_log(:,2,8);
K24 = K_log(:,2,9);
K25 = K_log(:,2,10);
K26 = K_log(:,2,11);
my_plot_setting(h);

subplot(2,1,2); 
h(1)=plot(phi, K21); 
hold on; h(2)= plot(phi,K22); 
hold on; h(3)= plot(phi,K23); 
hold on; h(4)= plot(phi,K24); 
hold on; h(5)= plot(phi,K25); 
hold on; h(6)= plot(phi,K26); 
ylabel('Proportional Gain (K_{2,6}-K_{2,10})'); 
xlabel('Grid Angle (rad)'); 
legend('V1','V2','V3','I1','I2','I3')
my_plot_setting(h);
save ('Knom12','K_log','xnom_log','phi'); 
