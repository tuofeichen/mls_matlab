% K gain analysis with Single Inverter Incorporating Dynamics of the Grid

function K = getKMatrix(Vpv)
% clear
% close all; 
%% Setup the linear system
Nstate = 4;   % Number of states
Nin    = 1;    % Number of inputs 
Nout   = 1;    % Number of outputs (last output is not used)

%assume a nominal condition 
Lout  = 200e-6; 
Cin   = 10e-6;
Lleak = 10e-6;
Cout  = 5e-6; 

% Some nominal values 
% Vpv  = 180; 
Iin  = 10;
Pin  = Vpv*Iin; 
Vg_amp = 120; 
Ig_amp = Pin/Vg_amp; 

% System matrix for the augmented state space
Vi_id = 1;
Ig_id = 2;
Vo_id = 3; 
Il_id = 4; 

%% A matrix
A = zeros(Nstate,Nstate);
% PV Voltage
A(Vi_id,Il_id) = -1/Cin;

% Grid Current
A(Ig_id,Vo_id) = 1/Lout; 

% Leakage Inductance Current
A(Il_id,Vo_id) = -1/Lleak;

% Inverter Output Voltage 
A(Vo_id,Il_id) = 1/Cout; 
A(Vo_id,Ig_id) = -1/Cout; 


%% B Matrix
B = zeros(Nstate,Nin); 
B(Il_id,1) = Vpv/Lleak; 

%% C Matrix
% C = [eye(Nout),zeros(Nout, Nstate-Nout)]; 
C = [0 1 0 0];
D = zeros(Nout,Nin); 

%% Augmented System for Integral Control
Ai = [zeros(Nout+Nstate,Nout),[-C;A]];
Bi = [-D;B];
Ci = [zeros(Nout,Nout),C];
Di = D; 

%% LQR Loss Matrix (Bryson's Rule to Normalize the Value)
Vin_max = 0.1*100; 
Ig_max  = 0.1*10;

Qdiag  = [1e6,1/(Vin_max^2),1/(Ig_max^2),1/(Vin_max^2),1/(Ig_max^2)];
Q = diag(Qdiag); 
Qpdiag = [1/(Vin_max^2)*ones(1,3),1/(Ig_max^2)*ones(1,3),1/(Vin_max^2)*ones(1,6),1/(Ig_max^2)*ones(1,6)];
Qp = diag(Qpdiag); 
dD_max = 0.01*ones(1,Nin);%length(Dnom)); 
Rdiag = 1./(dD_max.^2);
R = diag(Rdiag); 

nOutSense = 2; 
Csense = [eye(nOutSense),zeros(nOutSense, Nstate-nOutSense)]; 
Aei = [zeros(nOutSense+Nstate,nOutSense),[-Csense;A]];
Cei = [eye(nOutSense),zeros(nOutSense,Nstate)];

openLoopPole = eig(Aei); 
realOpenLoopPoleId = abs(imag(openLoopPole))<1;
imagOpenLoopPoleId = ~realOpenLoopPoleId; 
realClosedLoopPole = -1000-10*randn(sum(realOpenLoopPoleId),1); 
imagOpenLoopPole = openLoopPole(imagOpenLoopPoleId); 

imagClosedLoopPole = imagOpenLoopPole-1000;
closedLoopPole = [realClosedLoopPole;imagClosedLoopPole];

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
% save ('K_leak_pi','K'); 
end

