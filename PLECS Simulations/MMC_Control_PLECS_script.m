%%%% Some constants
clear
close all; 
V_gpeak = 120; % peak grid phase voltage (V)
I_pv = 10;     % PV current
f_g = 60;      % grid frequency (Hz)
fsw = 200e3; 
L_g = 500e-6;  % Grid equivalent inductance (Henries)
R_g = 0.01;    % Grid equivalent resitance (ohms)


C_pv = 20e-6; 
Cbus1 = C_pv;
Cbus_init1 = 40;
Cbus2 =  C_pv; 
Cbus_init2 = 60;
Cbus3 =  C_pv; 
Cbus_init3 = 70;

Cout = 15e-6;%e-6;%20e-6; 
Lout = 15e-6; 
Lleak = 1e-6;%e-6; 

% load control gain scheduling
% load Knom_ab.mat
% load Knom_ab.mat
load Knom_ifb_ab.mat
% load Knom_iso_buck.mat
load Dnom.mat
nom.D = [D1;D2;D3;D4;D5;D6]';
nom.K = K_log;
% load('Knom12.mat'); 
% nom.K12 = K_log;
% load('Knom13.mat');
% nom.K13 = K_log; 
nom.phi = phi; 
nom.id  = 1:length(K_log); 
nom.x   = xnom_log; 
nom.fsw = fsw; 
sim('MMC_Control_PLECS_IFB_diode_ab0.slx')

