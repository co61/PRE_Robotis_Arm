#include "position.hpp"
#include "getPosition.cpp"
#include <string>
using namespace std;

extern dynamixel::PortHandler *portHandler;
extern dynamixel::PacketHandler *packetHandler;

struct Angles { 
    double alpha;
    double beta;
    double gamma;
    double psi;  //rotation du bras
    bool etat; // 0 si vertical, 1 si horizontal
    string unit="R";
};


Angles calculate_angles(float Xobj, float Yobj, float Zobj, double dtX=0)
{
    Angles angle;

    float X=sqrt(Xobj*Xobj+Zobj*Zobj)+dtX;
    float Y=Yobj;

    // determine si la pince doit être a la verticale ou a l'horizontal
    /*if (Xobj <0.20)
    {
        X = Xobj;
        Y = Yobj -d0;//+d3 //La base de la pince doit être 12.6 cm au dessus de l'objet   peut etre 1cm de plus
        angle.etat = 0; //la pince arrive par dessus l'objet
    }
    else
    {
        X = Xobj - d3;
        Y = Yobj - d0;
        angle.etat = 1; // la pince arrive sur le cote
    }*/
    X-= d3;
    Y-= d0;
    angle.etat = 1; // la pince arrive sur le cote

    if (X<0){
        X=0;
    }

    printf("X : %g   Y :  %g\n", X , Y);
    double teta  = atan(Y/X);
    double racine = sqrt(X*X+Y*Y);
    double frac = (d1*d1+X*X+Y*Y-d2*d2)/(2*d1*racine);

    //calcul alpha
    angle.alpha = acos(frac) + teta + deltaAlpha;
    //calcul beta
    angle.beta = acos((d1*d1+d2*d2-(X*X+Y*Y))/(2*d1*d2)) +  (PI_t/2-deltaAlpha);
    
    //calcul gamma
    angle.gamma = 3*PI_t/2 - angle.alpha + (PI_t-angle.beta) ;


    //rotation du bras
    angle.psi = acos(Xobj/sqrt(Xobj*Xobj+Zobj*Zobj));
    if(Zobj <0 ){
        angle.psi=2*PI_t-angle.psi;
    }

    printf("%g \n",angle.psi);
    angle.unit = "R" ;
    //return struct angle
    return angle;
}


Angles anglesToDegree(Angles angleR){
    if(angleR.unit=="R"){
        // printf("Convert into degreeAngles");
        angleR.alpha = angleR.alpha*180/PI_t;
        angleR.beta = angleR.beta*180/PI_t;
        angleR.gamma = angleR.gamma*180/PI_t;
        angleR.psi = angleR.psi*180/PI_t;
        if (angleR.psi<0){
            angleR.psi=360-angleR.psi;
        }
        angleR.unit = "D";
    }
    return angleR;
}

Angles anglesToPosition(Angles angleRtoP, double dtpsi = 0){
    if(angleRtoP.unit=="R"){
        angleRtoP.alpha = 4096-convertRadianToPosition(angleRtoP.alpha, 1024);
        angleRtoP.beta = 4096-convertRadianToPosition(angleRtoP.beta, 0);
        angleRtoP.gamma = 4096-convertRadianToPosition(angleRtoP.gamma, 0);
        angleRtoP.psi = convertRadianToPosition(angleRtoP.psi, 0)+dtpsi;
        angleRtoP.unit = "P";
    }
    return angleRtoP;
}


void goToPosition(Angles angleInP, int dt=-10){
    if (angleInP.unit=="P"){
        printf("bras 3\n");
        positionBras3(angleInP.gamma+dt);
        printf("bras 1\n");
        positionBras1(angleInP.alpha+dt);
        printf("bras 2\n");
        positionBras2(angleInP.beta+dt);
        printf("base, psi : %g\n", angleInP.psi);
        positionBase(angleInP.psi);
    }
}