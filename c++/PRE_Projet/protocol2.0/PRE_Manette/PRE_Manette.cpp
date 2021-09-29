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

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fcntl.h> //fuction open
#include <stdio.h>
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
  #define ADDR_GOAL_SPEED             104
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


#define GOAL_POSE1    2280
#define GOAL_POSE2    2040
#define GOAL_POSE3    2850

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
        printf("--------------Lecture des données de PINCE--------------\n");
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

  
}



///////////////////////////////////////////////////////////////////////////////////////////////////////
//Joystick lib
int read_event(int fd, struct js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    return -1;
}

size_t get_axis_count(int fd)
{
    __u8 axes;

    if (ioctl(fd, JSIOCGAXES, &axes) == -1)
        return 0;

    return axes;
}

size_t get_button_count(int fd)
{
    __u8 buttons;
    if (ioctl(fd, JSIOCGBUTTONS, &buttons) == -1)
        return 0;

    return buttons;
}

struct axis_state {
    short x, y;
};


size_t get_axis_state(struct js_event *event, struct axis_state axes[3])
{
    size_t axis = event->number / 2;

    if (axis < 3)
    {
        if (event->number % 2 == 0)
            axes[axis].x = event->value;
        else
            axes[axis].y = event->value;
    }

    return axis;
}

void pose_init(int &dt1, int &dt2, int &dt3){
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  int32_t dxl_lecture = 0;
  int delta = 30;

  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
  dt1 = (dxl_lecture > GOAL_POSE1) ? -delta : delta;
  
  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
  dt2 = (dxl_lecture > GOAL_POSE2) ? -delta : delta;
  
  dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
  dt3 = (dxl_lecture > GOAL_POSE3) ? -delta : delta;

}


void pose_moove(int dt1, int dt2, int dt3){

  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  int goal = 1;
  int done1 = 0;
  int done2 = 0;
  int done3 = 0;

  int32_t dxl_lecture1 = 0;
  int32_t dxl_lecture2 = 0;
  int32_t dxl_lecture3 = 0;

  //Ouverture pince
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_GOAL_POSITION, 1740, &dxl_error);

  while(goal){
    //Récupération de la position des moteurs
    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture1, &dxl_error);
    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture2, &dxl_error);
    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture3, &dxl_error);

    if((dxl_lecture1 > GOAL_POSE1 + 20)||(dxl_lecture1 < GOAL_POSE1 - 20))
      dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_GOAL_POSITION, dxl_lecture1 + dt1, &dxl_error);
    else
      done1 = 1;

    if((dxl_lecture2 > GOAL_POSE2 + 20)||(dxl_lecture2 < GOAL_POSE2 - 20))
      dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_GOAL_POSITION, dxl_lecture2 + dt2, &dxl_error);
    else
      done2 = 1;

    if((dxl_lecture3 > GOAL_POSE3 + 20)||(dxl_lecture3 < GOAL_POSE3 - 20))
      dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_GOAL_POSITION, dxl_lecture3 + dt3, &dxl_error);
    else
      done3 = 1;


    sleep(0.1);
    printf("IN:  %d  %d  %d\n", done1, done2, done3);
    printf("POS:  %d  %d  %d\n", dxl_lecture1, dxl_lecture2, dxl_lecture3);

    if(done1 == 1){
      if(done2 == 1){
        if(done3 == 1){
          goal = 0;
        }
      }
    }
  }
}

void pose(){
  //Controle les moteurs
  Torque_enable_all();

  int dt1, dt2, dt3;

  //Récupération du sens de rotation voulue
  pose_init(dt1, dt2, dt3);

  //Mouvement des moteurs
  pose_moove(dt1, dt2, dt3);

  //Relache les moteurs
  Torque_disable_all();

  printf("INIT POSE TERMINE\n");

}

