close all
clear all
clc

moteur_bloque = 2;
%param?tres physiques du robot
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
%coordonn?es du point souhait?
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

point_desire = [0 -20];
x_desire = point_desire(1,1);
y_desire = point_desire(1,2);

%affichage du point d?sir?
figure,grid
plot(x_desire,y_desire,'x')



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% tracage des cercles repr?sentant la zone atteignable angle 2 bloqu?
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
title('mod?lisation du robot 3 axes dans le plan')
axis([-(d1+d2+d3) (d1+d2+d3) -(d1+d2+d3) (d1+d2+d3)])
hold on

%espace atteignable
viscircles([0,0],d1+d2+d3)

%moteur2 bloqu?
p2_x = d1*cos(teta1_init)+ d2*cos(teta2_init);
p2_y = d1*sin(teta1_init) + d2*sin(teta2_init);
%repr?sentation de la zone atteignable
rayon = sqrt( p2_x^2 + p2_y^2 );
rayon1 = rayon + d3;
viscircles([0,0],rayon1,'color','blue')

% mod?lisation du probleme en se ramenant ? 2 bras
%th?or?me al_kashi
teta_prime = acos((d1^2 + rayon^2 - d2^2)/(2 * d1* rayon))


point_atteignable = 0;
%v?rifier que le point est atteignable en bloquant le moteur2
if((x_desire)^2 + (y_desire)^2 > rayon1^2)
    disp('Impossible de se rendre ? ce point car en dehors du cercle accesible par le  robot en bloquant le moteur 2')
    point_atteignable = 1;
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% repr?sentation du robot dans sa position initial
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% calcul des diff?rents points
P1 = d1*cos(teta1_init) + i* d1*sin(teta1_init);
P2 = d1*cos(teta1_init)+ d2*cos(teta2_init) + i* (d1*sin(teta1_init)+d2*sin(teta2_init));
P3 = d1*cos(teta1_init)+ d2*cos(teta2_init) + d3*cos(teta3_init) + i* (d1*sin(teta1_init)+d2*sin(teta2_init) + d3*sin(teta3_init));


%fonction que j'ai d?finit dans une fonction matlab pour ne pas surcharger
%le code
affichage_robot(P1,P2,P3);
%line( [0,real(P2)]',[ 0 , imag(P2) ]','color','b' )
% on fait le reste que si le point est atteignable
if point_atteignable ~= 1
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % r?solution du syst?me afin fe trouver les angles
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   
    
    fun = @root; %fonction que j'ai d?fini dans une fonction matlab
    teta0 = [deg2rad(0),deg2rad(0)];
    [new_teta,fval,exitflag1,output] = fsolve(fun,teta0);
    
    %new teta est compos? de teta_cherche et teta 3
    %on a la relation teta_1 = teta_prime + teta_cherche
    teta1 = new_teta(1,1) + teta_prime;
    % calcul des diff?rents points
    P1 = d1*cos(teta1) + 1i* d1*sin(teta1);
    P2 = ( d1*cos(teta1))+ d2*cos( teta2_init ) + 1i* ( d1*sin(teta1) + d2*sin( teta2_init ));
    P3 = ( d1*cos(teta1) + d2*cos( teta2_init )+ d3*cos(new_teta(1,2))) + 1i * ( d1*sin(teta1) + d2*sin( teta2_init ) + d3*sin(new_teta(1,2)) );
    
    P4 = rayon*cos(new_teta(1,1)) + 1i * rayon*sin(new_teta(1,1));
    P5 = rayon*cos(new_teta(1,1)) + d3*cos(new_teta(1,2)) + 1i * ( rayon*sin(new_teta(1,1)) +d3*sin(new_teta(1,2)) );
    affichage_robot(P1,P2,P3);
    affichage_robot(P4,P5,P3);
    
end