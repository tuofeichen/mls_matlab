function Vn = getVn(D,Vgs,x)

V = x(1:3); 
Vn = (D(1)* V(1) + D(2)*V(3) + D(3)*V(1)+D(4)*V(2) + D(5)*V(2)+D(6)*V(3))/3; 

end