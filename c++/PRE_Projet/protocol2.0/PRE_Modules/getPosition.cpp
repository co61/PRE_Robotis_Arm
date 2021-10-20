#include <algorithm>
#include <tuple>

extern dynamixel::PortHandler *portHandler;
extern dynamixel::PacketHandler *packetHandler;

#define PI 3.14159265

double a2=0.128;
double a1=0.024;
double d1=sqrt(a1*a1+a2*a2);
double d2=0.124;
double d3=0.126;
double deltaAlpha=atan(a1/a2);


struct Position {
    double x;
    double y;
    double z;
};


double convertToRadian(int x,int interval[2],double valMax) {
   //define convert function
   return ((x-interval[0])*valMax)/(interval[1]-interval[0]);
}

Position getPositionPince3D(){
	double alpha,beta,gamma, psi; // angle moteur 12, 13, 14, 15
	int32_t dxl_lecture = 0;
	int dxl_comm_result = COMM_TX_FAIL;
	uint8_t dxl_error = 0;

	int interval[2]={3072,1024};
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);

	alpha=convertToRadian(dxl_lecture, interval, PI);

	int interval2[2]={2048,4096};
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);

	beta=convertToRadian(dxl_lecture, interval2, -PI);

	int interval3[2]={1024,3072};
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);

	gamma=convertToRadian(dxl_lecture, interval3, PI);

	int interval4[2]={0,2048};
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BASE, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);

	psi=convertToRadian(dxl_lecture, interval4, PI);

	Position getPositionPince;
	getPositionPince.x = (d1*cos(alpha-deltaAlpha)+d2*cos(beta-PI/2+alpha)+d3*cos(gamma-beta-alpha))*cos(psi);
	getPositionPince.y = 0.077+d1*sin(alpha-deltaAlpha)+d2*sin(beta-PI/2+alpha)+d3*sin(gamma-beta-alpha+PI);     
	getPositionPince.z = (d1*cos(alpha-deltaAlpha)+d2*cos(beta-PI/2+alpha)+d3*cos(gamma-beta-alpha))*sin(psi);
	// printf("alpha : %g, beta: %g, gamma: %g\n", alpha,beta,gamma);
	printf("x1 : %g, y1: %g, z1: %g\n",getPositionPince.x,getPositionPince.y, getPositionPince.z );
	return getPositionPince;
}

Position getPositionPince2D(){
	double alpha,beta,gamma; // angle moteur 12, 13, 14
	int32_t dxl_lecture = 0;
	int dxl_comm_result = COMM_TX_FAIL;
	uint8_t dxl_error = 0;

	int interval[2]={3072,1024};
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);

	alpha=convertToRadian(dxl_lecture, interval, PI);

	int interval2[2]={2048,4096};
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);

	beta=convertToRadian(dxl_lecture, interval2, -PI);

	int interval3[2]={1024,3072};
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);

	gamma=convertToRadian(dxl_lecture, interval3, PI);

	Position getPositionPince;
	getPositionPince.x = d1*cos(alpha-deltaAlpha)+d2*cos(beta-PI/2+alpha)+d3*cos(gamma-beta-alpha);
	getPositionPince.y = 0.077+d1*sin(alpha-deltaAlpha)+d2*sin(beta-PI/2+alpha)+d3*sin(gamma-beta-alpha+PI);
	// printf("alpha : %g, beta: %g, gamma: %g\n", alpha,beta,gamma);
	// printf("x1 : %g, y1: %g, z1: %g\n",getPositionPince.x,getPositionPince.y, getPositionPince.z );
	return getPositionPince;
}

Position getPositionB(){
	double alpha,beta; // angle moteur 12, 13
	int32_t dxl_lecture = 0;
	int dxl_comm_result = COMM_TX_FAIL;
	uint8_t dxl_error = 0;

	int interval[2]={3072,1024};
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);

	alpha=convertToRadian(dxl_lecture, interval, PI);

	int interval2[2]={2048,4096};
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);
	
	beta=convertToRadian(dxl_lecture, interval2, -PI);

	Position getPositionB;
	getPositionB.x = d1*cos(alpha-deltaAlpha)+d2*cos(beta-PI/2+alpha);
	getPositionB.y = 0.077+d1*sin(alpha-deltaAlpha)+d2*sin(beta-PI/2+alpha);
	// printf("alpha : %g, beta: %g, gamma: %g\n", alpha,beta,gamma);
	// printf("x1 : %g, y1: %g, z1: %g\n",getPositionPince.x,getPositionPince.y, getPositionPince.z );
	return getPositionB;
}

Position getPositionA(){
	double alpha; // angle moteur 12, 13, 14
	int32_t dxl_lecture = 0;
	int dxl_comm_result = COMM_TX_FAIL;
	uint8_t dxl_error = 0;

	int interval[2]={3072,1024};
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);

	alpha=convertToRadian(dxl_lecture, interval, PI);

	Position getPositionA;
	getPositionA.x = d1*cos(alpha-deltaAlpha);
	getPositionA.y = 0.077+d1*sin(alpha-deltaAlpha);
	// printf("alpha : %g, beta: %g, gamma: %g\n", alpha,beta,gamma);
	// printf("x1 : %g, y1: %g, z1: %g\n",getPositionPince.x,getPositionPince.y, getPositionPince.z );
	return getPositionA;
}