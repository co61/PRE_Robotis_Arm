close all
clear all
clc

moteur_bloque = 1;
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

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%conditions initiales des angles du robot
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

teta1_init=deg2rad(90);
teta2_init=deg2rad(0);
teta3_init=deg2rad(0);

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%coordonnées du point souhaité
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

point_desire = [-10 5];
x_desire = point_desire(1,1);
y_desire = point_desire(1,2);

%affichage du point désiré
figure,grid
plot(x_desire,y_desire,'x')



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% tracage des cercles représentant la zone atteignable angle 1 bloqué
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
title('modélisation du robot 3 axes dans le plan')
axis([-(d1+d2+d3) (d1+d2+d3) -(d1+d2+d3) (d1+d2+d3)])
hold on

%espace atteignable
viscircles([0,0],d1+d2+d3)

%moteur1 bloqué
p1_x = d1*cos(teta1_init);
p1_y = d1*sin(teta1_init);
viscircles([p1_x,p1_y],d2+d3,'color','blue')

point_atteignable = 0;
%vérifier que le point est atteignable en bloquant le moteur1
if (x_desire - p1_x)^2+(y_desire - p1_y)^2 > (d2+d3)^2
    disp('Impossible de se rendre à ce point car en dehors du cercle accesible par le  robot en bloquant le moteur 1')
    point_atteignable = 1;
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% représentation du robot dans sa position initial
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% calcul des différents points
P1 = d1*cos(teta1_init) + i* d1*sin(teta1_init);
P2 = d1*cos(teta1_init)+ d2*cos(teta2_init) + i* (d1*sin(teta1_init)+d2*sin(teta2_init));
P3 = d1*cos(teta1_init)+ d2*cos(teta2_init) + d3*cos(teta3_init) + i* (d1*sin(teta1_init)+d2*sin(teta2_init) + d3*sin(teta3_init));

%fonction que j'ai définit dans une fonction matlab pour ne pas surcharger
%le code
affichage_robot(P1,P2,P3);

% on fait le reste que si le point est atteignable
if point_atteignable ~= 1
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % résolution du système afin fe trouver les angles
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
   
    
    fun = @root; %fonction que j'ai défini dans une fonction matlab
    teta0 = [deg2rad(0),deg2rad(0)];
    [new_teta,fval,exitflag1,output] = fsolve(fun,teta0);
    
    % calcul des différents points
    P1 = d1*cos(teta1_init) + 1i* d1*sin(teta1_init);
    P2 = ( d1*cos(teta1_init)+ d2*cos(new_teta(1,1)) ) + 1i* ( d1*sin(teta1_init) + d2*sin(new_teta(1,1)));
    P3 = ( d1*cos(teta1_init)+ d2*cos(new_teta(1,1)) )+ d3*cos(new_teta(1,2)) + 1i * ( d1*sin(teta1_init) + d2*sin(new_teta(1,1)) + d3*sin(new_teta(1,2)) );
    
    
    affichage_robot(P1,P2,P3);
    
end