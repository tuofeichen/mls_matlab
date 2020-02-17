function dx_dt = sim_dynamics_6d(t,x,IV_curve,D,Vg)
    
% Vin = x(1); 
% Ipv = interp1(IV_curve.vs,IV_curve.iout,Vin,'linear','extrap');
% Vg = 40;
fsw = 100e3; 
tstep = 1/fsw;

Ipv = 3; % Assume current source for now 
Lout  = 100e-6;
Cin   = 10e-6;

Aiv = [-D(1),-D(3),0; 0 -D(4) -D(5); -D(2) 0 -D(6)]/Cin;
Avi = [D(1) 0 D(2); D(3) D(4) 0 ; 0 D(5) D(6)]/Lout;
A = [zeros(3,3), Aiv; Avi zeros(3,3)];

% solve for neutral point voltage 
V  = x(1:3); 
veps = 1e-6; 
D(1:2) = sign(Vg(1)+veps)*D(1:2);
D(3:4) = sign(Vg(2)+veps)*D(3:4);
D(5:6) = sign(Vg(3)+veps)*D(5:6);

Vn = (D(1)* V(1) + D(2)*V(3) + D(3)*V(1)+D(4)*V(2) + D(5)*V(2)+D(6)*V(3))/3; 
w  = [Ipv/Cin;Ipv/Cin;Ipv/Cin;-abs(Vg(1)+Vn)/Lout;-abs(Vg(2)+Vn)/Lout;-abs(Vg(3)+Vn)/Lout];
dx_dt = A*x+w; 


end