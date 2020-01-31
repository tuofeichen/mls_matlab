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
set(0, 'DefaultLineLineWidth', 2);
%% Setup the linear system
Nstate = 6;    % Number of states V1, V2, V3 and Id, Iq 
Nin    = 6;    % Number of inputs 
Nout   = 5;    % Number of outputs (same as the number of states)

%assume a nominal condition 
Lout = 100e-6; 
Cin  = 10e-6; 
num_point = 2*600; 
tstep = linspace(0,2*pi,num_point);

% Some nominal values 
Vpv  = 80; 
Iin  = 3;
Pin  = Vpv*Iin; 
Vg_amp = 120; 

% ABC Frame current amplitude
Ig_amp = Pin*2/Vg_amp; 
% DQ frame current setpoint (PF = 1)
Id_amp = 0;%Ig_amp; %*2/3; 
Iq_amp = Ig_amp;%0; 

Ig1 = (Ig_amp*(sin(tstep)));
Ig2 = (Ig_amp*(sin(tstep+2*pi/3))); 
Ig3 = (Ig_amp*(sin(tstep-2*pi/3))); 

getDOpenLoop(Vpv,Iin,Vg_amp,num_point/2);
load Dnom.mat; 

% LQR Loss Matrix (Bryson's Rule to Normalize the Value)
Vin_max = 1.1*Vpv;
dV_max  = 0.2*Vpv; 
dI_max  = 0.1*Ig_amp;
u_max   = 1; 

% constant Q matrix 
Qdiag  = [5e5*ones(1,3),5e6*ones(1,2),1/(dV_max^2)*ones(1,3),1/(dI_max^2),1/(dI_max^2),0];
Q = diag(Qdiag); 

% constant R matrix
dD_max = 0.05*ones(1,Nin); 
Rdiag = 1./(dD_max.^2);
R = diag(Rdiag); 

Kc = 2/3*[1,-0.5,-0.5;0 -sqrt(3)/2 sqrt(3)/2;1/3,1/3,1/3]; %clark transform for ABC (In this case more like ACB) 

invalid_cnt = 1; 
unstable_cnt = 1; 

for ii = 1:num_point

theta       = ii/num_point*2*pi; %-pi/2+ii/num_point*2*pi; % where are we on the 60Hz cycle
T           =  Kc;
Tinv        =  inv(Kc); 

D           =  [D1(ii),D2(ii),D3(ii),D4(ii),D5(ii),D6(ii)];
D(isnan(D)) =   0; 
Dnom        =   D; 
Ig          =  [Ig1(ii),Ig2(ii),Ig3(ii)]; 
Iab         =   T*Ig'; 
Ig_test     =   Tinv(:,1:2)*Iab(1:2);

Aiv = [-D(1),-D(3),0; 0 -D(4) -D(5); -D(2) 0 -D(6)]*Tinv/Cin;
Avi = T*[D(1) 0 D(2); D(3) D(4) 0 ; 0 D(5) D(6)]/Lout;
A = [zeros(3,3), Aiv; Avi,zeros(3,3)]; 

Q(Nout+4,Nout+4) = 1/((Iab(1))^2+0.1);
Q(Nout+5,Nout+5) = 1/((Iab(2))^2+0.1);

%A = [zeros(3,3), Aiv; Avi,zeros(2,2)];
Bv = [-Ig(1) 0 -Ig(2) 0 0 0; 
     0 0 0 -Ig(2) -Ig(3) 0; 
     0 -Ig(1) 0 0 0 -Ig(3)]/Cin;
Bi = T*[Vpv Vpv 0   0   0  0; 
       0  0  Vpv Vpv  0  0;
       0  0  0   0  Vpv Vpv]/Lout;
   
B  = [Bv; Bi];
C  = [eye(Nout),zeros(Nout,Nstate-Nout)];
D  = zeros(Nout,Nin); 

%% Augment for integral control
Ai = [zeros(Nout+Nstate,Nout),[-C;A]];
Bi = [-D;B];
Ci = [zeros(Nout,Nout),C];
Di = D;

% limit control effort at zero crossing?

% 
% Dnom_abs_sort = sort(abs(Dnom),'ascend');
% dD_max = min(sum(Dnom_abs_sort(1:2))+0.001,0.1)*ones(1,length(Dnom)); 
% % dD_max = min(abs(Dnom)+0.01,0.1);
% Rdiag = 1./(dD_max.^2);
% R = diag(Rdiag); 

try
     K = lqr(Ai,Bi,Q,R);%,1e-5*ones(length(R),length(Q))');
     
%     K = lqr(Ai+eye(length(Ai))*100,Bi,zeros(size(Q)),R);     
%   pole placement
     ol_pole = pole(ss(Ai,Bi,Ci,Di));
% %     complex_pole_index = imag(ol_pole) ~= 0;
% %     real_pole_index = imag(ol_pole)==0; 
% %     pole_desired = [ol_pole(complex_pole_index)-1000; ol_pole(real_pole_index)-1000-10*randn(sum(real_pole_index),1)];
%     pole_desired = [ol_pole(1:6)-100;ol_pole(7:end)-[100,101,102,103,104]'];
%     K = place(Ai,Bi,pole_desired);
    valid_flag = 1; 
catch
    valid_flag = 0; 
    if ii >1 
        K = reshape(K_log(ii-1,:,:),6,11);
    else
        K = zeros(Nin,Nout+Nstate); 
    end
    invalid_cnt = invalid_cnt + 1; 
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
cl_pole = pole(Gcl);
[V,D] = eig(Gcl.A);
if sum(real(cl_pole)>0)
    unstable_cnt = unstable_cnt + 1; 
    disp('Warning, unstable'); 
else
%     disp('Found a stable K'); 
end

end

rC_log(ii) = rank(ctrb(A,B)); 
rA_log(ii) = rank(A);
rAiv_log(ii) = rank(Aiv);
rAvi_log(ii) = rank(Avi);
lA_log(:,ii) = eig(A); 
rB_log(ii) = rank(B);
ol_pole_log(:,ii) = ol_pole; 
cl_pole_log(ii) = max(real(pole(Gcl))); %cl_pole;
K_log(ii,:,:)  = K; 
theta_log(ii) = theta; 
xnom_log(ii,:) = [Vpv,Vpv,Vpv,Iab'];
Id_log(:,ii) = Iab; 

% T_log (:,:,ii) = T; 
% I_log(:,ii) = inv(T)*[Id_amp,Iq_amp,0]';

end

if sum(K_log(1,:,:))==0
    K_log(1,:,:) = K_log(2,:,:); 
end

% plot(K_log(:,1,4))
K11 = K_log(:,1,1);
K12 = K_log(:,1,2);
K13 = K_log(:,1,3);
K14 = K_log(:,1,4);
K15 = K_log(:,1,5);

phi = theta_log; %(tstep(1:length(K11)));
figure; 
subplot(3,1,1);

plot(phi, K11);
hold on; plot(phi,K12); 
hold on; plot(phi,K13);
title('D1 Dependency');
legend('V1->D1','V2->D1','V3->D1');
subplot(3,1,2);
plot(phi,K14); 
hold on; plot(phi,K15); 
legend('Ia->D1','Ib->D1')


K21 = K_log(:,2,6);
K22 = K_log(:,2,7);
K23 = K_log(:,2,8);
K24 = K_log(:,2,9);
K25 = K_log(:,2,10);


subplot(3,1,3);
plot(phi,Ig1,phi,Ig2,phi,Ig3); 
hold on; plot(phi,zeros(1,length(phi))); 

% subplot(3,1,2); plot(phi, K21); 
% hold on; plot(phi,K22); 
% hold on; plot(phi,K23); 
% hold on; plot(phi,K24); 
% hold on; plot(phi,K25); 
% legend('V1','V2','V3','Id','Iq')

subplot(3,1,3);
hold off; 
plot(phi, Id_log(1,:),phi,Id_log(2,:));
hold on; plot(phi,zeros(1,length(phi)));
save ('Knom_ab','K_log','xnom_log','phi'); 

% figure; 
% plot(cl_pole_log); 
