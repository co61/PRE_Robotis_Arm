
#include <unistd.h>

#include <QDebug>
#include "../widget.h"
#include "moteur.hpp"
#include "../clavier/clavier.hpp"

extern dynamixel::PortHandler *portHandler;
extern dynamixel::PacketHandler *packetHandler;


extern int GOAL_POSE1;
extern int GOAL_POSE2;
extern int GOAL_POSE3;
extern int GOAL_POSE_PINCE;


extern Moteur base;
extern Moteur bras1;
extern Moteur bras2;
extern Moteur bras3;
extern Moteur pince;



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


int Moteur::getID(){
  return this->id;
}

int Moteur::Torque_disable(){

  this->dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, this->id, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, &this->dxl_error);
  if (this->dxl_comm_result != COMM_SUCCESS){
    printf("%s\n", packetHandler->getTxRxResult(this->dxl_comm_result));
    return 0;
  } 
  else if(this->dxl_error != 0){
    printf("%s\n", packetHandler->getRxPacketError(this->dxl_error));
    return 0;
  }
  else{
    printf("Succeeded disabling %d DYNAMIXEL Torque.\n", this->id);
    qDebug() << "Succeeded disabling" << this->id << "DYNAMIXEL Torque.\n";
    return 1;
  }

}



int Moteur::Torque_enable(){

  this->dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, this->id, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, &this->dxl_error);
  if (this->dxl_comm_result != COMM_SUCCESS){
    printf("%s\n", packetHandler->getTxRxResult(this->dxl_comm_result));
    return 0;
  } 
  else if(this->dxl_error != 0){
    printf("%s\n", packetHandler->getRxPacketError(this->dxl_error));
    return 0;
  }
  else{
    printf("Succeeded enabling %d DYNAMIXEL Torque.\n", this->id);
    return 1;
  }

}


void Moteur::profileVelocity(int val){
  /*
  this->dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, this->id, ADDR_DRIVE_MODE, 0, &this->dxl_error);
  printError(this->dxl_comm_result, this->dxl_error);
  */
  this->dxl_error = 0;
  this->dxl_comm_result = COMM_SUCCESS;
  this->dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, this->id, ADDR_PROFILE_VELOCITY, val, &this->dxl_error);
  printError(this->dxl_comm_result, this->dxl_error);
  this->dxl_error = 0;
  this->dxl_comm_result = COMM_SUCCESS;


    printf("Vitesse dedans fonctions: %d DYNAMIXEL Torque.\n", val);
}

int Moteur::read(){
  int32_t dxl_lecture = 0;

  this->dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, this->id, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &this->dxl_error);
  printError(this->dxl_comm_result, this->dxl_error);

  return dxl_lecture;
}



int Moteur::moove(int dt){
  int32_t dxl_lecture = 0;                      

  this->dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, this->id, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &this->dxl_error);
  printError(this->dxl_comm_result,this-> dxl_error);

  this->dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, this->id, ADDR_GOAL_POSITION, dxl_lecture + dt, &this->dxl_error);
  printError(this->dxl_comm_result, this->dxl_error);

  return dxl_lecture + dt;
}


void Torque_enable_all(){
  base.Torque_enable();
  bras1.Torque_enable();
  bras2.Torque_enable();
  bras3.Torque_enable();
  pince.Torque_enable();
}











// Mise a jour des moteurs selon les Dt choisit par la manette
void moteur_dt(int dt_base, int dt_bras1, int dt_bras2, int dt_bras3, int dt_pince){
  if(dt_pince != 0)
    pince.moove(dt_pince);

  if(dt_bras1 != 0)
    bras1.moove(dt_bras1);
  
  if(dt_bras2 != 0)
    bras2.moove(dt_bras2);
  
  if(dt_bras3 != 0)
    bras3.moove(dt_bras3);
  
  if(dt_base != 0)
    base.moove(dt_base);
}


int Moteur::position(int position){

  this->dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, this->id, ADDR_GOAL_POSITION, position, &this->dxl_error);
  printError(this->dxl_comm_result, this->dxl_error);
  this->dxl_error = 0;
  this->dxl_comm_result = COMM_SUCCESS;
  return 1;
}







////////////////////////////////////////////////////
// Pose le bras au sol avant de disable le Torque //
////////////////////////////////////////////////////
void position(){
  //Controle les moteurs
  Torque_enable_all();

  bras1.position(GOAL_POSE1);
  bras2.position(GOAL_POSE2);
  bras3.position(GOAL_POSE3);
  sleep(2);
  pince.position(GOAL_POSE_PINCE);

  printf("POSITION TERMINE\n");
}








void Moteur::profileVelocity(int base, int bras1, int bras2, int bras3, int pince){

  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BASE, ADDR_PROFILE_VELOCITY, base, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PROFILE_VELOCITY, bras1, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PROFILE_VELOCITY, bras2, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_PROFILE_VELOCITY, bras3, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_PROFILE_VELOCITY, pince, &dxl_error);
  printError(dxl_comm_result, dxl_error);

}
void Torque_disable_all(){

  Moteur::profileVelocity(30,30,30,30,30);

  usleep(1000000);

  bras1.position(2280);
  bras2.position(2040);
  bras3.position(2850);

  usleep(10000000);

  base.Torque_disable();
  bras1.Torque_disable();
  bras2.Torque_disable();
  bras3.Torque_disable();
  pince.Torque_disable();  
}



int getch_moteur() {
#if defined(__linux__) || defined(__APPLE__)
  struct termios oldt, newt;
  int ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
#elif defined(_WIN32) || defined(_WIN64)
  return _getch();
#endif
}


int kbhit_moteur(void) {
#if defined(__linux__) || defined(__APPLE__)
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if (ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }


  return 0;
#elif defined(_WIN32) || defined(_WIN64)
  return _kbhit();
#endif
}




//Initialisation des ports
int Moteur::init(){


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
    getch_moteur();
    return 0;
  }

  // Set port baudrate
  if (portHandler->setBaudRate(BAUDRATE)) {
    printf("Succeeded to change the baudrate!\n");
  }
  else {
    printf("Failed to change the baudrate!\n");
    printf("Press any key to terminate...\n");
    getch_moteur();
    return 0;
  }

  // Disable DYNAMIXEL Torque
  //Moteur::Torque_disable_all();


  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  //régalge de la vitesse de mouvement des moteurs
  /*
  for(auto& mot: Moteur::moteurs){
    mot.profileVelocity(30);
  }
  */
  return 1;

}