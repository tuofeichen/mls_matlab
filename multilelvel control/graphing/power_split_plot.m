close all
clear 
m_sample = 1000; 
p_sample = 6*m_sample*4; 

ha = tight_subplot(3,1,0.03,[.12 .12],[.1 .1]);

figure; 
% ax1 =subplot(3,1,1);
axes(ha(1)); 
w = 2*pi*60; 
T = 1/60;
t = linspace(0,2*T,p_sample); 
p1 = (sin(w*t)).^2; 
h(1) =  plot(t,(sin(w*t)).^2,'b');
hold on;
h(2) =  plot(t,(sin(w*t+2*pi/3)).^2,'r'); 
h(3) =  plot(t,(sin(w*t-2*pi/3)).^2,'g'); 
h(3).Color = [0 0.5  0];
title('3-\phi Power Splitting');
ylabel('Phase Power');
set(gca,'XTick',[]);
legend('\phi_1','\phi_2','\phi_3');
my_plot_setting(h);


% ax2 =subplot(3,1,2);
axes(ha(2));
% phase 1 related power 
t_split_1 = 30;
t_split_2 = 60;
t_split_3 = 90;
t_split_4 = 120;
t_split_5 = 150;

t1 = linspace(0,T*t_split_1/360,m_sample); 
m1_1 = (sin(w*t1)).^2;

t2 = linspace(T*t_split_1/360,T*t_split_2/360,m_sample); 
m1_2 = (sin(w*t2)).^2 - m1_1; 

t3 = linspace(T*t_split_2/360,T*t_split_3/360,m_sample); 
m1_3 = 0.5*ones(1,length(t3));

t4 = linspace(T*t_split_3/360,T*t_split_4/360,m_sample); 
m1_4 = fliplr(m1_2);

t5 = linspace(T*t_split_4/360,T*t_split_5/360,m_sample); 
m1_5 = fliplr(m1_1);

t6 = linspace(T*t_split_5/360,T/2,m_sample); 
m1_6 = zeros(1,length(t6));

t_phi1 = [t1,t2,t3,t4,t5,t6];
t_phi1 = [t_phi1,t_phi1+T/2,t_phi1+T,t_phi1+T*3/2];
s1_phi1 = [m1_1,m1_2,m1_3,m1_4,m1_5,m1_6];
s1_phi1 = [s1_phi1,s1_phi1,s1_phi1,s1_phi1];

h(1) = plot(t_phi1,s1_phi1,'b'); 
hold on; 
s2_phi1 = p1-s1_phi1; 
h(2) = plot(t_phi1,s2_phi1,'b--');


% phase 2 related power 
t_phi2 = t_phi1 - 1/3*T;
h(3) = plot(t_phi2,s1_phi1,'r:');
h(4) = plot(t_phi2,s2_phi1,'r');

% phase 3 related power
t_phi3 = t_phi1 + 1/3*T;
h(5) = plot(t_phi3,s1_phi1,'g--');
h(5).Color =  [0 0.5  0];
h(6) = plot(t_phi3,s2_phi1,'g:');
h(6).Color = [0 0.5  0];

% 
% legend('(S1 \rightarrow \phi_1)','(S2 \rightarrow \phi_1)',...
%     '(S3 \rightarrow \phi_2)','(S1 \rightarrow \phi_2)',...
%    '(S2 \rightarrow \phi_3)','(S3 \rightarrow \phi_3)');
ylabel('Inverter Power');
my_plot_setting(h); 
set(gca,'XTick',[]);
% lbl  = {'S1 \rightarrow \phi_1','S3 \rightarrow \phi_1',...
%         'S2 \rightarrow \phi_2','S1 \rightarrow \phi_2',...
%         'S3 \rightarrow \phi_3','S2 \rightarrow \phi_3'};

lbl  = {'I_1','I_2',...
    'I_4','I_3',...
    'I_6','I_5'};
% legend(lbl); 
h = legendflex(h,lbl,'nrow',1,'anchor', [3 3], 'buffer', [-4 -3]); 
set(h,'linewidth',2)
ylim([-0.001,0.8]);

% right chronical order 
% ax3 =subplot(3,1,3) ;

axes(ha(3));

s1_phi2 = interp1(t_phi2(1:5:end),s2_phi1(1:5:end),t_phi1);

h(1)  = plot(t_phi1,s1_phi1,'b'); 
hold on; 
h(2) = plot(t_phi1,s1_phi2,'r'); 

hold on; 
h(3) = plot(t_phi1,s1_phi1 + s1_phi2,'k'); 
% legend('S1 \rightarrow \phi_1','S1 \rightarrow \phi_2','S1 Total'); 
legend('I_1','I_3','S_1'); 
my_plot_setting(h); 
ylim([-0.001,0.6]);
% linkaxes([ax1,ax2,ax3],'x')
linkaxes(ha,'x')
xlim([T/2,T]);
xlabel('Time (s)'); 
ylabel('String Power'); 

x0 = 10; 
y0 = 10; 
width = 800; 
height = 600; 
set(gcf,'position',[x0,y0,width,height])

% end
