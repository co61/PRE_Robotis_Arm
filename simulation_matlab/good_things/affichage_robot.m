function [outputArg1,outputArg2] = affichage_robot(P1,P2,P3)
%AFFICHAGE_ROBOT Summary of this function goes here
%   Detailed explanation goes here
% p1,p2,p3 sont les nombres complexes représentant les coordonées des
% points qui représentent les extrémité des bras 
% outputArg1 = inputArg1;
% outputArg2 = inputArg2;


%affichage des segments

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
segment1 = line(segment1P1,segment1P2,'Color','b');
segment2 = line(segment2P1,segment2P2,'Color','r');
segment3 = line(segment3P1,segment3P2,'Color','g');

end

