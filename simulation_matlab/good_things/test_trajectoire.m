clear all
close all
clc

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DEFINITION DES PARAMETRES INTRINSEQUES DU ROBOT
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
d1 = 13;
d2 = 12.4;
d3 = 12.6;



x_desire = 10;
y_desire = 0;

module = sqrt(x_desire^2 + y_desire^2)
% pour que l epoint soit atteignable, il faut : module < d1+d2+d3
if module <= d1+d2+d3
    point_atteignable =1;
end

% initialisation
teta1_act = pi/2;
teta2_act = 0;
teta3_act = 0;

moteur_bloque = 1;

for mb = 1:3
    [new_teta1,new_teta2,new_teta3] = reach_point_moteur_x_bloque(x_desire,y_desire,moteur_bloque,d1,d2,d3,teta1_act,teta2_act,teta3_act)
    if new_teta1 > 1000 
        moteur_bloque = moteur_bloque +1;
    else
        disp(moteur_bloque)
        break;
    end   
end