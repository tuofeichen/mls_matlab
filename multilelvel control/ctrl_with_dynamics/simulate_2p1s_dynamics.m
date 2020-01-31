clear all; 
close all; 

load SPICE_IV.mat
Vg = 45; 

Vin = 41; 
I1 = 0; I2 = 0; 
Vo1 = 2*Vg/3; Vo2 =Vg/3; 
Vo1 = Vg/2; Vo2 = Vg/2;
x0 = [Vin;I1;I2;Vo1;Vo2];

solver_options = odeset('RelTol',1e-9);

[t,x] = ode45(@(t,x) sim_dynamics(t,x,IV_curve),linspace(0,10e-3,1000),x0,solver_options);
 
Vin = x(:,1); 
I1 = x(:,2); 
I2 = x(:,3); 
Vo1 = x(:,4); 
Vo2 = x(:,5); 

figure;
subplot(3,1,1)
h = plot(t,Vin);
title('Vin'); 
my_plot_setting(h); 

subplot(3,1,2); 
h = plot(t,I1,t,I2); 
hold on; 
h(3) = plot(t,(I1+I2)/2);
my_plot_setting(h); 

legend('I1','I2','Ig'); 

subplot(3,1,3); 
h = plot(t,Vo1,t,Vo2); my_plot_setting(h); 
legend('Vo1', 'Vo2'); 




