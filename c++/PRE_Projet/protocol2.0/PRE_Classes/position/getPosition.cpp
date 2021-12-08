
extern dynamixel::PortHandler *portHandler;
extern dynamixel::PacketHandler *packetHandler;


extern Moteur base;
extern Moteur bras1;
extern Moteur bras2;
extern Moteur bras3;
extern Moteur pince;


struct Position {
    double x;
    double y;
    double z;
};


double convertPositionToRadian(int x,int interval[2],double valMax) {
   //define convert function
   return ((x-interval[0])*valMax)/(interval[1]-interval[0]);
}
double convertRadianToPosition(double x,int offset) {
   //define convert function
   return (int)(x*(4096/(2*PI_t))+offset);
}

Position getPositionPince3D(){
	double alpha,beta,gamma, psi; // angle moteur 12, 13, 14, 15
	int32_t dxl_lecture = 0;
	int dxl_comm_result = COMM_TX_FAIL;
	uint8_t dxl_error = 0;

	int interval[2]={3072,1024};

	dxl_lecture = bras1.read();


	alpha=convertPositionToRadian(dxl_lecture, interval, PI_t);


	int interval2[2]={2048,4096};

	dxl_lecture = bras2.read();

	beta=convertPositionToRadian(dxl_lecture, interval2, -PI_t);


	int interval3[2]={1024,3072};

	dxl_lecture = bras3.read();


	gamma=convertPositionToRadian(dxl_lecture, interval3, PI_t);


	int interval4[2]={0,2048};

	dxl_lecture = base.read();

	psi=convertPositionToRadian(dxl_lecture, interval4, PI_t);

	Position getPositionPince;
	getPositionPince.x = (d1*cos(alpha-deltaAlpha)+d2*cos(beta-PI_t/2+alpha)+d3*cos(gamma-beta-alpha))*cos(psi);
	getPositionPince.y = 0.077+d1*sin(alpha-deltaAlpha)+d2*sin(beta-PI_t/2+alpha)+d3*sin(gamma-beta-alpha+PI_t);     
	getPositionPince.z = (d1*cos(alpha-deltaAlpha)+d2*cos(beta-PI_t/2+alpha)+d3*cos(gamma-beta-alpha))*sin(psi);

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
	/*
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);
	*/

	dxl_lecture = bras1.read();

	alpha=convertPositionToRadian(dxl_lecture, interval, PI_t);


	int interval2[2]={2048,4096};
	/*
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);
	*/

	dxl_lecture = bras2.read();

	beta=convertPositionToRadian(dxl_lecture, interval2, -PI_t);


	int interval3[2]={1024,3072};
	/*
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);
	*/

	dxl_lecture = bras3.read();


	gamma=convertPositionToRadian(dxl_lecture, interval3, PI_t);

	Position getPositionPince;
	getPositionPince.x = d1*cos(alpha-deltaAlpha)+d2*cos(beta-PI_t/2+alpha)+d3*cos(gamma-beta-alpha);
	getPositionPince.y = 0.077+d1*sin(alpha-deltaAlpha)+d2*sin(beta-PI_t/2+alpha)+d3*sin(gamma-beta-alpha+PI_t);

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
	/*
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);
	*/

	dxl_lecture = bras1.read();

	alpha=convertPositionToRadian(dxl_lecture, interval, PI_t);


	int interval2[2]={2048,4096};
	/*
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);
	*/

	dxl_lecture = bras2.read();

	beta=convertPositionToRadian(dxl_lecture, interval2, -PI_t);

	Position getPositionB;
	getPositionB.x = d1*cos(alpha-deltaAlpha)+d2*cos(beta-PI_t/2+alpha);
	getPositionB.y = 0.077+d1*sin(alpha-deltaAlpha)+d2*sin(beta-PI_t/2+alpha);

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

	/*
	dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
	printError(dxl_comm_result, dxl_error);
	*/

	dxl_lecture = bras1.read();


	alpha=convertPositionToRadian(dxl_lecture, interval, PI_t);


	Position getPositionA;
	getPositionA.x = d1*cos(alpha-deltaAlpha);
	getPositionA.y = 0.077+d1*sin(alpha-deltaAlpha);
	// printf("alpha : %g, beta: %g, gamma: %g\n", alpha,beta,gamma);
	// printf("x1 : %g, y1: %g, z1: %g\n",getPositionPince.x,getPositionPince.y, getPositionPince.z );
	return getPositionA;
}