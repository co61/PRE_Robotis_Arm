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

teta1 = t;
teta2 = 2*t;
teta3 = 3*t;


P1 = d1*cos(teta1) + i* d1*sin(teta1);
P2 = d1*cos(teta1)+ d2*cos(teta2) + i* (d1*sin(teta1)+d2*sin(teta2));
P3 = d1*cos(teta1)+ d2*cos(teta2) + d3*cos(teta3) + i* (d1*sin(teta1)+d2*sin(teta2) + d3*sin(teta3));

figure,
axis([-(d1+d2+d3) (d1+d2+d3) -(d1+d2+d3) (d1+d2+d3)])
for temps = 1:length(t)
    hold on
    %definition des trois segements du robot
    % permiere partie
    segment1P1(1,1) = 0;
    segment1P1(2,1) = real(P1(temps));
    segment1P2(1,1) = 0;
    segment1P2(2,1) = imag(P1(temps));
    % 2eme partie
    segment2P1(1,1) = segment1P1(2,1);
    segment2P1(2,1) = real(P2(temps));
    segment2P2(1,1) = segment1P2(2,1);
    segment2P2(2,1) = imag(P2(temps));
     % 3eme partie
    segment3P1(1,1) = segment2P1(2,1);
    segment3P1(2,1) = real(P3(temps));
    segment3P2(1,1) = segment2P2(2,1);
    segment3P2(2,1) = imag(P3(temps));
    
    
    %affichage
    segment1(temps) = line(segment1P1,segment1P2,'Color','b')
    segment2(temps) = line(segment2P1,segment2P2,'Color','r')
    segment3(temps) = line(segment3P1,segment3P2,'Color','g')
    if temps ~= 1
        segment1(temps-1).delete();
        segment2(temps-1).delete();
        segment3(temps-1).delete();
    end
    pause(0.01)
end

