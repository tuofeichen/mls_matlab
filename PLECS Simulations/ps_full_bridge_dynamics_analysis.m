% phase shift full bridge dynamics analysis 
clear
Lo = 10e-6; 
Lg = 500e-6; 
Cin = 20e-6; 
Cout = 10e-6; 

load Dnom.mat;
load Knom12.mat; 
% load Knom_ab.mat

D1 = abs(D1); 
xnom_log = abs(xnom_log); 
Vin_nom = xnom_log(:,1); 
Vout_nom = xnom_log(:,1).*abs(D1)'; 



Vi_id = 1;
Vo_id = 2; 
Io_id = 3; 
Ig_id = 4; 

for ii = 1:length(Vin_nom)
    
  if D1(ii)~=0
      Vin = Vin_nom(ii); 
      Vout = Vout_nom(ii); 
      Io   = xnom_log(ii,4); 
      Ig_nom = Io; 

      A(Io_id,Vi_id) = D1(ii)/Lo; 
      A(Io_id,Vo_id) = -1/Lo; 

      A(Vi_id,Io_id) = -D1(ii)/Cin; 

      A(Vo_id,Io_id) = 1/Cout; 
      A(Vo_id,Ig_id) = -1/Cout; 

      A(Ig_id, Vo_id) = 1/Lg; 

      B = zeros(4,1); 
      B(Io_id,1) = Vin/Lo; 
      B(Vi_id,1) = -Io/Cin; 

      C = [1,0,0,0;0 0 0 1];
      D = [0 0]';
      
      
      
      opt = stepDataOptions('StepAmplitude',0.1); 
      step(ss(A,B,C,D),1/(100e3),opt);
      
  end
end
