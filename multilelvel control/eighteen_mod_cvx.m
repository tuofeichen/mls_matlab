clear; close all; 
n = 18; % number of converters
Vmpps = [1:3,1:3,1:3];%0.5+ 0*randn(1,n/2);
Impps = [1:3,1:3,1:3];%1  + 0*randn(1,n/2);

 Ppv = sum(Vmpps.*Impps);
 t   = 2*pi*rand;
 Vg  = 10; 
 %Ig need to be solved,  current sharing might not be realstic
 Ig = 2*Ppv/Vg/3 ;  
 ii = 1;
 
 for t = linspace(0.001,2*pi,100)

 Ig1 = (Ig*sin(t)); 
 Ig2 = (Ig*sin(t+2*pi/3)); 
 Ig3 = (Ig*sin(t-2*pi/3));
 
 Vg1 = (Vg*sin(t)); 
 Vg2 = (Vg*sin(t+2*pi/3)); 
 Vg3 = (Vg*sin(t-2*pi/3)); 
 
%  voltage constraint
 A_v = [ones(1,n/3),zeros(1,2*n/3);
        zeros(1,n/3),ones(1,n/3),zeros(1,n/3);
        zeros(1,2*n/3),ones(1,n/3)];
    
%  grid power constraint
 A_pg = [Vmpps(1:n/6),Vmpps(n/3+1:n/2),zeros(1,2*n/3);
        zeros(1,n/3),Vmpps(1:n/3),zeros(1,n/3);
        zeros(1,2*n/3),Vmpps(n/6+1:n/2)];
    
%  panel current constraint
 A_i = zeros(n/2,n); 
 A_i(1,1) = 1; A_i(1,1+n/3) = 1; 
 A_i(2,2) = 1; A_i(2,2+n/3) = 1; 
 A_i(3,3) = 1; A_i(3,3+n/3) = 1; 
 A_i(4,4) = 1; A_i(4,4+2*n/3) = 1; 
 A_i(5,5) = 1; A_i(5,5+2*n/3) = 1; 
 A_i(6,6) = 1; A_i(6,6+2*n/3) = 1; 
 A_i(7,10) = 1; A_i(7,10+n/6) = 1; 
 A_i(8,11) = 1; A_i(8,11+n/6) = 1; 
 A_i(9,12) = 1; A_i(9,12+n/6) = 1; 
 
%  converter power constraint
 A_pci = diag([Vmpps(1:n/6),Vmpps(n/3+1:n/2),Vmpps(1:n/6),...
               Vmpps(n/6+1:n/3), Vmpps(n/6+1:n/3),Vmpps(n/3+1:n/2)]); 
 A_pcv = diag([Ig1*ones(1,n/3),Ig2*ones(1,n/3),Ig3*ones(1,n/3)]);  
  
 b = [Vg1,Vg2,Vg3,Vg1*Ig1,Vg2*Ig2,Vg3*Ig3,Impps(1:n/6),Impps(n/3+1:n/2),Impps(n/6+1:n/3),zeros(1,n)]';
  
 A = [A_v, zeros(3,n); 
      zeros(3,n),A_pg;
      zeros(n/2,n),A_i;
      A_pcv, -A_pci];
    
  
x_old = zeros(n*2,1); 
cvx_begin
variables x(n*2)

minimize norm(x_old-x)
subject to 
    A*x==b;
    x(n+1:end)>=0;
    abs(x(1:n))<= 5;
cvx_end

if cvx_status == 'Solved'
V(:,ii) = x(1:n); 
I(:,ii) = x(n+1:end); 

else    
    
disp('Solver Failed');
    

end
x_old = x; 
ii = ii + 1;
    
    


end
 
Ig1 = Ig*sin(linspace(0.001,2*pi,100));
Ig2 = Ig*sin(linspace(0.001,2*pi,100)+2*pi/3); 
Ig3 = Ig*sin(linspace(0.001,2*pi,100)-2*pi/3); 
Vg1 = Vg*sin(linspace(0.001,2*pi,100)); 
Vg2 = Vg*sin(linspace(0.001,2*pi,100)+2*pi/3); 
Vg3 = Vg*sin(linspace(0.001,2*pi,100)-2*pi/3); 


figure;
subplot(3,1,1);
% plot(sum(V(1:6,:)))
% hold on; plot(sum(V(7:12,:)))
% hold on; plot(sum(V(13:18,:)))
plot(V(3,:).*Ig1); hold on; plot(V(9,:).*Ig2); 
hold on; plot(V(3,:).*Ig1+V(9,:).*Ig2); 

subplot(3,1,2); 
plot(V(1,:).*Ig1); hold on; plot(V(7,:).*Ig2); 
hold on; plot(V(1,:).*Ig1+V(7,:).*Ig2); 

subplot(3,1,3);
plot(V(2,:).*Ig1); hold on; plot(V(8,:).*Ig2); 
hold on; plot(V(2,:).*Ig1+V(8,:).*Ig2); 

