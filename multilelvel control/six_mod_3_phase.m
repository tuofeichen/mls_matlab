clear; 
load VI_Curve.mat
% This is actually too small/too constrained 
 Vmpps = [300,300,300]; %0.5+ 0.01*randn(1,3);
 Impps = interp1(Vs,Is,Vmpps); %1  + 0.01*randn(1,3);
 Vg = 300;
 Ptot = sum(Vmpps.*Impps); 
 Ig =  2*Ptot/Vg/3;
 x_old = zeros(12,1); 
 cnt = 1; 
 for t = linspace(0,2*pi,100)
 Vg1 = (Vg*sin(t)); 
 Vg2 = (Vg*sin(t+2*pi/3)); 
 Vg3 = (Vg*sin(t-2*pi/3)); 
 Ig1 = Ig*sin(t);
 Ig2 = Ig*sin(t+2*pi/3); 
 Ig3 = Ig*sin(t-2*pi/3); 

 
 
 A_pwr_I = -diag([Vmpps(1),Vmpps(3),Vmpps(1),Vmpps(2),Vmpps(2),Vmpps(3)]);
 A_pwr_V = diag([Ig1,Ig1,Ig2,Ig2,Ig3,Ig3]); 
 
 A = [1 1 0 0 0 0  zeros(1,6);
      0 0 1 1 0 0  zeros(1,6);
      0 0 0 0 1 1  zeros(1,6);
      A_pwr_V,A_pwr_I;
      zeros(1,6), 1,0,1,0,0,0;
      zeros(1,6), 0,0,0,1,1,0,;
      zeros(1,6), 0,1,0,0,0,1;];
  
  b = [Vg1,Vg2,Vg3 , zeros(1,6),Impps(1),Impps(2),Impps(3)]';
  x = pinv(A)*b;
% cvx_begin
% variables x(12)
% 
% minimize norm(x(1:6)-x_old(1:6))
% subject to 
%     A*x==b;
%     x(7:end)>=0;
% cvx_end

  x_log(:,cnt) = x; 
  Vg_log(:,cnt) = [Vg1,Vg2,Vg3]';
  x_old = x; 
  cnt = cnt + 1; 
 end
 
Ig1 = Ig*sin(linspace(0.001,2*pi,100));
Ig2 = Ig*sin(linspace(0.001,2*pi,100)+2*pi/3); 
Ig3 = Ig*sin(linspace(0.001,2*pi,100)-2*pi/3); 
Vg1 = Vg*sin(linspace(0.001,2*pi,100)); 
Vg2 = Vg*sin(linspace(0.001,2*pi,100)+2*pi/3); 
Vg3 = Vg*sin(linspace(0.001,2*pi,100)-2*pi/3); 

% Power Distribution
figure;
subplot(3,1,1);

% plot(sum(V(1:6,:)))
% hold on; plot(sum(V(7:12,:)))
% hold on; plot(sum(V(13:18,:)))
plot(V(1,:).*Ig1); hold on; plot(V(5,:).*Ig2); 
hold on; plot(V(1,:).*Ig1+V(5,:).*Ig2); 
title('String 1 Power');
legend('C1 Power','C5 Power','Total Power');

subplot(3,1,2); 
plot(V(7,:).*Ig2); hold on; plot(V(9,:).*Ig3); 
hold on; plot(V(7,:).*Ig2+V(9,:).*Ig3); 
title('String 3 Power');
legend('C7 Power','C9 Power','Total Power');

subplot(3,1,3);
plot(V(3,:).*Ig1); hold on; plot(V(11,:).*Ig3); 
hold on; plot(V(3,:).*Ig1+V(11,:).*Ig3); 
title('String 5 Power');
legend('C3 Power','C11 Power','Total Power');
%  x = sym('setpoint',[13,1]);
%  
%  nonlinear_systems = [x(1)*x(13)*abs(sin(t))       == x(7) *Vmpps(1);
%                       x(2)*x(13)*abs(sin(t+2*pi/3))== x(8) *Vmpps(1);
%                       x(3)*x(13)*abs(sin(t-2*pi/3))== x(9) *Vmpps(3);
%                       x(4)*x(13)*abs(sin(t))       == x(10)*Vmpps(2);
%                       x(5)*x(13)*abs(sin(t+2*pi/3))== x(11)*Vmpps(3);
%                       x(6)*x(13)*abs(sin(t-2*pi/3))== x(12)*Vmpps(2);];
%  
%    
%  sol = solve([A*x==b,nonlinear_systems],x)
%  
%  
% double(sol.setpoint1)
% double(sol.setpoint2)
% double(sol.setpoint3)
% double(sol.setpoint4)
% double(sol.setpoint5)
% double(sol.setpoint6)
% double(sol.setpoint7)
% double(sol.setpoint8)
% double(sol.setpoint9)
% double(sol.setpoint10)
% double(sol.setpoint11)
% double(sol.setpoint12)
% double(sol.setpoint13)

