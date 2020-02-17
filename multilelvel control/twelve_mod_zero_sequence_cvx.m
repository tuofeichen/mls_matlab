clear; 
close all; 
load VI_Curve.mat; 
n = 12; % number of converters
Vmpps = 330+ 2*randn(1,n/2);
% Vmpps = [350*ones(1,n/2-1),300];
Impps = interp1(Vs, Is, Vmpps);

Pmpps = Vmpps.*Impps; 
string_index_phi_1 = [1,2,5,6];
string_index_phi_2 = [1,2,3,4];
string_index_phi_3 = [3,4,5,6];

 Ppv = sum(Vmpps.*Impps);
 t   = 2*pi*rand;
 Vg  = 1000; 
 %Ig need to be solved,  current sharing might not be realstic
 Ig = 2*Ppv/Vg/3 ; % current of the grid is solved such that total input power is total output power 
 ii = 1;
 
%  for within a cycle
 for t = linspace(0.001,2*pi,100)

 Ig1 = (Ig*sin(t)); 
 Ig2 = (Ig*sin(t+2*pi/3)); 
 Ig3 = (Ig*sin(t-2*pi/3));
 
 Vg1 = (Vg*sin(t)); 
 Vg2 = (Vg*sin(t+2*pi/3)); 
 Vg3 = (Vg*sin(t-2*pi/3)); 
 
%  voltage constraint, the last one is the neutral point voltage 
 A_v = [ones(1,n/3),zeros(1,2*n/3),-1;
        zeros(1,n/3),ones(1,n/3),zeros(1,n/3),-1;
        zeros(1,2*n/3),ones(1,n/3),-1];
    
%  panel current constraint
 A_i = zeros(n/2,n); 
 A_i(1,1) = 1; A_i(1,5)  = 1; 
 A_i(2,2) = 1; A_i(2,6)  = 1; 
 A_i(3,3) = 1; A_i(3,11) = 1; 
 A_i(4,4) = 1; A_i(4,12) = 1; 
 A_i(5,7) = 1; A_i(5,9)  = 1; 
 A_i(6,8) = 1; A_i(6,10) = 1; 
 
%  converter power constraint
 A_pci = diag([Vmpps(1:n/6),Vmpps(n/3+1:n/2),Vmpps(1:n/6),...
               Vmpps(n/6+1:n/3), Vmpps(n/6+1:n/3),Vmpps(n/3+1:n/2)]); 
 A_pcv = diag([Ig1*ones(1,n/3),Ig2*ones(1,n/3),Ig3*ones(1,n/3)]);  
  
 b = [Vg1,Vg2,Vg3,Impps(1:n/6),Impps(n/3+1:n/2),Impps(n/6+1:n/3),zeros(1,n)]';
  
 A = [A_v, zeros(3,n); 
     zeros(n/2,n+1),A_i;
      A_pcv,zeros(n,1), -A_pci];    
  
  
x_old = zeros(n*2+1,1); 
cvx_begin
variables x(n*2+1)

minimize norm(x_old(1:n)-x(1:n))+2*norm(x(13))
subject to 
    A*x==b;
    x(n+2:end)>=0;
    abs(x(1:n+1))<= 1000;
cvx_end

if strcmp(cvx_status,'Solved')
V(:,ii) = x(1:n+1); 
I(:,ii) = x(n+2:end); 

else    
    
disp('Solver Failed');
    

end
x_old = x; 
ii = ii + 1;
    
if sin(t)>0.9
save('x_temp','x','Vmpps','Ig1','Ig2','Ig3','Vg1','Vg2','Vg3')
end
    


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

% Phase Voltage from the module
figure;
subplot(3,1,1);
plot(sum(V(1:n/3,:)));
hold on; 
plot(sum(V(n/3+1:2*n/3,:)));
plot(sum(V(2*n/3+1:end,:)));

title('Phase Voltage')
legend('\phi1','\phi2','\phi3');

subplot(3,1,2); 
plot(V(n+1,:)); %zero sequence voltage
title('Zero Sequence Voltage'); 

subplot(3,1,3); 
plot(sum(V(1:n/3,:)).*Ig1);
hold on; 
plot(sum(V(n/3+1:2*n/3,:)).*Ig2);
plot(sum(V(2*n/3+1:end,:)).*Ig3);
title('Phase Power from Converter');
legend('\phi1','\phi2','\phi3');

figure; 
subplot(2,1,1); 
bar(Vmpps.*Impps)
xlabel('String (#)'); 
ylabel('Power (W)'); 

subplot(2,1,2); 
bar([sum(Pmpps(string_index_phi_1)),sum(Pmpps(string_index_phi_2)),sum(Pmpps(string_index_phi_3)),2*sum(Pmpps)/3]);
ylabel('Max Phase Power');


