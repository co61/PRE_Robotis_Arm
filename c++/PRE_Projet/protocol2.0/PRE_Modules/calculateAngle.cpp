
#include <iostream>
#include <cmath>

using namespace std;

#define PI 3.141592653589793238463 

double a2=0.128;
double a1=0.024;
double d1=sqrt(a1*a1+a2*a2);
double d2=0.124;
double d3=0.126;
double deltaAlpha=atan(a1/a2);


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

    double teta  = asin(Y/X);
    double racine = sqrt(X*X+Y*Y);
    double frac = (d1*d1+X*X+Y*Y-d2*d2)/(2*d1*racine);

    angle.alpha = acos(frac) + teta;

    angle.beta = PI - acos((d1*d1+d2*d2-(X*X+Y*Y))/(2*d1*d2));

    float A = angle.alpha+ deltaAlpha*PI/180;
    float B = (PI-angle.beta) + (PI/2-deltaAlpha)*PI/180;

    angle.gamma = 3*PI/2 - A + (PI-B) ;


    return angle;
}



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

    return 0;
}