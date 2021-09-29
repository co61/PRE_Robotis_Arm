/*******************************************************************************
* Copyright 2017 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*******************************************************************************
************************     Read and Write Example      ***********************
* Required Environment to run this example :
*   - Protocol 2.0 supported DYNAMIXEL(X, P, PRO/PRO(A), MX 2.0 series)
*   - DYNAMIXEL Starter Set (U2D2, U2D2 PHB, 12V SMPS)
* How to use the example :
*   - Use proper DYNAMIXEL Model definition from line #44
*   - Build and Run from proper architecture subdirectory.
*   - For ARM based SBCs such as Raspberry Pi, use linux_sbc subdirectory to build and run.
*   - https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_sdk/overview/
* Author: Ryu Woon Jung (Leon)
* Maintainer : Zerom, Will Son
*******************************************************************************/

#if defined(__linux__) || defined(__APPLE__)
#include <fcntl.h>
#include <termios.h>
#define STDIN_FILENO 0
#elif defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string>


#include <unistd.h>
#include <linux/joystick.h>

#include "dynamixel_sdk.h"  // Uses DYNAMIXEL SDK library

/********* DYNAMIXEL Model definition *********
***** (Use only one definition at a time) *****/
#define X_SERIES // X330, X430, X540, 2X430
// #define PRO_SERIES // H54, H42, M54, M42, L54, L42
// #define PRO_A_SERIES // PRO series with (A) firmware update.
// #define P_SERIES  // PH54, PH42, PM54
// #define XL320  // [WARNING] Operating Voltage : 7.4V
// #define MX_SERIES // MX series with 2.0 firmware update.

// Control table address
#if defined(X_SERIES) || defined(MX_SERIES)
  #define ADDR_TORQUE_ENABLE          64
  #define ADDR_MAX_POSITION           48
  #define ADDR_MIN_POSITION           52
  #define ADDR_GOAL_POSITION          116
  #define ADDR_PRESENT_POSITION       132
  #define MINIMUM_POSITION_LIMIT      0  
  #define MAXIMUM_POSITION_LIMIT      100  
  #define BAUDRATE                    1000000
#elif defined(PRO_SERIES)
  #define ADDR_TORQUE_ENABLE          562  // Control table address is different in DYNAMIXEL model
  #define ADDR_GOAL_POSITION          596
  #define ADDR_PRESENT_POSITION       611
  #define MINIMUM_POSITION_LIMIT      -150000  // Refer to the Minimum Position Limit of product eManual
  #define MAXIMUM_POSITION_LIMIT      150000  // Refer to the Maximum Position Limit of product eManual
  #define BAUDRATE                    57600
#elif defined(P_SERIES) ||defined(PRO_A_SERIES)
  #define ADDR_TORQUE_ENABLE          512  // Control table address is different in DYNAMIXEL model
  #define ADDR_GOAL_POSITION          564
  #define ADDR_PRESENT_POSITION       580
  #define MINIMUM_POSITION_LIMIT      -150000  // Refer to the Minimum Position Limit of product eManual
  #define MAXIMUM_POSITION_LIMIT      150000  // Refer to the Maximum Position Limit of product eManual
  #define BAUDRATE                    57600
#endif

// DYNAMIXEL Protocol Version (1.0 / 2.0)
// https://emanual.robotis.com/docs/en/dxl/protocol2/
#define PROTOCOL_VERSION  2.0

// Factory default ID of all DYNAMIXEL is 1
#define DXL_ID_BASE   11
#define DXL_ID_BRAS1  12
#define DXL_ID_BRAS2  13
#define DXL_ID_BRAS3  14
#define DXL_ID_PINCE  15

// Use the actual port assigned to the U2D2.
// ex) Windows: "COM*", Linux: "/dev/ttyUSB*", Mac: "/dev/tty.usbserial-*"
#define DEVICENAME  "/dev/ttyUSB0"

#define TORQUE_ENABLE                   1
#define TORQUE_DISABLE                  0
#define DXL_MOVING_STATUS_THRESHOLD     20  // DYNAMIXEL moving status threshold
#define ESC_ASCII_VALUE                 0x1b