////////////////////////////////////////////////////////////////////////////////////////////////
void moteur_dt(int dt_base, int dt_bras1, int dt_bras2, int dt_bras3, int dt_pince){

  int32_t dxl_lecture = 0;
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result

  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  if(dt_pince != 0){
    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_GOAL_POSITION, dxl_lecture + dt_pince, &dxl_error);
    printf("Mouvement moteur: %d, Position: %d\n", DXL_ID_PINCE, dxl_lecture + dt_pince);
  }

  if(dt_bras1 != 0){
    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_GOAL_POSITION, dxl_lecture + dt_bras1, &dxl_error);
    printf("Mouvement moteur: %d, Position: %d\n", DXL_ID_BRAS1, dxl_lecture + dt_bras1);
  }

  if(dt_bras2 != 0){
    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_GOAL_POSITION, dxl_lecture + dt_bras2, &dxl_error);
    printf("Mouvement moteur: %d, Position: %d\n", DXL_ID_BRAS2, dxl_lecture + dt_bras2);
  }

  if(dt_bras3 != 0){
    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_GOAL_POSITION, dxl_lecture + dt_bras3, &dxl_error);
    printf("Mouvement moteur: %d, Position: %d\n", DXL_ID_BRAS3, dxl_lecture + dt_bras3);
  }

  if(dt_base != 0){
    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BASE, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_BASE, ADDR_GOAL_POSITION, dxl_lecture - dt_base, &dxl_error);
    printf("Mouvement moteur: %d, Position: %d\n", DXL_ID_BASE, dxl_lecture - dt_base);
  }

}


void manette(){

  Torque_enable_all();
  
  int dt_base = 0;
  int dt_bras1 = 0;
  int dt_bras2 = 0;
  int dt_bras3 = 0;
  int dt_pince = 0;


  const char *device;
  int js;
  struct js_event event;
  struct axis_state axes[3] = {0};
  size_t axis;



  device = "/dev/input/js0";

  js = open(device, O_NONBLOCK);

  if (js == -1)
      perror("Could not open joystick");

  /* This loop will exit if the controller is unplugged. */
  int quit = 1;
  while (quit)
  {
    if(read_event(js, &event) == 0){
      switch (event.type)
      {
          case JS_EVENT_BUTTON:
              printf("Button %u %s\n", event.number, event.value ? "pressed" : "released");
              if ((event.number == 0)&&(event.value)){
                pose();
              }
              else if((event.number == 1)&&(event.value)){

              }
              else if((event.number == 2)&&(event.value)){
                
              }
              else if((event.number == 3)&&(event.value)){
                
              }
              else if((event.number == 6)&&(event.value)){
                quit = 0;
              }
              break;
          case JS_EVENT_AXIS:
              axis = get_axis_state(&event, axes);
              if (axis < 7){
                  printf("Axis %zu at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);
                  if(axis == 0){
                    if((int(axes[axis].y/3000)>5)||(int(axes[axis].y/3000)<-5))
                      dt_bras2 = int(axes[axis].y/3000)*3;
                    else
                      dt_bras2 = 0;

                    if((int(axes[axis].x/3000)>5)||(int(axes[axis].x/3000)<-5))
                      dt_bras1 = int(axes[axis].x/3000)*4;
                    else
                      dt_bras1 = 0;
                  }
                  else if(axis == 1){
                    if((int(axes[axis].y/3000)>5)||(int(axes[axis].y/3000)<-5))
                      dt_base = int(axes[axis].y/3000)*3;
                    else
                      dt_base = 0;
                    if((int(axes[axis].x)) > 0)
                      dt_pince = -10;
                    else
                      dt_pince = 0;
                    }
                  else if(axis == 2){
                    if((int(axes[axis].x/3000)>5)||(int(axes[axis].x/3000)<-5))
                      dt_bras3 = int(axes[axis].x/3000)*3;
                    else
                      dt_bras3 = 0;
                    
                    if((int(axes[axis].y))  > 0)
                      dt_pince = 10;
                    else
                      dt_pince = 0;
                    }
              }

              break;
          default:
              /* Ignore init events. */
              break;
      }
    }
      
    fflush(stdout);


    moteur_dt(dt_base, dt_bras1, dt_bras2, dt_bras3, dt_pince);
    
  }
  //Fermeture du joystick
  close(js);
  pose();
}

int init(){
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

  //pose();
  // Disable DYNAMIXEL Torque
  Torque_disable_all();

  return 1;

}

int main() {

  if(!init())
    return 0;

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
    case 'm' :
    	manette();
    	break;
    default:
        break;
    }
  }


  pose();

  // Close port
  portHandler->closePort();
  return 0;
}
