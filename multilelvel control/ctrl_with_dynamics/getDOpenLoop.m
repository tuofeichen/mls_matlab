function Dnom = getDOpenLoop(Vin, Iin, Vg1_amp,num_point)

tstep = linspace(0,pi,num_point); % only need to calculate half of the cycle and then reflect
Pin = Vin*Iin; 
Ig1_amp = Vin*Iin*2/Vg1_amp;

Vg1 = (Vg1_amp*(sin(tstep)));
Vg2 = (Vg1_amp*(sin(tstep+2*pi/3))); 
Vg3 = (Vg1_amp*(sin(tstep-2*pi/3))); 

Ig1 = (Ig1_amp*(sin(tstep)));
Ig2 = (Ig1_amp*(sin(tstep+2*pi/3))); 
Ig3 = (Ig1_amp*(sin(tstep-2*pi/3))); 

Pg1 = Vg1.*Ig1;
Pg2 = Vg2.*Ig2; 
Pg3 = Vg3.*Ig3; 

sin_16   =  Pg1(1:num_point/6);
sin_26   =  Pg1(num_point/6+1:num_point/3);
sinf_16  = fliplr(sin_16); 
sinfi_16 = fliplr(sinf_16); 


P1 = [sin_16,sin_26-sin_16,Pin*ones(1,num_point/6),Pin-sinfi_16,sinf_16,zeros(1,num_point/6)]'; 
P2 = circshift(P1,[num_point/6,0]);  
P6 = circshift(P2,[num_point/2,0]);


P3 = circshift(P1,[num_point/2,0]);

P4 = circshift(P3,[-num_point/6,0]); 
P5 = circshift(P4,[num_point/2,0]);


V1_prop = P1'./Pg1; 
V2_prop = P2'./Pg1;

V3_prop = P3'./Pg2; 
V4_prop = P4'./Pg2;

V5_prop = P5'./Pg3; 
V6_prop = P6'./Pg3;


V1 = Vg1.*V1_prop; 
V2 = Vg1.*V2_prop; 

V3 = Vg2.*V3_prop; 
V4 = Vg2.*V4_prop; 

V5 = Vg3.*V5_prop; 
V6 = Vg3.*V6_prop; 


D1p = V1/Vin; 
D2p = V2/Vin; 
D3p = V3/Vin; 
D4p = V4/Vin; 
D5p = V5/Vin; 
D6p = V6/Vin; 

tstep = linspace(pi,2*pi,num_point);
Pin = Vin*Iin; 
Ig1_amp = Vin*Iin*2/Vg1_amp;

Vg1 = (Vg1_amp*(sin(tstep)));
Vg2 = (Vg1_amp*(sin(tstep+2*pi/3))); 
Vg3 = (Vg1_amp*(sin(tstep-2*pi/3))); 

Ig1 = (Ig1_amp*(sin(tstep)));
Ig2 = (Ig1_amp*(sin(tstep+2*pi/3))); 
Ig3 = (Ig1_amp*(sin(tstep-2*pi/3))); 

Pg1 = Vg1.*Ig1;
Pg2 = Vg2.*Ig2; 
Pg3 = Vg3.*Ig3; 

sin_16   =  Pg1(1:num_point/6);
sin_26   =  Pg1(num_point/6+1:num_point/3);
sinf_16  = fliplr(sin_16); 
sinfi_16 = fliplr(sinf_16); 


P1 = [sin_16,sin_26-sin_16,Pin*ones(1,num_point/6),Pin-sinfi_16,sinf_16,zeros(1,num_point/6)]'; 
P2 = circshift(P1,[num_point/6,0]);  
P6 = circshift(P2,[num_point/2,0]);


P3 = circshift(P1,[num_point/2,0]);

P4 = circshift(P3,[-num_point/6,0]); 
P5 = circshift(P4,[num_point/2,0]);


V1_prop = P1'./Pg1; 
V2_prop = P2'./Pg1;

V3_prop = P3'./Pg2; 
V4_prop = P4'./Pg2;

V5_prop = P5'./Pg3; 
V6_prop = P6'./Pg3;


V1 = Vg1.*V1_prop; 
V2 = Vg1.*V2_prop; 

V3 = Vg2.*V3_prop; 
V4 = Vg2.*V4_prop; 

V5 = Vg3.*V5_prop; 
V6 = Vg3.*V6_prop; 


D1n = V1/Vin; 
D2n = V2/Vin; 
D3n = V3/Vin; 
D4n = V4/Vin; 
D5n = V5/Vin; 
D6n = V6/Vin; 

tstep = linspace(0,2*pi,2*num_point);
D1 = [D1p,-D1p];
D2 = [D2p,-D2p];
D3 = [D3p,-D3p];
D4 = [D4p,-D4p];
D5 = [D5p,-D5p];
D6 = [D6p,-D6p];

D1(isnan(D1)) = 0 ; 
D2(isnan(D2)) = 0 ; 
D3(isnan(D3)) = 0 ; 
D4(isnan(D4)) = 0 ; 
D5(isnan(D5)) = 0 ; 
D6(isnan(D6)) = 0 ; 

figure; 
% subplot(3,1,1);
% plot(tstep,V1_prop); hold on; plot(tstep,V2_prop);
% ylabel('Voltage Proportion');
% subplot(3,1,2);
% plot(tstep,P1); hold on; plot(tstep,P2)
% ylabel('Power Split');
% subplot(3,1,3);

plot(tstep,D1); hold on; plot(tstep,D2);
plot(tstep,D3); hold on; plot(tstep,D4);
plot(tstep,D5); hold on; plot(tstep,D6);
ylabel('Duty Cycle / Voltage Split')

phi = tstep; 
save('Dnom','D1','D2','D3','D4','D5','D6');
Dnom = {D1,D2,D3,D4,D5,D6};

end

