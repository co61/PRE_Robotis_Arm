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





point_desire = [10 10];
x_desire = point_desire(1,1);
y_desire = point_desire(1,2);

if (x_desire)^2+(y_desire)^2 > (d1+d2+d3)^2 %d1 + d2 +d3 est le rayon du robot
    disp('imossible de se rendre à ce point car en dehors du cercle accesible par le  robot')
    in_circle = 1;
    
else
    in_circle = 0;
end

figure,grid
plot(x_desire,y_desire,'x')
viscircles([0,0],d1+d2+d3)
title('modélisation du robot 3 axes dans le plan')
axis([-(d1+d2+d3) (d1+d2+d3) -(d1+d2+d3) (d1+d2+d3)])
hold on
condition =0;
temps =1;
while (condition == 0 && in_circle == 0)
    if temps == 1
        teta1(temps)=deg2rad(90);
        teta2(temps)=deg2rad(0);
        teta3(temps)=deg2rad(0);
        hauteur_actuelle = (d1*sin(teta1(1))+d2*sin(teta2(1)) + d3*sin(teta3(1)));
        
        P1 = d1*cos(teta1) + i* d1*sin(teta1);
        P2 = d1*cos(teta1)+ d2*cos(teta2) + i* (d1*sin(teta1)+d2*sin(teta2));
        P3 = d1*cos(teta1)+ d2*cos(teta2) + d3*cos(teta3) + i* (d1*sin(teta1)+d2*sin(teta2) + d3*sin(teta3));
        temps = temps + 1;
        
    else % temps != 1
        angle_bloque = 1;
        teta1(temps)=teta1(temps-1);
        
        p1_x = d1*cos(teta1(temps));
        p1_y = d1*sin(teta1(temps));
        
        %est-ce que le point desire est atteignable ? 
        %il faut noter que le centre du cercle atteignable est l'extremite
        %du bras 1
        
        viscircles([p1_x,p1_y],d2+d3,'color','blue')
        if((x_desire - p1_x)^2 + (y_desire - p1_y)^2 > (d2 + d3)^2)
            disp('pas réalisable en bloquant le moteur1');
         end   

        fun = @root2d; %fonction que j'ai défini dans une fonction matlab
        teta0 = [deg2rad(0),deg2rad(0)];
        [new_teta,fval,exitflag1,output] = fsolve(fun,teta0);
        if exitflag1 > 0
            condition = 1
            P1 = d1*cos(teta1(temps)) + i* d1*sin(teta1(temps));
            P2 = d1*cos(teta1(temps))+ d2*cos(new_teta(1,1)) + i* (d1*sin(teta1(temps))+d2*sin(new_teta(1,1)));
            P3 = d1*cos(teta1(temps))+ d2*cos(new_teta(1,1)) + d3*cos(new_teta(1,2)) + i* (d1*sin(teta1(temps))+d2*sin(new_teta(1,1)) + d3*sin(new_teta(1,2)));
        end
        % si pas de solution en bloquant l'angle 1 => bloquer angle 2
        if exitflag1 < 0
            angle_bloque = 2;
            teta2(temps)=teta2(temps-1);
            
            p2_x = d1*cos(teta1(temps))+ d2*cos(teta2(temps));
            p2_y = d1*sin(teta1(temps)) + d2*sin(teta2(temps));
            
            %théorème d'al-kashi
            %distance = sqrt(d1^2 + d2^2 - 2*d1*d2*cos(teta2(temps)));
            rayon = sqrt( p2_x^2 + p2_y^2 );
            rayon1 = rayon + d3;
            viscircles([0,0],rayon1,'color','green')
             
            if((x_desire)^2 + (y_desire)^2 > rayon1^2)
                disp('on ne peut pas atteindre le point en bloquant le moteur 2')
            end    
            
        
            fun = @root2d; %fonction que j'ai défini dans une fonction matlab
            teta0 = [deg2rad(0),deg2rad(0)];
            [new_teta,fval,exitflag2,output] = fsolve(fun,teta0);
            
            if exitflag2 > 0
                condition = 2
                P1 = d1*cos(new_teta(1,1)) + i* d1*sin(new_teta(1,1));
                P2 = d1*cos(new_teta(1,1))+ d2*cos(teta2(temps)) + i* (d1*sin(new_teta(1,1))+d2*sin(teta2(temps)));
                P3 = d1*cos(new_teta(1,1))+ d2*cos(teta2(temps)) + d3*cos(new_teta(1,2)) + i* (d1*sin(new_teta(1,1))+d2*sin(teta2(temps)) + d3*sin(new_teta(1,2)));
            end
            
%             if exitflag2 < 0
%                 angle_bloque = 3;
%                 teta3(temps)=teta3(temps-1);
%                 
%                 p3_x = d3*cos(teta3(temps));
%                 p3_y = d3*sin(teta3(temps));
%                 
%                 
%                 fun = @root2d; %fonction que j'ai défini dans une fonction matlab
%                 teta0 = [deg2rad(90),deg2rad(0)];
%                 [new_teta,fval,exitflag3,output] = fsolve(fun,teta0);
%                 if exitflag3 > 0
%                     condition = 3
%                     P1 = d1*cos(new_teta(1,1)) + i* d1*sin(new_teta(1,1));
%                     P2 = d1*cos(new_teta(1,1))+ d2*cos(new_teta(1,2)) + i* (d1*sin(new_teta(1,1))+d2*sin(teta2(temps)));
%                     P3 = d1*sin(new_teta(1,1))+ d2*sin(new_teta(1,2)) + d3*cos(teta3(temps)) + i* (d1*sin(new_teta(1,1))+d2*sin(new_teta(1,2)) + d3*sin(teta3(temps)));
%                 end
%                 
%             end
        end
        
        
        
        
      
        
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









   
    
    
