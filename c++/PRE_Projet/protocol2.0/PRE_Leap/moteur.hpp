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


// Use the actual port assigned to the U2D2.
// ex) Windows: "COM*", Linux: "/dev/ttyUSB*", Mac: "/dev/tty.usbserial-*"
#define DEVICENAME  "/dev/ttyUSB0"

#define TORQUE_ENABLE                   1
#define TORQUE_DISABLE                  0
#define DXL_MOVING_STATUS_THRESHOLD     20  // DYNAMIXEL moving status threshold
#define ESC_ASCII_VALUE                 0x1b

