#include "moteur.hpp"

#include "controle.hpp"
#include "controle.cpp"

extern dynamixel::PortHandler *portHandler;
extern dynamixel::PacketHandler *packetHandler;


int Torque_disable(int dxl_id){

  int dxl_comm_result = COMM_TX_FAIL;             // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, dxl_id, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
  if (dxl_comm_result != COMM_SUCCESS){
    printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    return 0;
  } 
  else if(dxl_error != 0){
    printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    return 0;
  }
  else{
    printf("Succeeded disabling %d DYNAMIXEL Torque.\n", dxl_id);
    return 1;
  }

}


int Torque_enable(int dxl_id){

  int dxl_comm_result = COMM_TX_FAIL;             // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, dxl_id, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
  if (dxl_comm_result != COMM_SUCCESS){
    printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    return 0;
  } 
  else if(dxl_error != 0){
    printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    return 0;
  }
  else{
    printf("Succeeded enabling %d DYNAMIXEL Torque.\n", dxl_id);
    return 1;
  }

}

void Torque_enable_all(){
  Torque_enable(DXL_ID_BASE);
  Torque_enable(DXL_ID_BRAS1);
  Torque_enable(DXL_ID_BRAS2);
  Torque_enable(DXL_ID_BRAS3);
  Torque_enable(DXL_ID_PINCE);
}

void Torque_disable_all(){
  Torque_disable(DXL_ID_BASE);
  Torque_disable(DXL_ID_BRAS1);
  Torque_disable(DXL_ID_BRAS2);
  Torque_disable(DXL_ID_BRAS3);
  Torque_disable(DXL_ID_PINCE);  
}


//Erreur de com
int printError(int dxl_comm_result, uint8_t dxl_error){
	if (dxl_comm_result != COMM_SUCCESS)
    {
      printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
      return 0;
    }
    else if (dxl_error != 0)
    {
      printf("%s\n", packetHandler->getRxPacketError(dxl_error));
      return 0;
    }
  return 1;
}

int readBase(){
  int32_t dxl_lecture = 0;
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BASE, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
  printError(dxl_comm_result, dxl_error);

  return dxl_lecture;
}

int readBras1(){
  int32_t dxl_lecture = 0;
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
  printError(dxl_comm_result, dxl_error);

  return dxl_lecture;
}

int readBras2(){
  int32_t dxl_lecture = 0;
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
  printError(dxl_comm_result, dxl_error);

  return dxl_lecture;
}

int readBras3(){
  int32_t dxl_lecture = 0;
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
  printError(dxl_comm_result, dxl_error);

  return dxl_lecture;
}

int readPince(){
  int32_t dxl_lecture = 0;
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error
  
  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
  printError(dxl_comm_result, dxl_error);

  return dxl_lecture;
}


int mooveBase(int dt){
  int32_t dxl_lecture = 0;
  int dxl_comm_result = COMM_TX_FAIL;              
  uint8_t dxl_error = 0;                           

  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BASE, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
  printError(dxl_comm_result, dxl_error);

  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BASE, ADDR_GOAL_POSITION, dxl_lecture + dt, &dxl_error);
  printError(dxl_comm_result, dxl_error);

  return dxl_lecture + dt;
}

int mooveBras1(int dt){
    int32_t dxl_lecture = 0;
    int dxl_comm_result = COMM_TX_FAIL;              
    uint8_t dxl_error = 0;                           

    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
    printError(dxl_comm_result, dxl_error);

    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_GOAL_POSITION, dxl_lecture + dt, &dxl_error);
    printError(dxl_comm_result, dxl_error);

    return dxl_lecture + dt;
}

int mooveBras2(int dt){
    int32_t dxl_lecture = 0;
    int dxl_comm_result = COMM_TX_FAIL;              
    uint8_t dxl_error = 0;                           

    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
    printError(dxl_comm_result, dxl_error);

    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_GOAL_POSITION, dxl_lecture + dt, &dxl_error);
    printError(dxl_comm_result, dxl_error);

    return dxl_lecture + dt;
}

int mooveBras3(int dt){
    int32_t dxl_lecture = 0;
    int dxl_comm_result = COMM_TX_FAIL;              
    uint8_t dxl_error = 0;                           

    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
    printError(dxl_comm_result, dxl_error);

    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_GOAL_POSITION, dxl_lecture + dt, &dxl_error);
    printError(dxl_comm_result, dxl_error);

    return dxl_lecture + dt;
}

int moovePince(int dt){
    int32_t dxl_lecture = 0;
    int dxl_comm_result = COMM_TX_FAIL;              
    uint8_t dxl_error = 0;                           

    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
    printError(dxl_comm_result, dxl_error);

    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_GOAL_POSITION, dxl_lecture + dt, &dxl_error);
    printError(dxl_comm_result, dxl_error);

    return dxl_lecture + dt;
}

// Mise a jour des moteurs selon les Dt choisit par la manette
void moteur_dt(int dt_base, int dt_bras1, int dt_bras2, int dt_bras3, int dt_pince){
  if(dt_pince != 0)
    moovePince(dt_pince);

  if(dt_bras1 != 0)
    mooveBras1(dt_bras1);
  
  if(dt_bras2 != 0)
    mooveBras2(dt_bras2);
  
  if(dt_bras3 != 0)
    mooveBras3(dt_bras3);
  
  if(dt_base != 0)
    mooveBase(dt_base);
}

int positionBras1(int position){
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_GOAL_POSITION, position, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  return 1;
}

int positionBras2(int position){
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_GOAL_POSITION, position, &dxl_error);
  
  return printError(dxl_comm_result, dxl_error);
}

int positionBras3(int position){
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_GOAL_POSITION, position, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  return printError(dxl_comm_result, dxl_error);
}


int positionBase(int position){
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BASE, ADDR_GOAL_POSITION, position, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  return printError(dxl_comm_result, dxl_error);
}


int positionPince(int position){
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_GOAL_POSITION, position, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  return printError(dxl_comm_result, dxl_error);
}



//Initialisation des ports
int init(){
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  // Initialize PortHandler instance
  // Set the port path
  // Get methods and members of PortHandlerLinux or PortHandlerWindows
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);

  // Initialize PacketHandler instance
  // Set the protocol version
  // Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
  packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);


  // Open port
  if (portHandler->openPort()) {
    printf("Succeeded to open the port!\n");
  }
  else {
    printf("Failed to open the port!\n");
    printf("Press any key to terminate...\n");
    getch();
    return 0;
  }

  // Set port baudrate
  if (portHandler->setBaudRate(BAUDRATE)) {
    printf("Succeeded to change the baudrate!\n");
  }
  else {
    printf("Failed to change the baudrate!\n");
    printf("Press any key to terminate...\n");
    getch();
    return 0;
  }

  // Disable DYNAMIXEL Torque
  Torque_disable_all();

  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_DRIVE_MODE, 0, &dxl_error);
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_PROFILE_VELOCITY, 50, &dxl_error);

  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_DRIVE_MODE, 0, &dxl_error);
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PROFILE_VELOCITY, 30, &dxl_error);

  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_DRIVE_MODE, 0, &dxl_error);
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PROFILE_VELOCITY, 30, &dxl_error);

  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_DRIVE_MODE, 0, &dxl_error);
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_PROFILE_VELOCITY, 30, &dxl_error);

  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID_BASE, ADDR_DRIVE_MODE, 0, &dxl_error);
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BASE, ADDR_PROFILE_VELOCITY, 30, &dxl_error);

  return 1;

}