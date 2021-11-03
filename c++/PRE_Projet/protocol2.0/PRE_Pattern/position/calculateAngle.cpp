#include "position.hpp"
#include <string>
using namespace std;

extern dynamixel::PortHandler *portHandler;
extern dynamixel::PacketHandler *packetHandler;

struct Angles { 
    double alpha;
    double beta;
    double gamma;
    bool etat; // 0 si vertical, 1 si horizontal
    string unit="R";
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
        Y = Yobj + d3-0.077; //La base de la pince doit être 12.6 cm au dessus de l'objet   peut etre 1cm de plus
        angle.etat = 0; //la pince arrive par dessus l'objet
    }
    else
    {
        X = Xobj - d3;
        Y = Yobj-0.077;
        angle.etat = 1; // la pince arrive sur le cote
    }

    double teta  = atan(Y/X);
    double racine = sqrt(X*X+Y*Y);
    double frac = (d1*d1+X*X+Y*Y-d2*d2)/(2*d1*racine);

    //calcul alpha
    angle.alpha = acos(frac) + teta + deltaAlpha;
    //calcul beta
    angle.beta = 3*PI/2 - acos((d1*d1+d2*d2-(X*X+Y*Y))/(2*d1*d2));

    //calcul des anlges "complet"
    float A = angle.alpha;
    float B = angle.beta;
    //calcul gamma
    angle.gamma = 3*PI/2 - A + (PI-B) ;

    //return struct angle
    return angle;
}

Angles anglesToDegree(Angles angles){
    angles.alpha = angles.alpha*180/PI;
    angles.beta = angles.beta*180/PI;
    angles.gamma = angles.gamma*180/PI;
    angles.unit = "D";
    return angles;
}

Angles anglesToPosition(Angles angles){
    angles.alpha = convertRadianToPosition(angles.alpha, 1024);
    angles.beta = 4096-convertRadianToPosition(angles.beta, 0);
    angles.gamma = 4096-convertRadianToPosition(angles.gamma, 0);
    angles.unit = "P";
    return angles;
}


void goToPosition(Angles angleP){
    if (angleP.unit=="P"){
        positionBras3(angleP.gamma);
        positionBras1(angleP.alpha);
        positionBras2(angleP.beta);
    }
}

/*
int main(int argc, char *argv[])
{
    float alpha = 0.0;
    float beta = 0.0;
    int etat = 0;
    Angles angles = calculate_angles(0.30,-0.040);
    alpha = angles.alpha;
    beta = angles.beta;
    etat = angles.etat;

    std::cout << "etat : "<<etat << ";  alpha : " << alpha*(180.0/3.141592653589793238463) << ";  beta : "<<beta* (180.0/3.141592653589793238463)<< "\n";
    
    long double pi = 3.141592653589793238463;
    float temp = pi-alpha-0.1849;


    long double x = 0.130*cos(alpha) + 0.124 * cos(pi-0.1849-temp-beta);
    long double y = 0.130*sin(alpha) + 0.124 * sin(pi-0.1849-temp-beta);

    std::cout << "position x de la pince : " << x << "\n";
    std::cout << "position y de la pince : " << y << "\n";
    std::cout << "temp : " << temp << "\n";

    float A = alpha*(180.0/3.141592653589793238463) + 10.6;
    float B = (180-beta*(180.0/3.141592653589793238463)) + 80;
    
    float A_code = 1024 + (11.377778*A);
    float B_code = B * 11.3777778;

    std::cout << "valeur A : " << A << "  valeur A codé : " << A_code << "\n";
    std::cout << "valeur B : " << B << "  valeur B codé : " << B_code << "\n";
    
    float test = -temp*(180.0/3.141592653589793238463) + B - 180;

    float teta = asin(y/x);

    float angle_pince = 3*pi/2 - A*(3.141592653589793238463/180.0) + (180-B) *(3.141592653589793238463/180.0);
    
    std::cout << "valeur test angle pince : " <<  angle_pince << "\n";
    std::cout << "valeur test angle pince par fct: " <<  angles.gamma << "\n";

    return 0;
}*/