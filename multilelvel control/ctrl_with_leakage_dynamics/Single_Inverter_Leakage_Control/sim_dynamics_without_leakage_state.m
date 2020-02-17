function dx_dt = sim_dynamics_without_leakage_state(t,x,D,Vg,Ipv)
Vi_id = 1;
Ig_id = 2;
Vo_id = 3;          

Lout  = 100e-6; 
Cin   = 15e-6;
Lleak = 5e-6;
Cout  = 10e-6; 
fsw   = 100e3; 
T     = 1/fsw;

dx_dt(1) = (Ipv - x(Vo_id)*D*x(Ig_id)*T/(4*Lleak))/Cin;
dx_dt(2) = (x(Vo_id)-Vg)/Lout; 
dx_dt(3) = (x(Vi_id)*D*x(Ig_id)*T/(4*Lleak) - x(Ig_id))/Cout; 

dx_dt = dx_dt';
end
