function du = mpcUpdate(D,dx,x,Vpv,T,Lout,Cin,Vg,Vn,Ipv,Dnom)

Ig = x(4:6); 


Aiv = [-D(1),-D(3),0; 0 -D(4) -D(5); -D(2) 0 -D(6)]/Cin;
Avi = [D(1) 0 D(2); D(3) D(4) 0 ; 0 D(5) D(6)]/Lout;
A = [zeros(3,3), Aiv; Avi zeros(3,3)];

Bv = [-Ig(1) 0 -Ig(2) 0 0 0; 
     0 0 0 -Ig(2) -Ig(3) 0; 
     0 -Ig(1) 0 0 0 -Ig(3)]/Cin;

Bi = [Vpv Vpv 0   0   0  0; 
       0  0  Vpv Vpv  0  0;
       0  0  0   0  Vpv Vpv]/Lout;
   
B = [Bv; Bi];
Vn = 0; 
w  = [Ipv/Cin;Ipv/Cin;Ipv/Cin;-(Vg(1)+Vn)/Lout;-(Vg(2)+Vn)/Lout;-(Vg(3)+Vn)/Lout];
V  = x(1:3);% Extract PV Voltage to update Vn if necessary

dx_dt_auto = A*x+w; % should allow this 
% 
% [~,min_index] = min(Dnom); 
% [~,max_index] = max(Dnom); 
% [~,zero_index] = min(abs(Dnom)); 
% 
% if min_index == max_index
% cvx_begin quiet
% variables du(6)
% minimize norm (dx-dx_dt_auto*T - B*du*T)
% subject to 
%     D+du>=-1
%     D+du<=1
% cvx_end
%     
% else
cvx_begin quiet
variables du(6)
minimize norm (dx-dx_dt_auto*T - B*du*T) + norm(D+du- Dnom) 
subject to 
    D+du>=-1
    D+du<=1
cvx_end
% end

end

