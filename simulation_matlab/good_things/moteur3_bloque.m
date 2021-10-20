close all
clear all
clc

moteur_bloque = 3;
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
teta2_init=deg2rad(45);
teta3_init=deg2rad(0);

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%coordonnées du point souhaité
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

point_desire = [20 -18];
x_desire = point_desire(1,1);
y_desire = point_desire(1,2);

%affichage du point désiré
figure,grid
plot(x_desire,y_desire,'x')


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% tracage des cercles représentant la zone atteignable angle 2 bloqué
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
title('modélisation du robot 3 axes dans le plan')
axis([-(d1+d2+d3) (d1+d2+d3) -(d1+d2+d3) (d1+d2+d3)])
hold on

%espace atteignable
viscircles([0,0],d1+d2+d3)
hold on

%moteur3 bloqué
p1_x = d1*cos(teta1_init);
p1_y = d1*sin(teta1_init);
p3_x = d1*cos(teta1_init) + d2*cos(teta2_init) + d3*cos(teta3_init);
p3_y = d1*sin(teta1_init) + d2*sin(teta2_init)+ d3*sin(teta3_init);
%représentation de la zone atteignable
r = sqrt( (p3_x - p1_x )^2 + (p3_y - p1_y)^2 )
r1 = r + d1;
viscircles([0,0],r1,'color','blue')

% modélisation du probleme en se ramenant à 2 bras
%théorème al_kashi
teta_prime = acos((d2^2 + r^2 - d3^2)/(2 * d2* r))
teta_prime_deg = rad2deg(teta_prime)

% on a la relation teta_prime_prime = 180 - teta_prime_deg + teta2_init_deg 
%teta_prime_prime_deg = 180 - teta_prime_deg - rad2deg(teta2_init)

% teta_prime = angle entre r et d2

point_atteignable = 0;
%vérifier que le point est atteignable en bloquant le moteur2
if((x_desire)^2 + (y_desire)^2 >r1^2)
    disp('Impossible de se rendre à ce point car en dehors du cercle accesible par le  robot en bloquant le moteur 3')
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
    
    %on a la relation teta_1 = teta_prime + new_teta(1,1)
    new_teta_deg = rad2deg(new_teta)
    teta2 =  new_teta(1,2) + teta_prime;
    
    % calcul des différents points
    P4 = d1*cos(new_teta(1,1)) + 1i * d1*sin(new_teta(1,1));
    P5 = d1*cos(new_teta(1,1)) + r*cos(new_teta(1,2)) + 1i * (d1*sin(new_teta(1,1)) + r*sin(new_teta(1,2)) );
    %affichage_robot(P4,P5,P5) 
       
    P1 =  d1*cos(new_teta(1,1)) + 1i * d1*sin(new_teta(1,1));
    P2 =  d1*cos(new_teta(1,1)) + d2*cos( teta2 ) + 1i * (d1*sin(new_teta(1,1)) + d2*sin( teta2 ));
    
    %calcul de l'angle teta3 à partir de P2 et P5
    rapport  =(imag(P5) - imag(P2)) / (real(P5) - real(P2));
    if (real(P5) > real(P2))
         teta3 = atan( rapport );
    else
        disp('real(p5) < real(p2)')
        teta3 = atan( rapport ) + pi;
    end
    
    P3 =  d1*cos(new_teta(1,1)) + d2*cos( teta2 ) + d3*cos( teta3 ) + 1i * (d1*sin(new_teta(1,1)) + d2*sin( teta2 ) + d3*sin( teta3 ));
    affichage_robot(P1,P2,P3);
end
