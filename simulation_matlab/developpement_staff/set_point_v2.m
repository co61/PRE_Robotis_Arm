close all
clear all
clc

%paramètres physiques du robot
d1 = 13;
d2 = 12.4;
d3 = 12.6;

teta1_max = 90;
teta1_min = -90;

teta2_max = 90;
teta2_min = -90;

teta2_max = 90;
teta2_min = -90;

pas = 0.01;
t = 0:pas:2*pi-pas;



%on doit trouver les teta en fonction du temps qui nous permettre de tracer
%une ligne droite verticale y = constante
%a chaque fois que l'utilisateur touchera le joystick, on va venir générer
%le vecteur contenant les angles au cours du temps à donner au robot

x_constant = 20;% cm
dh = 0.5;
point_desire = [35 0];
x_desire = point_desire(1,1);
y_desire = point_desire(1,2);

if (x_desire)^2+(y_desire)^2 > (d1+d2+d3)^2 %d1 + d2 +d3 est le rayon du robot
    disp('imossible de se rendre à ce point car en dehors du cercle accesible par le  robot')
    in_circle = 1;
    
else
    in_circle = 0;
end

figure,grid
title('modélisation du robot 3 axes dans le plan')
axis([-(d1+d2+d3) (d1+d2+d3) -(d1+d2+d3) (d1+d2+d3)])
hold on
condition =0;
temps =1;
while (condition == 0 && in_circle == 0)
    if temps == 1
        teta1(temps)=deg2rad(90);
        teta2(temps)=deg2rad(90);
        teta3(temps)=deg2rad(90);
        hauteur_actuelle = (d1*sin(teta1(1))+d2*sin(teta2(1)) + d3*sin(teta3(1)));
        
        P1 = d1*cos(teta1) + i* d1*sin(teta1);
        P2 = d1*cos(teta1)+ d2*cos(teta2) + i* (d1*sin(teta1)+d2*sin(teta2));
        P3 = d1*cos(teta1)+ d2*cos(teta2) + d3*cos(teta3) + i* (d1*sin(teta1)+d2*sin(teta2) + d3*sin(teta3));
        temps = temps +1;
    else % temps != 1
       
        fun = @root_2d_v2; %fonction que j'ai défini dans une fonction matlab
        teta0 = [deg2rad(0),deg2rad(0),deg2rad(0)];
        [new_teta,fval,exitflag1,output] = fsolve(fun,teta0);
        
      
        %definition des trois segements du robot
        % permiere partie
        segment1P1(1,1) = 0;
        segment1P1(2,1) = real(P1);
        segment1P2(1,1) = 0;
        segment1P2(2,1) = imag(P1);
        % 2eme partie
        segment2P1(1,1) = segment1P1(2,1);
        segment2P1(2,1) = real(P2);
        segment2P2(1,1) = segment1P2(2,1);
        segment2P2(2,1) = imag(P2);
        % 3eme partie
        segment3P1(1,1) = segment2P1(2,1);
        segment3P1(2,1) = real(P3);
        segment3P2(1,1) = segment2P2(2,1);
        segment3P2(2,1) = imag(P3);
        
        %affichage
        segment1(temps) = line(segment1P1,segment1P2,'Color','b');
        segment2(temps) = line(segment2P1,segment2P2,'Color','r');
        segment3(temps) = line(segment3P1,segment3P2,'Color','g');
        
        segment1(temps-1).delete();
        segment2(temps-1).delete();
        segment3(temps-1).delete();
        
    end
    pause(0.01)
end









   