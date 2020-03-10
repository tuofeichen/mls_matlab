% combine abc frame K
Nstate = 6;
Nout = 6; 
iGainId = 1:Nstate; 
pGainId = Nstate+1:Nstate+Nout;
load Knom12.mat
K12_log = K_log; 
Kp12_log = K12_log(:,:,pGainId); 
Ki12_log = K12_log(:,:,iGainId); 


load Knom13.mat
K13_log = K_log; 
Kp13_log = K13_log(:,:,pGainId); 
Ki13_log = K13_log(:,:,iGainId);  

load Knom23.mat
K23_log = K_log; 
Kp23_log = K23_log(:,:,pGainId);
Ki23_log = K23_log(:,:,iGainId);


% K12_log(:,:,1:6)  = Ki12_log;
% K12_log(:,:,7:12) = Kp12_log;
% 
% K13_log(:,:,1:6)  = Ki13_log;
% K13_log(:,:,7:12) = Kp13_log;
% 
% K23_log(:,:,1:6)  = Ki23_log;
% K23_log(:,:,7:12) = Kp23_log;
% 
% Kp = (Kp12_log+Kp13_log+Kp23_log)/3;
% Ki = (Ki12_log+Ki13_log+Ki23_log)/3; 


K_conv_12 = (K12_log + K13_log)/2;
K_conv_34 = (K12_log + K23_log)/2;
K_conv_56 = (K13_log + K23_log)/2;

K_log(:,1:2,:) = K_conv_12(:,1:2,:);
K_log(:,3:4,:) = K_conv_34(:,3:4,:);
K_log(:,5:6,:) = K_conv_56(:,5:6,:);

tstep = linspace(0,2*pi,length(K12_log));
num_point = length(tstep);
num_dist_state = 4; 

% for plotConvId = 1:6
% K11 = K_log(:,plotConvId,1);
% K12 = K_log(:,plotConvId,2);
% K13 = K_log(:,plotConvId,3);
% K14 = K_log(:,plotConvId,4);
% K15 = K_log(:,plotConvId,5);
% K16 = K_log(:,plotConvId,6);
% 
% % phi = theta_log; %(tstep(1:length(K11)));
% phi = (tstep(1:length(K11)));
% figure; 
% subplot(2,1,1);
% plot(phi, [K11,K12,K13,K14,K15,K16]);
% title(['Integral Gain related to D',num2str(plotConvId)]);
% % legend('V1->D1','V2->D1','V3->D1');
% legend('V1->D1','V2->D1','V3->D1','Ig1->D1','Ig2->D1','Ig3->D1');
% 
% 
% K17 = K_log(:,plotConvId,7);
% K18 = K_log(:,plotConvId,8);
% K19 = K_log(:,plotConvId,9);
% K110 = K_log(:,plotConvId,10);
% K111 = K_log(:,plotConvId,11);
% K112 = K_log(:,plotConvId,12);
% 
% subplot(2,1,2);
% plot(phi, [K17,K18,K19,K110,K111,K112]);
% title(['Proportional Gain related to D',num2str(plotConvId)]);
% % legend('V1->D1','V2->D1','V3->D1');
% legend('V1->D1','V2->D1','V3->D1','Ig1->D1','Ig2->D1','Ig3->D1');
% xlabel('Grid Angle (rad)')
% % 
%  end

Vi_id = 1:3; 
Ii_id = 4:6; 
Vp_id = 7:9; 
Ip_id = 10:12; 

K1_log = reshape(K_log(:,1,[Vi_id(1),Ii_id(1),Vp_id(1),Ip_id(1)]),num_point,num_dist_state); 
K2_log = reshape(K_log(:,2,[Vi_id(3),Ii_id(1),Vp_id(3),Ip_id(1)]),num_point,num_dist_state); 
K3_log = reshape(K_log(:,3,[Vi_id(1),Ii_id(2),Vp_id(1),Ip_id(2)]),num_point,num_dist_state);  
K4_log = reshape(K_log(:,4,[Vi_id(2),Ii_id(2),Vp_id(2),Ip_id(2)]),num_point,num_dist_state);  
K5_log = reshape(K_log(:,5,[Vi_id(2),Ii_id(3),Vp_id(2),Ip_id(3)]),num_point,num_dist_state);  
K6_log = reshape(K_log(:,6,[Vi_id(3),Ii_id(3),Vp_id(3),Ip_id(3)]),num_point,num_dist_state);  

K_sparse_log = K_log; 

x1_log =  xnom_log(:,[Vi_id(1),Ii_id(1)]); 
x2_log =  xnom_log(:,[Vi_id(3),Ii_id(1)]); 
x3_log =  xnom_log(:,[Vi_id(1),Ii_id(2)]); 
x4_log =  xnom_log(:,[Vi_id(2),Ii_id(2)]); 
x5_log =  xnom_log(:,[Vi_id(2),Ii_id(3)]); 
x6_log =  xnom_log(:,[Vi_id(3),Ii_id(3)]); 

phi_log = phi; 
save ('Knom_abc5','K1_log','K2_log','K3_log','K4_log','K5_log','K6_log',...
        'x1_log','x2_log','x3_log','x4_log','x5_log','x6_log','phi_log','K_sparse_log'); 





