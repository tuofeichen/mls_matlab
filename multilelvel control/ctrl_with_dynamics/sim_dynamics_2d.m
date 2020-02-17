function dx_dt = sim_dynamics_2d(t,x,IV_curve,D,Vg)
    
%Vin = x(1); 
%Ipv = interp1(IV_curve.vs,IV_curve.iout,Vin,'linear','extrap');

% Vg = 40;
Ipv = 4; % Assume current source for now 

Lout  = 300e-6;
Cin   = 20e-6;

D1 = D(1); D2 = D(2); 

% State Equation (add dummy state for the pv current input)
A = [0, -D1/Cin-D2/Cin; 
     D1/Lout+D2/Lout, 0];
     
% B = [-Io/Cin,-Io/Cin; Vin/Lout, Vin/Lout;];
% B = [-Io/Cin,-Io/Cin; Vin/Lout 0 ;0 Vin/Lout; 0 0;];

w = [Ipv/Cin;-Vg/Lout];

dx_dt = A*x + w; 

% discontinuity of the freewheeling diode 
if x(2) <= 0 && dx_dt(2)<=0
    dx_dt(2) = 0; 
    %dx_dt(3) = 0; 
end
% 
% if x(3) <= 0 && dx_dt(3)<=0
%     dx_dt(3) = 0; 
%     %dx_dt(2) = 0; 
% end


end