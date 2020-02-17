function D = PandO(Vpv,Ipv)
%#codegen
persistent Dprev Pprev Vprev Iprev cnt

% initial guess of the 
if isempty(Dprev)
    Dprev = 0.7; 
    Vprev = 300;
    Iprev = 5; 
    Pprev = 2000;  
    cnt = 1;
end
     
method = 2; 
Ppv = Vpv*Ipv; 
% % 
% if abs(Vpv-Vprev)<0.1
%     D = Dprev;
%     return;
% end

cnt = cnt + 1;
if mod(cnt,2000)~=0
    D=Dprev;
    return
end
    
deltaD = 0.001; %disturbed quantity

if method == 1 % Perturb and Observe
if  Ppv > Pprev
    if Vpv>Vprev
        D = Dprev - deltaD;
    else
        D = Dprev + deltaD;
    end
else
    if Vpv>Vprev
        D = Dprev + deltaD;
    else
        D = Dprev - deltaD;
    end 
end

else if method == 2
   dV = Vpv - Vprev; 
   dI = Ipv - Iprev; 
        if dV == 0
           if dI>0
               D = Dprev-deltaD; 
           else
               D = Dprev+deltaD; 
           end
        else 
           if (dI/dV) > -Ipv/Vpv
               D = Dprev-deltaD; 
           else
               D = Dprev + deltaD; 
           end
        end
    end
end


if D>1
    D = 1; 
else if D<0
        D= 0; 
    end
end

Dprev = D; 
Pprev = Ppv; 
Vprev = Vpv; 
Iprev = Ipv; 
end