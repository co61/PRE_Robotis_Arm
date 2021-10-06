#include <controle.hpp>
#include <moteur.hpp>
#include <algorithm>

extern dynamixel::PortHandler *portHandler;
extern dynamixel::PacketHandler *packetHandler;

#define PI 3.14159265

double a2=0.128;
double a1=0.024;
double d1=sqrt(a1^2+a2^2);
double d2=0.124;
double d3=0.126;
double deltaAlpha=acos(a1/d1);

double convertToDegre(int x,int interval[2],double valMax) {
   //define convert function
   return ((x-interval[0])*valMax)/(interval[1]-interval[0]);
}

(double,double) getPositionPince(){
	double alpha,beta,gamma; // angle moteur 12, 13, 14
	int32_t dxl_lecture = 0;
	int dxl_comm_result = COMM_TX_FAIL;              
	uint8_t dxl_error = 0;                           

	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);

	alpha=convertToDegre(dxl_lecture);

	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);

	beta=convertToDegre(dxl_lecture);

	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);

	gamma=convertToDegre(dxl_lecture);


	double x1 = d1*cos(alpha-deltaAlpha)+d2*cos(beta-90+alpha)+d3*cos(gamma-beta-alpha+180);
	double y1 = 0.077+d1*sin(alpha-deltaAlpha)+d2*sin(beta-90+alpha)+d3*sin(gamma-beta-alpha+180);

	printf("x1 : %g, y1: %g\n",x1,y1 );
	return (x1,y1);
}