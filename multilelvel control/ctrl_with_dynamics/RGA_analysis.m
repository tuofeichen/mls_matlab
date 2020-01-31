clear
close all
% assume a nominal condition 
Lout = 400e-6; 
Cout = 5e-6;
Cin= 10e-6; 
Vin = 30; 
Vout = 40; 
Io = 3; 
D1 = 2/3; 
D2 = 2/3; 

A = [0, -D1/Cin -D2/Cin 0 ; 
     D1/Lout 0   0 -1/Lout ;
     D2/Lout 0   0  1/Lout ; 
     0  0.5/Cout  -0.5/Cout  0]; 
 
B = [-Io,-Io; Vin 0 ;0 Vin; 0 0 ;];

Cc = ctrb(A,B); 
rank(Cc)

%C =[1 0 0 0;  0 0 0 1;];
C = eye(size(A)); %full state feedback
D = zeros(size(B)); 
Gtf = ss(A,B,C,D);
%s   =  tf('s'); 
%Gtf   = C*((s*eye(size(A))-A)\B); % DC gain of the plant


K = place(A,B,1e4*[-0.001+i,-0.001-i,-0.002+i,-0.002-i]);%place the poles here
Gcl = inv(eye(4) + Gtf*K)*Gtf*K;

RGA =  G.*pinv(G).'; % this pinv need to be taken with a grain of salt 

s = j * linspace(0,5e3*2*pi,10000); % j*3.7e3*2*pi;

% s = j*1e3*2*pi;
for ii = 1:length(s)
G = pinv(s(ii)*eye(size(A))-A)*B; %DC gain of the plant
RGA = G.*pinv(G).';
L11(ii) = RGA(1,1);
L22(ii) = RGA(2,2); 
L41(ii) = RGA(4,1);
L42(ii) = RGA(4,2); 
end

figure; 
subplot(2,1,1); 
h(1) = plot(abs(s)/(2*pi),abs(L11)); 
hold on; 
% h(2) = semilogy(abs(s)/(2*pi),abs(L22));
h(2) = plot(abs(s)/(2*pi),abs(L42)); 
grid on

%h(3) = semilogy(abs(s)/(2*pi),abs(L51));
subplot(2,1,2);
h(3) = semilogy(abs(s)/(2*pi),angle(L11));
hold on
h(4) = semilogy(abs(s)/(2*pi),angle(L41));
my_plot_setting(h); 