//Variables globales

dynamixel::PortHandler *portHandler;

dynamixel::PacketHandler *packetHandler;


int getch() {
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

int kbhit(void) {
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
void printError(int dxl_comm_result, uint8_t dxl_error){
	if (dxl_comm_result != COMM_SUCCESS)
    {
      printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    }
    else if (dxl_error != 0)
    {
      printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    }
}

void lecture(){
  while(1){
    printf("\n================================\nChoix ID de lecture (1 à 5)\n1 -> BASE\n2 -> BAS du BRAS\n3 -> MILIEU du BRAS\n4 -> HAUT du BRAS\n5 -> PINCE\n(Echap pour revenir en arrière)\n");
    int chr = getch();

    //ID du moteur
    int lecture_id = 0;

    int32_t dxl_lecture = 0;  

    int dxl_comm_result = COMM_TX_FAIL;              // Communication result
    uint8_t dxl_error = 0;                           // DYNAMIXEL error


    if (chr == ESC_ASCII_VALUE)
      break;

    switch( chr )
    {
    case '1' :
        lecture_id=11;
        printf("--------------Lecture des données de BASE--------------\n");
        break;
    case '2' :
        lecture_id=12;
        printf("--------------Lecture des données de BAS du BRAS--------------\n");
        break;
    case '3' :
        lecture_id=13;
        printf("--------------Lecture des données de MILIEU du BRAS--------------\n");
        break;
    case '4' :
        lecture_id=14;
        printf("--------------Lecture des données de HAUT du BRAS--------------\n");
        break;
    case '5' :
        lecture_id=15;
        printf("--------------Lecture des données de PINCE--------------\n");
        break;
    default:
        lecture_id=15;
        printf("===========Lecture des données de PINCE===========\n");
        break;
    }

    if((lecture_id == 11)||(lecture_id == 12)||(lecture_id == 13)||(lecture_id == 14)||(lecture_id == 15)){

      std::string lecture_str;

      lecture_str = "Present position";
      dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, lecture_id, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
      printError(dxl_comm_result, dxl_error);
      printf("%s: %03d\n", lecture_str.c_str(), dxl_lecture);

      lecture_str = "Min position limit";
      dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, lecture_id, ADDR_MIN_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
      printError(dxl_comm_result, dxl_error);
      printf("%s: %03d\n", lecture_str.c_str(), dxl_lecture);

      lecture_str = "Max position limit";
      dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, lecture_id, ADDR_MAX_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
      printError(dxl_comm_result, dxl_error);
      printf("%s: %03d\n", lecture_str.c_str(), dxl_lecture);

      lecture_str = "Goal position";
      dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, lecture_id, ADDR_GOAL_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
      printError(dxl_comm_result, dxl_error);
      printf("%s: %03d\n", lecture_str.c_str(), dxl_lecture);
      /*
      if (dxl_comm_result != COMM_SUCCESS) {
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
      }
      else if (dxl_error != 0) {
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
      }
      */
    }
  }

}


void parametrer(){


    printf("\n================================\nChoix ID de paramètres (1 à 5)\n1 -> BASE\n2 -> BAS du BRAS\n3 -> MILIEU du BRAS\n4 -> HAUT du BRAS\n5 -> PINCE\n(Echap pour revenir en arrière)\n");
    int chr = getch();
    int lecture_id = 0;
    int lecture_addr = 0; //Adresse lu sur le moteur

    int32_t dxl_lecture = 0;  
    int dxl_comm_result = COMM_TX_FAIL;              // Communication result
    uint8_t dxl_error = 0;                           // DYNAMIXEL error


    int dtbase = 20;


    switch( chr )
    {
    case '1' :
        lecture_id=11;
        printf("--------------Paramétrer des données de BASE--------------\n");
        break;
    case '2' :
        lecture_id=12;
        printf("--------------Paramétrer des données de BAS du BRAS--------------\n");
        break;
    case '3' :
        lecture_id=13;
        printf("--------------Paramétrer des données de MILIEU du BRAS--------------\n");
        break;
    case '4' :
        lecture_id=14;
        printf("--------------Paramétrer des données de HAUT du BRAS--------------\n");
        break;
    case '5' :
        lecture_id=15;
        printf("--------------Paramétrer des données de PINCE--------------\n");
        break;
    default:
        lecture_id=15;
        printf("===========Paramétrer des données de PINCE===========\n");
        break;
    }



  std::string lecture_str;
  while(1){
    int dt = 0;

    chr = getch();
    if (chr == ESC_ASCII_VALUE)
      break;

    switch(chr)
      {      
      case 'a':
        lecture_str = "Min position";
        lecture_addr = ADDR_MIN_POSITION;
        dt = dtbase;
        break;
      case 'q':
        lecture_str = "Min position";
        lecture_addr = ADDR_MIN_POSITION;
        dt = -dtbase;
        break;
      case 'z':
        lecture_str = "Max position";
        lecture_addr = ADDR_MAX_POSITION;
        dt = dtbase;
        break;
      case 's':
        lecture_str = "Max position";
        lecture_addr = ADDR_MAX_POSITION;
        dt = -dtbase;
        break;
      case 'e':
        lecture_str = "Goal position";
        lecture_addr = ADDR_GOAL_POSITION;
        dt = dtbase;
        break;
      case 'd':
        lecture_str = "Goal position";
        lecture_addr = ADDR_GOAL_POSITION;
        dt = -dtbase;
        break;
      }


    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, lecture_id, lecture_addr, (uint32_t*)&dxl_lecture, &dxl_error);
    printError(dxl_comm_result, dxl_error);
    printf("%s: %03d\n", lecture_str.c_str(), dxl_lecture);

    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, lecture_id, lecture_addr, dxl_lecture + dt, &dxl_error);
    printError(dxl_comm_result, dxl_error); 
  }
}

