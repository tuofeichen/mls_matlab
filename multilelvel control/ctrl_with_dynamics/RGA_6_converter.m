clear
close all
%% consider the following topology
% P1    P2   P3
% |     |    |
% C1-S1-C3   |
% |     |    |
% |    C4-S2-C5   
% |          |
% C2---S3----C6


%assume a nominal condition 
Lout = 400e-6; 
% Cout = 5e-6;
Cin  = 20e-6; 
Vin  = 30; 



D  = [1 1 0 0.5 0.5 0]';

Io = 3; 
Vg = [Vin;0.5*Vin;0.5*Vin;];
Ig = [Io,0.5*Io, 0.5*Io]';



Aiv = [-D(1),-D(3),0; 0 -D(4) -D(5); -D(2) 0 -D(6)]/Cin;
Avi = [D(1) 0 D(2); D(3) D(4) 0 ; 0 D(5) D(6)]/Lout;
A = [zeros(3,3), Aiv; Avi zeros(3,3)];

Bv = [-Ig(1) 0 -Ig(2) 0 0 0; 
     0 0 0 -Ig(2) -Ig(3) 0; 
     0 -Ig(1) 0 0 0 -Ig(3)]/Cin;

Bi = [Vin Vin 0   0   0  0; 
       0  0  Vin Vin  0  0;
       0  0  0   0  Vin Vin]/Lout;
   
B = [Bv; Bi]; 


Cc = ctrb(A,B); 
rank(Cc)

% C = [1 0 0 0 0; 0 1 0 0 0; ];%pick the state we want to control 
s = 0; 
G = pinv(s*eye(size(A))-A)*B; %DC gain of the plant
RGA = G.*pinv(G).';

s = j * linspace(0,5e3*2*pi,10000); % j*3.7e3*2*pi;


% s = j*1e3*2*pi;
for ii = 1:length(s)
G = pinv(s(ii)*eye(size(A))-A)*B; %DC gain of the plant

RGA = G.*pinv(G).';

L11(ii) = RGA(1,1);
L22(ii) = RGA(2,2); 
L52(ii) = RGA(5,2);
L41(ii) = RGA(4,1);

 end

figure; 
subplot(2,1,1); 
h(1) = plot(abs(s)/(2*pi),abs(L11)); 
hold on; 
% h(2) = semilogy(abs(s)/(2*pi),abs(L22));
h(2) = plot(abs(s)/(2*pi),abs(L52)); 
grid on

%h(3) = semilogy(abs(s)/(2*pi),abs(L51));
subplot(2,1,2);
h(3) = semilogy(abs(s)/(2*pi),angle(L11));
hold on
h(4) = semilogy(abs(s)/(2*pi),angle(L52));
my_plot_setting(h); 


