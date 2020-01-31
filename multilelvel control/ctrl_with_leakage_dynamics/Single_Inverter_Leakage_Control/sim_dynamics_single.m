function dx_dt = sim_dynamics_single(t,x,D,Vg,Ipv)
Vi_id = 1;
Ig_id = 2;
Vo_id = 3; 
Il_id = 4;         

Lout  = 200e-6; 
Cin   = 10e-6;
Lleak = 10e-6;
Cout  = 5e-6; 

dx_dt(1) = (Ipv - D*x(Ig_id))/Cin;
dx_dt(2) = (x(Vo_id)-Vg)/Lout; 
dx_dt(3) = (x(Il_id) - x(Ig_id))/Cout; 
dx_dt(4) = (D*x(Vi_id) - x(Vo_id))/Lleak; 
dx_dt = dx_dt';
end