void manette(){
  Torque_enable_all();

  const char *device;
  int js;

  int joystick1_x = 0;
  int joystick1_y = 0; 
  /*
  int joystick2_x = 0;
  int joystick2_y = 0;
  */

  device = "/dev/input/js0";
  js = open(device, O_RDONLY);

  if (js == -1)
      printf("Could not find the controller");

  struct js_event *event;


  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error
  int lecture_addr = ADDR_PRESENT_POSITION;


  int32_t pos_pince;
  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_PINCE, lecture_addr, (uint32_t*)&pos_pince, &dxl_error);
/*
  int32_t pos_base;
  int32_t pos_bras1;
  int32_t pos_bras2;
  int32_t pos_bras3;

  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BASE, lecture_addr, (uint32_t*)&pos_base, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  printf("%d: %03d\n", DXL_ID_BASE, pos_base);

  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, lecture_addr, (uint32_t*)&pos_bras1, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  printf("%d: %03d\n", DXL_ID_BRAS1, pos_bras1);
  
  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, lecture_addr, (uint32_t*)&pos_bras2, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  printf("%d: %03d\n", DXL_ID_BRAS2, pos_bras2);
  
  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS3, lecture_addr, (uint32_t*)&pos_bras3, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  printf("%d: %03d\n", DXL_ID_BRAS3, pos_bras3);
  
  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_PINCE, lecture_addr, (uint32_t*)&pos_pince, &dxl_error);
  printError(dxl_comm_result, dxl_error);
  printf("%d: %03d\n", DXL_ID_PINCE, pos_pince);*/

