clear; 

 n = 12; % 12 converter system 
 Vmpps = 0.5+ 0.01*randn(1,6);
 Impps = 1  + 0.01*randn(1,6);
 Ppv = sum(Vmpps.*Impps)
 t   = 2*pi*rand;
 Vg  = 2; 
 
 %Ig need to be solved,  current sharing might not be realstic
 Ig = 2*Ppv/Vg/3 ; 
 
 Ig1 = (Ig*sin(t)); 
 Ig2 = (Ig*sin(t+2*pi/3)); 
 Ig3 = (Ig*sin(t-2*pi/3));
 
 Vg1 = (Vg*sin(t)); 
 Vg2 = (Vg*sin(t+2*pi/3)); 
 Vg3 = (Vg*sin(t-2*pi/3)); 
 
%  voltage constraint
 A_v = [ones(1,4),zeros(1,8);
        zeros(1,4),ones(1,4),zeros(1,4);
        zeros(1,8),ones(1,4)];
%  grid power constraint
 A_pg = [Vmpps(1),Vmpps(4),Vmpps(5),Vmpps(6),zeros(1,8)
        zeros(1,4),Vmpps(1),Vmpps(2),Vmpps(3),Vmpps(4),zeros(1,4);
        zeros(1,8),Vmpps(2),Vmpps(3),Vmpps(5),Vmpps(6),];
    
%  panel current constraint
 A_i = zeros(n/2,n); 
 A_i(1,1) = 1; A_i(1,5) = 1; 
 A_i(2,6) = 1; A_i(2,9) = 1; 
 A_i(3,7) = 1; A_i(3,10) = 1; 
 A_i(4,2) = 1; A_i(4,8) = 1; 
 A_i(5,3) = 1; A_i(5,11) = 1; 
 A_i(6,4) = 1; A_i(6,12) = 1; 
 
%  converter power constraint
 A_pci = diag([Vmpps(1),Vmpps(4),Vmpps(5),Vmpps(6),Vmpps(1),Vmpps(2),...
     Vmpps(3),Vmpps(4),Vmpps(2),Vmpps(3),Vmpps(5),Vmpps(6)]); 
 A_pcv = diag([Ig1*ones(1,4),Ig2*ones(1,4),Ig3*ones(1,4)]);  
 
 A = [A_v, zeros(3,n); 
      zeros(3,n),A_pg;
      zeros(n/2,n),A_i;
      A_pcv, -A_pci];
      
 
 b = [Vg1,Vg2,Vg3,Vg1*Ig1,Vg2*Ig2,Vg3*Ig3,Impps,zeros(1,n)]';
 cond(A);
 rank(A);
 
 
 setpoint = pinv(A)*b;
 norm(A*setpoint-b)
%  x = sym('setpoint',[24,1]);
%  solve([A*x==b],x,Ig)

