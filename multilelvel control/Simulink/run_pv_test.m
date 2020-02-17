clear; 
cnt = 1; 
for duty = 0.05:0.05:0.99
set_param('pv_test/Duty','value',num2str(duty));
sim('pv_test');
I(cnt) = I_PV.Data(end); 
V(cnt) = V_pv.Data(end); 
cnt = cnt + 1; 
end
        