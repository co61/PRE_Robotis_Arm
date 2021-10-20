#include <iostream>
#include <cmath>

using namespace std;

extern dynamixel::PortHandler *portHandler;
extern dynamixel::PacketHandler *packetHandler;

struct Angles { 
    double alpha;
    double beta;
    double gamma;
    bool etat; // 0 si vertical, 1 si horizontal
};


Angles calculate_angles(float Xobj, float Yobj)
{
    Angles angle;

    float X=0;
    float Y=0;

    // determine si la pince doit être a la verticale ou a l'horizontal
    if (Xobj <0.20)
    {
        X = Xobj;
        Y = Yobj + d3; //La base de la pince doit être 12.6 cm au dessus de l'objet   peut etre 1cm de plus
        angle.etat = 0; //la pince arrive par dessus l'objet
    }
    else
    {
        X = Xobj - d3;
        Y = Yobj;
        angle.etat = 1; // la pince arrive sur le cote
    }

    double teta  = atan(Y/X);
    double racine = sqrt(X*X+Y*Y);
    double frac = (d1*d1+X*X+Y*Y-d2*d2)/(2*d1*racine);

    //calcul alpha
    angle.alpha = acos(frac) + teta + deltaAlpha;
    //calcul beta
    angle.beta = PI - acos((d1*d1+d2*d2-(X*X+Y*Y))/(2*d1*d2))+ (PI/2-deltaAlpha);

    //calcul des anlges "complet"
    float A = angle.alpha;
    float B = PI-angle.beta;
    //calcul gamma
    angle.gamma = 3*PI/2 - A + (PI-B) ;

    //return struct angle
    return angle;
}

Angles anglesToDegree(Angles angles){
    angles.alpha = angles.alpha*180/PI;
    angles.beta = angles.beta*180/PI;
    angles.gamma = angles.gamma*180/PI;
    return angles;
}

