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
% close all; 
set(0, 'DefaultLineLineWidth', 2);
%% Setup the linear system
Nstate = 6;    % Number of states V1, V2, V3 and Id, Iq 
Nin    = 6;    % Number of inputs 
Nout   = 5;    % Number of outputs (same as the number of states)

%assume a nominal condition 
Lout = 500e-6; 
Cin  = 30e-6; 
num_point = 2*120; 
tstep = linspace(0,2*pi,num_point);

% Some nominal values 
Vpv  = 100; 
Iin  = 20;
Pin  = Vpv*Iin; 
Vg_amp = 120; 

% ABC Frame current amplitude
Ig_amp = Pin*2/Vg_amp; 
% DQ frame current setpoint (PF = 1)
Id_amp = 0;%Ig_amp; %*2/3; 
Iq_amp = Ig_amp;%0; 

Ig1 = (Ig_amp*(sin(tstep)));
Ig2 = (Ig_amp*(sin(tstep-2*pi/3))); 
Ig3 = (Ig_amp*(sin(tstep+2*pi/3))); 

getDOpenLoop(Vpv,Iin,Vg_amp,num_point/2);
load Dnom.mat; 

% LQR Loss Matrix (Bryson's Rule to Normalize the Value)
Vin_max = 1.1*Vpv;
dV_max  = 0.005*Vpv; 
dI_max  = 0.01*Ig_amp;
u_max   = 1; 

% constant Q matrix 
Qdiag  = [5e5*ones(1,3),8e6*ones(1,2),1/(dV_max^2)*ones(1,3),1/(dI_max^2),1/(dI_max^2),0];
Q = diag(Qdiag); 

% constant R matrix
dD_max = 0.03*ones(1,Nin); 
Rdiag = 1./(dD_max.^2);
R = diag(Rdiag); 

Kc = 2/3*[1,-0.5,-0.5;0 sqrt(3)/2 -sqrt(3)/2;1/3,1/3,1/3]; %clark transform for ABC (In this case more like ACB) 

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

% Q(Nout+4,Nout+4) = 1/((Iab(1))^2+0.1);
% Q(Nout+5,Nout+5) = 1/((Iab(2))^2+0.1);

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

% if we have input delay
DelayT = struct('delay',1e-3,'a',zeros(Nstate,Nstate),'b',B,'c',zeros(Nout,Nstate),'d',zeros(Nout,Nin));
delayedStateSpaceModel = delayss(A,zeros(Nin,Nstate),C,D,DelayT);

A = delayedStateSpaceModel.A; 
B = delayedStateSpaceModel.B; 
%% Augment for implicit model following
Am = diag([-5000,-5000,-5000,-1,-1,-1]);
Ai = [A,zeros(Nstate,Nout+Nstate);-C, zeros(Nout,Nout),C;zeros(Nstate,Nout+Nstate) Am]; 
Bi = [B;zeros(Nout+Nstate,Nin)];

% Ci = eye(size(Ai)); 
% Di = D;
Qdiag  = [1/(dV_max^2)*ones(1,3),1/(dI_max^2)*ones(1,2),0,1e7*ones(1,3),5e6*ones(1,2),1/(dV_max^2)*zeros(1,3),1/(dI_max^2)*zeros(1,2),0];
Q = diag(Qdiag);

% Q = (C*A-C*Am)'*(C*A-C*Am);
% R = (C*B)'*C*B;%+R;
% N = (C*A-C*Am)'*C*B;

% Ai = [zeros(Nout+Nstate,Nout),[-C;A]];
%Ci = eye(size(Ai)); 
% Bi = [-D;B];
% Ci = [zeros(Nout,Nout),C];
% Di = D;

% limit control effort at zero crossing?

% 
% Dnom_abs_sort = sort(abs(Dnom),'ascend');
% dD_max = min(sum(Dnom_abs_sort(1:2))+0.05,0.1)*ones(1,length(Dnom)); 
% % dD_max = min(0.1*abs(Ig)+0.001)*ones(1,length(Dnom));
% % dD_max = min(dD_max,0.05)


% Rdiag = exp(abs(Dnom)-0.5-1)*; 
% Rdiag = max(Rdiag,1/(0.03^2)); 
% R = diag(Rdiag); 

try
     K = lqr(Ai,Bi,Q,R);%,1e-5*ones(length(R),length(Q))');
     Kp  = K(:,1:Nstate); 
     Ki  = K(:,Nstate+1:Nstate+Nout); 
     K = [Ki Kp];
     
%     K = lqr(Ai+eye(length(Ai))*100,Bi,zeros(size(Q)),R);     
%   pole placement
%      ol_pole = pole(ss(Ai,Bi,Ci,Di));
% %     complex_pole_index = imag(ol_pole) ~= 0;
% %     real_pole_index = imag(ol_pole)==0; 
% %     pole_desired = [ol_pole(complex_pole_index)-1000; ol_pole(real_pole_index)-1000-10*randn(sum(real_pole_index),1)];
%     pole_desired = [ol_pole(1:6)-100;ol_pole(7:end)-[100,101,102,103,104]'];
%     K = place(Ai,Bi,pole_desired);
    valid_flag = 1; 
catch
    warning('error in K');
    valid_flag = 0; 
    if ii >1 
        K = reshape(K_log(ii-1,:,:),6,11);
    else
        K = zeros(Nin,Nout+Nstate); 
    end
    invalid_cnt = invalid_cnt + 1; 
end

if sum(sum(K))~=0
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
R_log(ii) = Rdiag(1); 
rB_log(ii) = rank(B);
% ol_pole_log(:,ii) = ol_pole; 
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
%% Ia -> Ds
% K14 = K_log(:,1,4);
% K24 = K_log(:,2,4);
% K34 = K_log(:,3,4);
% K44 = K_log(:,4,4);
% K54 = K_log(:,5,4);
% K64 = K_log(:,6,4);

%% xs -> D1
K11 = K_log(:,1,1);
K12 = K_log(:,1,2);
K13 = K_log(:,1,3);
K14 = K_log(:,1,4);
K15 = K_log(:,1,5);

phi = theta_log; %(tstep(1:length(K11)));
figure; 
subplot(2,1,1);
plot(phi, [K11,K12,K13,K14,K15]);
title('Integral Gain related to D1');
% legend('V1->D1','V2->D1','V3->D1');
legend('V1->D1','V2->D1','V3->D1','Ia->D1','Ib->D1');


K11 = K_log(:,1,6);
K12 = K_log(:,1,7);
K13 = K_log(:,1,8);
K14 = K_log(:,1,9);
K15 = K_log(:,1,10);

subplot(2,1,2);
plot(phi, [K11,K12,K13,K14,K15]);
title('Proportional Gain related to D1');
% legend('V1->D1','V2->D1','V3->D1');
legend('V1->D1','V2->D1','V3->D1','Ia->D1','Ib->D1');

% legend('Ia->D1','Ib->D1')
% legend('Ia->D4','Ia->D5','Ia->D6');




% subplot(3,1,3);
% plot(phi,Ig1,phi,Ig2,phi,Ig3); 
% hold on; plot(phi,zeros(1,length(phi))); 
% legend('I1','I2','I3')
xlabel('Grid Angle (rad)')

% K21 = K_log(:,2,6);
% K22 = K_log(:,2,7);
% K23 = K_log(:,2,8);
% K24 = K_log(:,2,9);
% K25 = K_log(:,2,10);

% subplot(3,1,2); plot(phi, K21); 
% hold on; plot(phi,K22); 
% hold on; plot(phi,K23); 
% hold on; plot(phi,K24); 
% hold on; plot(phi,K25); 
% legend('V1','V2','V3','Id','Iq')

% subplot(3,1,3);
% plot(phi, Id_log(1,:),phi,Id_log(2,:));
% hold on; plot(phi,zeros(1,length(phi)));
save ('Knom_ab','K_log','xnom_log','phi'); 

% figure; 
% plot(cl_pole_log); 
