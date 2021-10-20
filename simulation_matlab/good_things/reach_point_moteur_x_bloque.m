function [new_teta1,new_teta2,new_teta3] = reach_point_moteur_x_bloque(x_desire,y_desire,moteur_bloque,d1,d2,d3,teta1_act,teta2_act,teta3_act)
%MOTEUR_X_BLOQUE Summary of this function goes here
% moteur_bloque définit quel moteur est coincé
% [x_desire y_desire] definit le point qu'on veut atteindre
% teta1_act,teta2_act, teta3_act correspondent aux angles acutuels en
% radian
% définissants la position du robot
% d1,d2,d3 sont les longueurs de chaque axe



% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%coordonnées du point souhaité
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
point_desire = [x_desire y_desire];

%affichage du point désiré
figure,grid
plot(x_desire,y_desire,'x')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% tracage des cercles représentant la zone atteignable angle 1 bloqué
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

title('modélisation du robot 3 axes dans le plan')
% on représente que la zone utile pour le robot
axis([-(d1+d2+d3) (d1+d2+d3) -(d1+d2+d3) (d1+d2+d3)])
hold on

%espace atteignable
viscircles([0,0],d1+d2+d3)


point_atteignable = 0;
if moteur_bloque == 1
    %moteur1 bloqué
    p1_x = d1*cos(teta1_act);
    p1_y = d1*sin(teta1_act);
    
    viscircles([p1_x,p1_y],d2+d3,'color','blue')
    %vérifier que le point est atteignable en bloquant le moteur1
    if (x_desire - p1_x)^2+(y_desire - p1_y)^2 > (d2+d3)^2
        disp('Impossible de se rendre à ce point car en dehors du cercle accesible par le  robot en bloquant le moteur 1')
        point_atteignable = 1;
        
        % variables de sorties
        new_teta1 = 1001;
        new_teta2 = 1001;
        new_teta3 = 1001;
        
    end
    % pour faire appel a root_moteur_x
    assignin('base','p1_x',p1_x);
    assignin('base','p1_y',p1_y);
elseif moteur_bloque == 2
    %moteur2 bloqué
    p2_x = d1*cos(teta1_act)+ d2*cos(teta2_act);
    p2_y = d1*sin(teta1_act) + d2*sin(teta2_act);
    %représentation de la zone atteignable
    rayon = sqrt( p2_x^2 + p2_y^2 );
    rayon1 = rayon + d3;
    viscircles([0,0],rayon1,'color','blue')
    
    % modélisation du probleme en se ramenant à 2 bras
    %théorème al_kashi
    teta_prime = acos((d1^2 + rayon^2 - d2^2)/(2 * d1* rayon))
    teta_prime_deg = rad2deg(teta_prime)
    
    %vérifier que le point est atteignable en bloquant le moteur2
    if((x_desire)^2 + (y_desire)^2 > rayon1^2)
        disp('Impossible de se rendre à ce point car en dehors du cercle accesible par le  robot en bloquant le moteur 2')
        point_atteignable = 1;
        
        % variables de sorties
        new_teta1 = 1002;
        new_teta2 = 1002;
        new_teta3 = 1002;
        
    end
     % pour faire appel a root_moteur_x
    assignin('base','p2_x',p2_x);
    assignin('base','p2_y',p2_y);
    assignin('base','rayon',rayon);
