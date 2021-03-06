% K gain analysis with phase shifted full-bridge (isolated buck)

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
Nstate = 12;   % Number of states
Nin    = 6;    % Number of inputs 
Nout   = 5;    % Number of outputs (last output is not used)

%assume a nominal condition 
Lg  = 200e-6; 
Rg = 0.0001;
Cin   = 20e-6;
Lleak = 1e-6;
Cout  = 20e-6; 
fsw   = 100e3; 
Tsw   = 1/fsw; 
%fsw = 1; 

num_point = 2*120; 
tstep = linspace(0,2*pi,num_point);

% Some nominal values 
Vpv  = 80; 
Iin  = 10;
Pin  = Vpv*Iin; 
Vg_amp = 120; 
Ig_amp = Pin*2/Vg_amp; 

Ig1 = (Ig_amp*(sin(tstep)));
Ig2 = (Ig_amp*(sin(tstep-2*pi/3))); 
Ig3 = (Ig_amp*(sin(tstep+2*pi/3))); 

getDOpenLoop(Vpv,Iin,Vg_amp,num_point/2);
load Dnom.mat; 
Dsub  = Dnom./RoNom *Lleak*fsw;
Dsub(isnan(Dsub)) = 0; 
D1 = Dsub(1,:); 
D2 = Dsub(2,:); 
D3 = Dsub(3,:); 
D4 = Dsub(4,:); 
D5 = Dsub(5,:); 
D6 = Dsub(6,:); 



% System matrix for the augmented state space
Vi_id = [1 2 3];
Ig_id = [4 5 6];
Vo_id = 7:12; 

for ii = 1:length(D1)
%% A matrix
A = zeros(Nstate,Nstate);
% PV Voltage
A(Vi_id(1),Vo_id(1)) = -(D1(ii))*Tsw/(Lleak*Cin);
A(Vi_id(1),Vo_id(3)) = -(D3(ii))*Tsw/(Lleak*Cin);
A(Vi_id(2),Vo_id(4)) = -(D4(ii))*Tsw/(Lleak*Cin);
A(Vi_id(2),Vo_id(5)) = -(D5(ii))*Tsw/(Lleak*Cin);
A(Vi_id(3),Vo_id(2)) = -(D2(ii))*Tsw/(Lleak*Cin);
A(Vi_id(3),Vo_id(6)) = -(D6(ii))*Tsw/(Lleak*Cin);

% Grid Current
A(Ig_id(1),Vo_id(1)) = 1/Lg; 
A(Ig_id(1),Vo_id(2)) = 1/Lg; 
A(Ig_id(2),Vo_id(3)) = 1/Lg; 
A(Ig_id(2),Vo_id(4)) = 1/Lg; 
A(Ig_id(3),Vo_id(5)) = 1/Lg; 
A(Ig_id(3),Vo_id(6)) = 1/Lg; 


% Inverter Output Voltage 
A(Vo_id(1),Vi_id(1)) = (D1(ii))*Tsw/(Lleak*Cout); 
A(Vo_id(1),Ig_id(1)) = -1/Cout; 

A(Vo_id(2),Vi_id(3)) = (D2(ii))*Tsw/(Lleak*Cout); 
A(Vo_id(2),Ig_id(1)) = -1/Cout;  

A(Vo_id(3),Vi_id(1)) = (D3(ii))*Tsw/(Lleak*Cout); 
A(Vo_id(3),Ig_id(2)) = -1/Cout; 

A(Vo_id(4),Vi_id(2)) = (D4(ii))*Tsw/(Lleak*Cout); 
A(Vo_id(4),Ig_id(2)) = -1/Cout; 

A(Vo_id(5),Vi_id(2)) = (D5(ii))*Tsw/(Lleak*Cout); 
A(Vo_id(5),Ig_id(3)) = -1/Cout; 

A(Vo_id(6),Vi_id(3)) = (D6(ii))*Tsw/(Lleak*Cout); 
A(Vo_id(6),Ig_id(3)) = -1/Cout; 


%% B Matrix
B = zeros(Nstate,Nin); 

B(Vi_id(1),1) = -VoNom(1,ii)*Tsw/(Lleak*Cin);
B(Vi_id(3),2) = -VoNom(2,ii)*Tsw/(Lleak*Cin);
B(Vi_id(1),3) = -VoNom(3,ii)*Tsw/(Lleak*Cin);
B(Vi_id(2),4) = -VoNom(4,ii)*Tsw/(Lleak*Cin);
B(Vi_id(2),5) = -VoNom(5,ii)*Tsw/(Lleak*Cin);
B(Vi_id(3),6) = -VoNom(6,ii)*Tsw/(Lleak*Cin);

