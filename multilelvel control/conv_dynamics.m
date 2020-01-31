function dx_dt = conv_dynamics(t,x,D,Vg,Ipv)

L = 1e-3; 
C = 1e-5;

dx_dt(1) = 1/C*(Ipv(1) - D(1)*x(3)); 
dx_dt(2) = 1/C*(Ipv(2) - D(2)*x(3)); 
dx_dt(3) = 1/L*(Vg - D(1)*x(1)-D(2)*x(2)); 
dx_dt = dx_dt';
end