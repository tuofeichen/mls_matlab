function Ic_d = solvePowerFraction(Vs,Is,Vd,Vg_phi,N)

Id = interp1(Vs,Is,Vd);
Pds = Vd.*Id; 
Pphi_frac = Vg_phi.^2/(sum(Vg_phi.^2)); 
Pdphi = sum(Pds) *Pphi_frac; 

Ps_frac(4) =  0.5086; %constrained the system to quickly solve
Ps_frac(3) = (Pdphi(2)-Ps_frac(4)*Pds(2))/Pds(1);
Ps_frac(2) = (Pdphi(2)+Pdphi(1)-Pds(1)-Ps_frac(4)*Pds(2))/Pds(3);
Ps_frac(1) = 1 - Ps_frac(3); 
Ps_frac(5) = 1 - Ps_frac(4); 
Ps_frac(6) = 1 - Ps_frac(2); 

Ps_frac_mat = [Ps_frac(1),0,0;
          0,0,Ps_frac(2);
          Ps_frac(3),0,0;
          0,Ps_frac(4),0
          0,Ps_frac(5),0
          0,0,Ps_frac(6)
          ];
      
Ic_d =  Ps_frac_mat *Id;
end