B(Vo_id(1),1) = -Vpv*Tsw/(Lleak*Cin);
B(Vo_id(2),2) = -Vpv*Tsw/(Lleak*Cin);
B(Vo_id(3),3) = -Vpv*Tsw/(Lleak*Cin);
B(Vo_id(4),4) = -Vpv*Tsw/(Lleak*Cin);
B(Vo_id(5),5) = -Vpv*Tsw/(Lleak*Cin);
B(Vo_id(6),6) = -Vpv*Tsw/(Lleak*Cin);


%% C Matrix
C = [eye(Nout),zeros(Nout, Nstate-Nout)]; 
D = zeros(Nout,Nin); 
%% Augmented System for Integral Control
Ai = [zeros(Nout+Nstate,Nout),[-C;A]];
Bi = [-D;B];
Ci = [zeros(Nout,Nout),C];
Di = D; 

%% LQR Loss Matrix (Bryson's Rule to Normalize the Value)
Vin_max = 0.01*100; 
Ig_max  = 0.05*10;
u_max   = 1; 

Qdiag  = [5e5*ones(1,3),5e6*ones(1,2),1/(Vin_max^2)*ones(1,3),1/(Ig_max^2)*ones(1,3)...
    1/(Vin_max^2)*ones(1,6)];

Q = diag(Qdiag); 
Qpdiag = [1/(Vin_max^2)*ones(1,3),1/(Ig_max^2)*ones(1,3),1/(Vin_max^2)*ones(1,6),1/(Ig_max^2)*ones(1,6)];
Qp = diag(Qpdiag); 
dD_max = 0.1*ones(1,Nin);%length(Dnom)); 
Rdiag = 1./(dD_max.^2);
R = diag(Rdiag); 

% Nout = 12; 
% Csense = [eye(Nout),zeros(Nout, Nstate-Nout)]; 
% Aei = [zeros(Nout+Nstate,Nout),[-Csense;A]];
% Cei = [eye(Nout),zeros(Nout,Nstate)];
% 
% openLoopPole = eig(Aei); 
% realOpenLoopPoleId = abs(imag(openLoopPole))<1;
% imagOpenLoopPoleId = ~realOpenLoopPoleId; 
% realClosedLoopPole = -1000-10*randn(sum(realOpenLoopPoleId),1); 
% imagOpenLoopPole = openLoopPole(imagOpenLoopPoleId); 
% 
% imagClosedLoopPole = [imagOpenLoopPole(1:2)-1000;imagOpenLoopPole(3:4)-1001;imagOpenLoopPole(5:6)-1002;...
%     imagOpenLoopPole(7:8)-1000; imagOpenLoopPole(9:10)-1001; imagOpenLoopPole(11:12)-1002;];
% 
% closedLoopPole = [realClosedLoopPole;imagClosedLoopPole];

try
    K = lqr(Ai,Bi,Q,R); % LQR controller 
%     L = place(Aei',Cei',closedLoopPole)'; %integral estimator with pole placement
%     L = place(A',Csense',closedLoopPole)';
catch
    warning('K invalid');  
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
    if sum(real(pole(Gcl))> 0)
        disp('Warning, unstable'); 
    end
end
K_log(ii,:,:)  = K(:,1:(2*Nout+1)); 
xnom_log(ii,:) = [Vpv,Vpv,Vpv,Ig1(ii),Ig2(ii),Ig3(ii)];

end

K11 = K_log(:,1,1);
K12 = K_log(:,1,2);
K13 = K_log(:,1,3);
K14 = K_log(:,1,4);
K15 = K_log(:,1,5);

% phi = theta_log; %(tstep(1:length(K11)));
phi = (tstep(1:length(K11)));
figure; 
subplot(2,1,1);
plot(phi, [K11,K12,K13,K14,K15]);
title('Integral Gain related to D1');
% legend('V1->D1','V2->D1','V3->D1');
legend('V1->D1','V2->D1','V3->D1','Ig1->D1','Ig2->D1');


K11 = K_log(:,1,6);
K12 = K_log(:,1,7);
K13 = K_log(:,1,8);
K14 = K_log(:,1,9);
K15 = K_log(:,1,10);
% K16 = K_log(:,1,Vo_id(1)); 
% K17 = K_log(:,1,Io_id(1)); 


subplot(2,1,2);
plot(phi, [K11,K12,K13,K14,K15]);
title('Proportional Gain related to D1');
% legend('V1->D1','V2->D1','V3->D1');
legend('V1->D1','V2->D1','V3->D1','Ig1->D1','Ig2->D1');
xlabel('Grid Angle (rad)')

phi = (tstep(1:length(K11)));
save ('Knom_leak','K_log','xnom_log','phi'); 