ssize_t bytes;
  int quit = 1;
    while (quit)
    {
        bytes = read(js, event, sizeof(*event));
        //printf("Joystick 2 (%d,%d) \n"  , joystick2_x, joystick2_y);
        switch (event->type)
        {
            case JS_EVENT_BUTTON:
                //printf("Button %u %s\n", event->number, event->value ? "pressed" : "released");
                //quit = 0;
                break;  
            case JS_EVENT_AXIS:
                if (  event -> number == 0)//event-> number < 5 && event-> number > 1)
                {
                    //printf("Joystick%u %i \n", event-> number, event->value);
                    joystick1_x = int(event->value / 300);

                }

                if (  event -> number == 1)//event-> number < 5 && event-> number > 1)
                {
                    //printf("Joystick%u %i \n", event-> number, event->value);
                    joystick1_y = int((event->value *-1)/300);
                }

                if (  event -> number == 3)//event-> number < 5 && event-> number > 1)
                {
                    //printf("Joystick%u %i \n", event-> number, event->value);
                    //joystick2_x = int((event->value )/100);
                }

                if (  event -> number == 4)//event-> number < 5 && event-> number > 1)
                {
                    //printf("Joystick%u %i \n", event-> number, event->value);
                    //joystick2_y = int((event->value *-1)/100);
                }
                /*
                printf("Joystick 1 (%d,%d)     ", joystick1_x/30, joystick1_y/30);
                printf("Joystick 2 (%d,%d) \n"  , joystick2_x, joystick2_y);
                */
            default:
                /* Ignore init events. */
                break;
        }
        fflush(stdout);
//    printError(dxl_comm_result, dxl_error);
//    printf("%d: %03d\n", DXL_ID_PINCE, pos_pince);
      packetHandler->write4ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_GOAL_POSITION, pos_pince + joystick1_x, &dxl_error);
//    printError(dxl_comm_result, dxl_error); 

        //quit = 0;
    }

  close(js);
}


void bouger(){

    printf("\n================================\n(Echap pour revenir en arrière)\n");
    int chr;
    int lecture_id = 0;

    int dt;
    int dtbase = 40;

    int32_t dxl_lecture = 0;  // Read 4 byte Position data
    int dxl_comm_result = COMM_TX_FAIL;              // Communication result
    uint8_t dxl_error = 0;                           // DYNAMIXEL error

    Torque_enable_all();

  while(1){
    chr = getch();
    
    dt = 0;
    
    if (chr == ESC_ASCII_VALUE)
      break;

    switch(chr)
    {      
      case 'a':
        lecture_id = DXL_ID_BASE;
        dt = dtbase;
        break;
      case 'q':
        lecture_id = DXL_ID_BASE;
        dt = -dtbase;
        break;
      case 'z':
        lecture_id = DXL_ID_BRAS1;
        dt = dtbase;
        break;
      case 's':
        lecture_id = DXL_ID_BRAS1;
        dt = -dtbase;
        break;
      case 'e':
        lecture_id = DXL_ID_BRAS2;
        dt = dtbase;
        break;
      case 'd':
        lecture_id = DXL_ID_BRAS2;
        dt = -dtbase;
        break;
      case 'r':
        lecture_id = DXL_ID_BRAS3;
        dt = dtbase;
        break;
      case 'f':
        lecture_id = DXL_ID_BRAS3;
        dt = -dtbase;
        break;
      case 't':
        lecture_id = DXL_ID_PINCE;
        dt = dtbase;
        break;
      case 'g':
        lecture_id = DXL_ID_PINCE;
        dt = -dtbase;
        break;
    }

    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, lecture_id, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
    printError(dxl_comm_result, dxl_error);

    printf("[ID:%d]Present Position: %03d\n",lecture_id, dxl_lecture);

    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, lecture_id, ADDR_GOAL_POSITION, dxl_lecture + dt, &dxl_error);
    printError(dxl_comm_result, dxl_error);


  }

  Torque_disable_all();
  
}

int main() {
  // Initialize PortHandler instance
  // Set the port path
  // Get methods and members of PortHandlerLinux or PortHandlerWindows
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);

  // Initialize PacketHandler instance
  // Set the protocol version
  // Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
  packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);


  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  int dxl_goal_position[2] = {MINIMUM_POSITION_LIMIT, MAXIMUM_POSITION_LIMIT};         // Goal position

  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  int32_t dxl_lecture = 0;  


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

  printf("Lancement du programme.\n");
  while(1) {
    printf("\n============================================\nb -> bouger\nl -> lire\np -> paramétrer\nm -> manette\n");
    int chr = getch();

    if (chr == ESC_ASCII_VALUE)
      break;
    
    switch( chr )
    {
    case 'b' :
        bouger();
        break;
    case 'l' :
        lecture();
        break;
    case 'p' :
        parametrer();
        break;
    case 'm':
        manette();
    default:
        break;
    }
  }


  Torque_disable_all();

  // Close port
  portHandler->closePort();
  return 0;
}
