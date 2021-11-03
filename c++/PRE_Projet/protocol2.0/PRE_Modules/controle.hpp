#include <linux/joystick.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define PI 3.141592653589793238463 

double a2=0.128;
double a1=0.024;
double d1=sqrt(a1*a1+a2*a2);
double d2=0.124;
double d3=0.126;
double deltaAlpha=atan(a1/a2);