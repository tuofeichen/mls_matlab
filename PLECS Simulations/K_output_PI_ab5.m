% K gain analysis with sinusoidal steady state change 

%% consider the following topology
% P1    P2   P3
% |     |    |
% C1-S1-C3   |
% |     |    |
% |    C4-S2-C5   
% |          |
% C2---S3----C6


Vn = (D1V1+D2V3+D3V1+D4V2+D5V2+D6V3)/3;



clear
close all
load IV_curve.mat
% close all; 
%% Setup the linear system
Nstate = 5; % Number of states
Nin    = 6;    % Number of inputs 
Nout   = 5;   % Number of outputs (last output is not used)

Nstack = 1; 
Nskip  = 3; 

%assume a nominal condition 
Lout = 15e-3; 
Cin  = 100e-6; 
num_point = 2*150; 
tstep = linspace(0,2*pi,num_point);

% Some nominal values 
Vpv  =[850,850,850];
% Iin = interp1(V25,I25,Vpv); 
Iin = [25,25,25];
Pin  = sum(Vpv.*Iin); 
Vg_amp = 1000/Nstack; 
Ig_amp = Pin*2/3/Vg_amp; 

Ig1 = (Ig_amp*(sin(tstep)));
Ig2 = (Ig_amp*(sin(tstep-2*pi/3))); 
Ig3 = (Ig_amp*(sin(tstep+2*pi/3))); 

