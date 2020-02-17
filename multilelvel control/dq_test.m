% dq transformation test
close all; 
theta = linspace(0,2*pi,100); 

id = 1; iq = 0;
Iref = [id,iq]';
Kc = sqrt(2/3)*[1,-1/2,-1/2; 0, sqrt(3)/2,-sqrt(3)/2; 1/sqrt(2)*ones(1,3)]; 
    
for ii = 1:length(theta)
   Kp = [cos(theta(ii)),sin(theta(ii)); -sin(theta(ii)), cos(theta(ii))];
   Iref_ab = inv(Kp)*Iref; 
   Iref_ab0 = [Iref_ab;0]; % zero meaning no unbalanced current
   Iref_abc = inv(Kc)*Iref_ab0; 
   Va(ii) = Iref_abc(1); 
   Vb(ii) = Iref_abc(2); 
   Vc(ii) = Iref_abc(3); 
    
end

figure; 
subplot(3,1,1);
plot(theta,Va);hold on; plot(theta,Vb); hold on; plot(theta,Vc)
title('Voltage'); 

id = 1; iq = 1;
Iref = [id,iq]';
Kc = sqrt(2/3)*[1,-1/2,-1/2; 0, sqrt(3)/2,-sqrt(3)/2; 1/sqrt(2)*ones(1,3)]; 
    
for ii = 1:length(theta)
    
   Kp = [cos(theta(ii)),sin(theta(ii)); -sin(theta(ii)), cos(theta(ii))];
   Iref_ab = inv(Kp)*Iref; 
   Iref_ab0 = [Iref_ab;0]; % zero meaning no unbalanced current
   Iref_abc = inv(Kc)*Iref_ab0; 
   Ia(ii) = Iref_abc(1); 
   Ib(ii) = Iref_abc(2); 
   Ic(ii) = Iref_abc(3); 
    
end

subplot(3,1,2);
plot(theta,Ia);hold on; plot(theta,Ib); hold on; plot(theta,Ic)
title('Current'); 

subplot(3,1,3); 
plot(Va.*Ia); hold on; plot(Vb.*Ib); hold on; plot(Vc.*Ic)
title('Power'); 



