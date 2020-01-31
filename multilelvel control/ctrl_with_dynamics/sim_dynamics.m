function dx_dt = sim_dynamics(t,x,IV_curve,D)
    
% Vin = x(1); 
% Ipv = interp1(IV_curve.vs,IV_curve.iout,Vin,'linear','extrap');

Vo = 40;
Ipv = 4; % Assume current source for now 

Lout  = 300e-6;
Cin   = 20e-6;
Cout  = 10e-6;


D1 = D(1); D2 = D(2); 
%D1 = 0.4; D2 = 0.6;
A = [0, -D1/Cin -D2/Cin 0 ; 
     D1/Lout 0   0 -1/Lout ;
     D2/Lout 0   0  1/Lout ; 
     0  0.5/Cout  -0.5/Cout  0]; 
 
% B = [-Io/Cin,-Io/Cin; Vin/Lout 0 ;0 Vin/Lout; 0 0;];

w = [Ipv/Cin,0,-Vo/Lout,0]';

dx_dt = A*x + w; 

% discontinuity of the freewheeling diode 
if x(2) <= 0 && dx_dt(2)<=0
    dx_dt(2) = 0; 
    %dx_dt(3) = 0; 
end

if x(3) <= 0 && dx_dt(3)<=0
    dx_dt(3) = 0; 
    %dx_dt(2) = 0; 
end


end