getDOpenLoop(Vpv(1),Iin(1),Vg_amp,num_point/2);
load Dnom.mat; 
load Knom_abc.mat
% LQR Loss Matrix (Bryson's Rule to Normalize the Value)
Vin_max = 0.05*100; 
Ig_max  = 0.05*10;
u_max   = 1; 

Qdiag  = [5e5*ones(1,3),5e6*ones(1,2),1/(Vin_max^2)*ones(1,3),1/(Ig_max^2)*ones(1,2)];
% Qpdiag = [1/(Vin_max^2)*ones(1,3),1/(Ig_max^2)*ones(1,3)];
% Qp     = diag (Qpdiag); 


Q = diag(Qdiag); 
R = sqrt(1/Nin)*1*eye(Nin); 

for ii = 1:num_point
    
D           = [D1(ii),D2(ii),D3(ii),D4(ii),D5(ii),D6(ii)];
D(isnan(D)) = 0; 
Dnom        = D; 
Ig          = [Ig1(ii),Ig2(ii),Ig3(ii)]; 


Aiv = [D(1)-D(3),D(1); -D(4) -D(5); D(2) D(2)-D(6)]/Cin;
Avi = [D(1) 0 D(2); 0 D(5) D(6);]/Lout;
A = [zeros(3,3), Aiv; Avi zeros(2,2)]; 

Bv = [-Ig(1) 0 -Ig(2) 0 0 0; 
     0 0 0 -Ig(2) -Ig(3) 0; 
     0 -Ig(1) 0 0 0 -Ig(3)]/Cin; %this is fine nominally

Bi = [0 0 Vpv(1) Vpv(3)  0  0; 
       0  0  0  0  Vpv(1)   Vpv(2);]/Lout;   
B = [Bv; Bi];

C = [eye(Nout), zeros(Nout,Nstate-Nout)];

% switch Nskip
%     case 1       
%          C(4,4) = 0; C(4,5) = 1;     
%          C(5,6) = 1; C(5,5) = 0; 
%     case 2
%          C(5,6) = 1; C(5,5) = 0; 
%     case 3
% 
% end

D = zeros(Nout,Nin); 

%% Augment for integral control for 5 of the states (system should solve for the sixth) 
Ai = [zeros(Nout+Nstate,Nout),[-C;A]];
Bi = [-D;B];
Ci = [zeros(Nout,Nout),C];
Di = D;
% 
% Q(Nout+4,Nout+4) = 1/((Ig(1))^2+1);
% Q(Nout+5,Nout+5) = 1/((Ig(2))^2+1);
% Q(Nout+6,Nout+6) = 1/((Ig(3))^2+1);
% Qp(4,4) = 1/((Ig(1))^2+0.1);
% Qp(5,5) = 1/((Ig(2))^2+0.1);
% Qp(6,6) = 1/((Ig(3))^2+0.1);

% dD_max = abs(0.5- abs(abs(Dnom)-0.5)); 
dD_max = 0.1*ones(1,length(Dnom)); 
Rdiag = 1./(dD_max.^2);
R = diag(Rdiag); 

try
    [K,S,P] = lqr(Ai,Bi,Q,R);

%     switch Nskip
%         case 1       
%              K = [K(:,1:3),zeros(6,1),K(:,4:end)];        
%         case 2
%              K = [K(:,1:4),zeros(6,1),K(:,5:end)];
%         case 3
%              K = [K(:,1:5),zeros(6,1),K(:,6:end)]; 
%     end
%     
catch
%     K = lqr(Ai+randn,Bi,Q,R); 
    disp('Warning, LQR Failed!') ;
    if (ii==1) 
        xnom_log(ii,:) = [Vpv,Ig(1),Ig(2),Ig(3)];
        continue; 
    end 
    K = reshape(K_log(ii-1,:,:),6,10); 
end


if sum(sum(K))~=0
    if sum(real(P)>0)
        disp('Warning, unstable'); 
    end
end
pole_log(ii)  = max(real(P)); 
K_log(ii,:,:)  = K; 
xnom_log(ii,:) = [Vpv,Ig(1),Ig(2),Ig(3)];
end


%% xs -> D1

plotConvId = 1; 
K11 = K_log(:,plotConvId,1);
K12 = K_log(:,plotConvId,2);
K13 = K_log(:,plotConvId,3);
K14 = K_log(:,plotConvId,4);
K15 = K_log(:,plotConvId,5);
K16 = K_log(:,plotConvId,6);
K17 = K_log(:,plotConvId,7);
K18 = K_log(:,plotConvId,8);
K19 = K_log(:,plotConvId,9);
K110 = K_log(:,plotConvId,10);

% phi = theta_log; %(tstep(1:length(K11)));
phi = (tstep(1:length(K11)));
figure; 
subplot(2,1,1);
plot(phi, [K11,K12,K13,K14,K15]);
title(['Integral Gain related to D',num2str(plotConvId)]);
% legend('V1->D1','V2->D1','V3->D1');
legend('V1->D1','V2->D1','V3->D1','Ig1->D1','Ig2->D1','Ig3->D1');


% K111 = K_log(:,plotConvId,11);
% K112 = K_log(:,plotConvId,12);

subplot(2,1,2);
plot(phi, [K16,K17,K18,K19,K110]);
title(['Proportional Gain related to D',num2str(plotConvId)]);
% legend('V1->D1','V2->D1','V3->D1');
legend('V1->D1','V2->D1','V3->D1','Ig1->D1','Ig2->D1','Ig3->D1');
xlabel('Grid Angle (rad)')

% figure;
% subplot(3,1,1); 
% h(1) = plot(tstep,D1);
% my_plot_setting(h); 
% ylabel('Duty Cycle of C1');
% 
% subplot(3,1,2); 
% h(1) = plot(tstep,Ig1);
% hold on; 
% h(2) = plot(tstep,Ig2);
% h(3) = plot(tstep,Ig3); 
% my_plot_setting(h); 
% ylabel('Grid Current');
% 
% subplot(3,1,3); 
% h(3) = plot(tstep,Vpv(1)*ones(1,length(tstep)));
% my_plot_setting(h); 
% ylabel('PV Voltage');
% phi = (tstep(1:length(K11)));

% switch Nskip
%     case 1       
%         save ('Knom23','K_log','xnom_log','phi'); 
%     case 2
%         save ('Knom13','K_log','xnom_log','phi'); 
%     case 3
%         save ('Knom12','K_log','xnom_log','phi'); 
% end
%         
save('Knom_bc5','K_log','xnom_log','phi'); 
        
        