else
    %moteur3 bloqué
    p1_x = d1*cos(teta1_act);
    p1_y = d1*sin(teta1_act);
    p3_x = d1*cos(teta1_act) + d2*cos(teta2_act) + d3*cos(teta3_act);
    p3_y = d1*sin(teta1_act) + d2*sin(teta2_act)+ d3*sin(teta3_act);
    %représentation de la zone atteignable
    r = sqrt( (p3_x - p1_x )^2 + (p3_y - p1_y)^2 )
    r1 = r + d1;
    viscircles([0,0],r1,'color','blue')
    
    % modélisation du probleme en se ramenant à 2 bras
    %théorème al_kashi
    teta_prime = acos((d2^2 + r^2 - d3^2)/(2 * d2* r))
    teta_prime_deg = rad2deg(teta_prime)
    
    if((x_desire)^2 + (y_desire)^2 >r1^2)
        disp('Impossible de se rendre à ce point car en dehors du cercle accesible par le  robot en bloquant le moteur 3')
        point_atteignable = 1;
        
        % variables de sorties
        new_teta1 = 1003;
        new_teta2 = 1003;
        new_teta3 = 1003;
    end
    
    % pour faire appel a root_moteur_x
    assignin('base','p3_x',p3_x);
    assignin('base','p3_y',p3_y);
    assignin('base','r',r);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% représentation du robot dans sa position initial
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% calcul des différents points
P1 = d1*cos(teta1_act) + i* d1*sin(teta1_act);
P2 = d1*cos(teta1_act)+ d2*cos(teta2_act) + i* (d1*sin(teta1_act)+d2*sin(teta2_act));
P3 = d1*cos(teta1_act)+ d2*cos(teta2_act) + d3*cos(teta3_act) + i* (d1*sin(teta1_act)+d2*sin(teta2_act) + d3*sin(teta3_act));

%fonction que j'ai définit dans une fonction matlab pour ne pas surcharger
%le code
affichage_robot(P1,P2,P3);


% on fait le reste que si le point est atteignable
if point_atteignable ~= 1
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % résolution du système afin fe trouver les angles
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    fun = @root_moteur_x; %fonction que j'ai défini dans une fonction matlab
    teta0 = [deg2rad(0),deg2rad(0)];
    [new_teta,fval,exitflag1,output] = fsolve(fun,teta0);
    
    
    if moteur_bloque == 1
        % calcul des différents points
        P1 = d1*cos(teta1_act) + 1i* d1*sin(teta1_act);
        P2 = ( d1*cos(teta1_act)+ d2*cos(new_teta(1,1)) ) + 1i* ( d1*sin(teta1_act) + d2*sin(new_teta(1,1)));
        P3 = ( d1*cos(teta1_act)+ d2*cos(new_teta(1,1)) )+ d3*cos(new_teta(1,2)) + 1i * ( d1*sin(teta1_act) + d2*sin(new_teta(1,1)) + d3*sin(new_teta(1,2)) );
        
        affichage_robot(P1,P2,P3);
        legend('position souhaitée','axe 1 bloqué','axe 2','axe 3')
        
        % variables de sorties
        new_teta1 = teta1_act;
        new_teta2 = new_teta(1,1);
        new_teta3 = new_teta(1,2);
        
    elseif moteur_bloque == 2
        
        %new teta est composé de teta_cherche et teta 3
        %on a la relation teta_1 = teta_prime + new_teta(1,1)
        new_teta_deg = rad2deg(new_teta)
        teta1 =  new_teta(1,1) + teta_prime;
        
        % calcul des différents points
        P4 = rayon*cos(new_teta(1,1)) + 1i * rayon*sin(new_teta(1,1));
        P5 = rayon*cos(new_teta(1,1)) + d3*cos(new_teta(1,2)) + 1i * ( rayon*sin(new_teta(1,1)) + d3*sin(new_teta(1,2)) );
        %affichage_robot(P4,P5,P5)
        
        P1 = d1*cos(teta1 ) + 1i* d1*sin(teta1);
        
        %calcul de l'angle teta2 à partir de P1 et P4
        rapport  =(imag(P4) - imag(P1)) / (real(P4) - real(P1));
        if (real(P4) > real(P1))
            teta2 = atan( rapport );
        else
            disp('real(p4) < real(p1)')
            teta2 = atan( rapport ) + pi;
        end
        
        P2 =  d1*cos(teta1)+ d2*cos(  teta2  ) + 1i* ( d1*sin(teta1) + d2*sin( teta2 ));
        P3 =  d1*cos(teta1) + d2*cos( teta2 )+ d3*cos(new_teta(1,2)) + 1i * ( d1*sin(teta1) + d2*sin( teta2 ) + d3*sin(new_teta(1,2))) ;
        affichage_robot(P1,P2,P3);
        
        % variables de sorties
        new_teta1 = teta1;
        new_teta2 = teta2;
        new_teta3 = new_teta(1,2);
        
    else
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
        
         % variables de sorties
        new_teta1 = new_teta(1,1);
        new_teta2 = teta2;
        new_teta3 = teta3;
    end
    
end

end

