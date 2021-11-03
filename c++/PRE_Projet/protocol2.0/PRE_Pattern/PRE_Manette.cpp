#include "Sample.cpp"
#include <unistd.h>
//#include "manette/controle.hpp"
//#include "manette/controle.cpp"
//#include "controle.cpp"
#include "position/getPosition.cpp"
#include "position/calculateAngle.cpp"

//Variables globales
//initialisé dans moteur.cpp
dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;

#define INIT_POSE1    2280
#define INIT_POSE2    2040
#define INIT_POSE3    1850

int GOAL_POSE1=2280;
int GOAL_POSE2=2040;
int GOAL_POSE3=2850;
int GOAL_POSE_PINCE=1500;


void lecture(){
  while(1){
    printf("\n================================\nLecture\n");
    int chr = getch();

    if (chr == ESC_ASCII_VALUE)
      break;

    std::string lecture_str;

    lecture_str = "Present position";
    printf("11: %s: %03d\n", lecture_str.c_str(), readBase());
    printf("12: %s: %03d\n", lecture_str.c_str(), readBras1());
    printf("13: %s: %03d\n", lecture_str.c_str(), readBras2());
    printf("14: %s: %03d\n", lecture_str.c_str(), readBras3());
    printf("15: %s: %03d\n", lecture_str.c_str(), readPince());
  }
}

void thibaut(){

  int taille = 30;

Torque_enable_all();

  Positions tab_pose[taille];

  for (int i =0; i<taille;i++){
    tab_pose[i].base = 1000;
    tab_pose[i].bras1 = 2048;
    tab_pose[i].pince = 1000;
  }

  tab_pose[0].bras2=2402;tab_pose[0].bras3=1572;
  tab_pose[1].bras2=2367;tab_pose[1].bras3=1539;
  tab_pose[2].bras2=2340;tab_pose[2].bras3=1499;
  tab_pose[3].bras2=2320;tab_pose[3].bras3=1453;
  tab_pose[4].bras2=2308;tab_pose[4].bras3=1403;
  tab_pose[5].bras2=2303;tab_pose[5].bras3=1350;
  tab_pose[6].bras2=2305;tab_pose[6].bras3=1296;
  tab_pose[7].bras2=2314;tab_pose[7].bras3=1242;
  tab_pose[8].bras2=2331;tab_pose[8].bras3=1193;
  tab_pose[9].bras2=2354;tab_pose[9].bras3=1149;
  tab_pose[10].bras2=2389;tab_pose[10].bras3=1114;

  tab_pose[11].bras2=2427;tab_pose[11].bras3=1091;
  tab_pose[12].bras2=2479;tab_pose[12].bras3=1084;
  tab_pose[13].bras2=2540;tab_pose[13].bras3=1096;
  tab_pose[14].bras2=2609;tab_pose[14].bras3=1129;
  tab_pose[15].bras2=2681;tab_pose[15].bras3=1181;
  tab_pose[16].bras2=2749;tab_pose[16].bras3=1247;
  tab_pose[17].bras2=1295;tab_pose[17].bras3=2782;
  tab_pose[18].bras2=1399;tab_pose[18].bras3=2820;
  tab_pose[19].bras2=1429;tab_pose[19].bras3=2838;
  tab_pose[20].bras2=1483;tab_pose[20].bras3=2836;

  tab_pose[21].bras2=1527;tab_pose[21].bras3=2817;
  tab_pose[22].bras2=1561;tab_pose[22].bras3=2785;
  tab_pose[23].bras2=1587;tab_pose[23].bras3=2743;
  tab_pose[24].bras2=1605;tab_pose[24].bras3=2694;
  tab_pose[25].bras2=1616;tab_pose[25].bras3=2642;
  tab_pose[26].bras2=1620;tab_pose[26].bras3=2588;
  tab_pose[27].bras2=1617;tab_pose[27].bras3=2534;
  tab_pose[28].bras2=1607;tab_pose[28].bras3=2483;
  tab_pose[29].bras2=2444;tab_pose[29].bras3=1597;

  positionBase(tab_pose[0].base);
  positionBras1(tab_pose[0].bras1);
  positionBras2(tab_pose[0].bras2);
  positionBras3(tab_pose[0].bras3);
  positionPince(tab_pose[0].pince);

  printf("Attente \n");

  profileVelocity(110,110,110,110,110);
  getch();

  printf("Début \n");
  for (int i=0; i<taille;i++){
      positionBase(tab_pose[i].base);
      positionBras1(tab_pose[i].bras1);
      positionBras2(tab_pose[i].bras2);
      positionBras3(tab_pose[i].bras3);
      positionPince(tab_pose[i].pince);

      printf("%d", i);

      usleep(50000);

  }


  profileVelocity(30,30,30,30,30);

  printf("Fin \n");
}

void enregistrer(){


  printf("Libérer les moteurs = appuie sur une touche\n");
  getch();

  Torque_disable_all();


  printf("Début enregistrement = appuie sur une touche\n");
  getch();

  Torque_enable(DXL_ID_PINCE);

  int taille = 2500;

  int i = 0;
  Positions tab_pos[taille];
  
  while(i < taille){
    Positions p;

    printf("Enregistrement positon: %d\n", i);

    p.base = readBase();
    p.bras1 = readBras1();
    p.bras2 = readBras2();
    p.bras3 = readBras3();
    p.pince = readPince();

    tab_pos[i] = p;



    sleep(0.1);

    i++;
  }


  printf("== Controle des moteurs et reprise position initiale = appuie sur une touche ==\n");
  getch();
  Torque_enable_all();

  sleep(1);

  positionBase(tab_pos[0].base);
  positionBras1(tab_pos[0].bras1);
  positionBras2(tab_pos[0].bras2);
  positionBras3(tab_pos[0].bras3);
  positionPince(tab_pos[0].pince);


  printf("== Reproduire la chorégraphie = appuie sur une touche ==\n\n");
  getch();


  i = 0;
  int quit = 1;

  while(quit){
    profileVelocity(160,160,160,160,160);
    while(i < taille){

      printf("aller positon: %d\n", i);

      positionBase(tab_pos[i].base);
      positionBras1(tab_pos[i].bras1);
      positionBras2(tab_pos[i].bras2);
      positionBras3(tab_pos[i].bras3);
      positionPince(tab_pos[i].pince);

      sleep(0.1);

      i++;



    }
    i=0;


    profileVelocity(30,30,30,30,30);

    printf("== Mise en position initial de chorégraphie = appuie sur une touche ==\n\n");
    getch();


    positionBase(tab_pos[0].base);
    positionBras1(tab_pos[0].bras1);
    positionBras2(tab_pos[0].bras2);
    positionBras3(tab_pos[0].bras3);
    positionPince(tab_pos[0].pince);


    printf("== Reproduire la chorégraphie = appuie sur une touche ou Echap ==\n\n");
    int chr = getch();
    if(chr == ESC_ASCII_VALUE) quit = 0;
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

  int dt;
  int dtbase = 40;

  int dxl_lecture = 0;  // Read 4 byte Position data

  Torque_enable_all();

  while(1){
    chr = getch();
    dt = 0;
    
    if (chr == ESC_ASCII_VALUE)
      break;

    switch(chr)
    {      
      case 'a':
        dxl_lecture = mooveBase(dtbase);
        printf("[ID:%d]Present Position: %03d\n",DXL_ID_BASE, dxl_lecture);
        break;
      case 'q':
        dxl_lecture = mooveBase(-dtbase);
        printf("[ID:%d]Present Position: %03d\n",DXL_ID_BASE, dxl_lecture);
        break;
      case 'z':
        dxl_lecture = mooveBras1(dtbase);
        printf("[ID:%d]Present Position: %03d\n",DXL_ID_BRAS1, dxl_lecture);
        break;
      case 's':
        dxl_lecture = mooveBras1(-dtbase);
        printf("[ID:%d]Present Position: %03d\n",DXL_ID_BRAS1, dxl_lecture);
        break;
      case 'e':
        dxl_lecture = mooveBras2(dtbase);
        printf("[ID:%d]Present Position: %03d\n",DXL_ID_BRAS2, dxl_lecture);
        break;
      case 'd':
        dxl_lecture = mooveBras2(-dtbase);
        printf("[ID:%d]Present Position: %03d\n",DXL_ID_BRAS2, dxl_lecture);
        break;
      case 'r':
        dxl_lecture = mooveBras3(dtbase);
        printf("[ID:%d]Present Position: %03d\n",DXL_ID_BRAS3, dxl_lecture);
        break;
      case 'f':
        dxl_lecture = mooveBras3(-dtbase);
        printf("[ID:%d]Present Position: %03d\n",DXL_ID_BRAS3, dxl_lecture);
        break;
      case 't':
        dxl_lecture = moovePince(dtbase);
        printf("[ID:%d]Present Position: %03d\n",DXL_ID_PINCE, dxl_lecture);
        break;
      case 'g':
        dxl_lecture = moovePince(-dtbase);
        printf("[ID:%d]Present Position: %03d\n",DXL_ID_PINCE, dxl_lecture);
        break;
    }


  }
}


void readPosition(){
  while(1){
    getPositionPince3D();
  }
}

void goTO(){
  Angles anglesR=calculate_angles(0.240,0.180);
  printf("Angles alpha : %g, beta : %g, gamma : %g\n", anglesR.alpha, anglesR.beta, anglesR.gamma);
  Angles anglesD = anglesToDegree(anglesR);
  printf("Angles alpha : %g, beta : %g, gamma : %g\n", anglesD.alpha, anglesD.beta, anglesD.gamma);
  Angles anglesP = anglesToPosition(anglesR);
  printf("Angles alpha : %g, beta : %g, gamma : %g\n", anglesP.alpha, anglesP.beta, anglesP.gamma);
  int quit = 1;
  
  Torque_enable_all();
  while(quit){
    printf("Pret pour lacher les moteurs ? Appuie sur Echap\n");
    int chr = getch();
    if (chr == ESC_ASCII_VALUE)
      quit = 0;
  }
  goToPosition(anglesP);

  Position posPince = getPositionPince3D();
  printf("Position  x : %g, y : %g, z : %g\n", posPince.x, posPince.y, posPince.z);

}





int main() {

  if(!init());
  //  return 0;

  printf("Lancement du programme.\n");
  while(1) {
    printf("\n============================================\nb -> bouger\nl -> lire\np -> paramétrer\nm -> manette\nk -> Leap\n");
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
    case 'k' :
    	  leap();
    	  break;
    case 'e':
        enregistrer();
        break;
    case 'i' :
        goTO();
        break;
    case 'u' :
        readPosition();
    case 't':
        thibaut();
        break;
    default:
        break;
    }
  }

  
  
position();

  int quit = 1;
  while(quit){
    printf("Pret pour lacher les moteurs ? Appuie sur Echap\n");
    int chr = getch();
    if (chr == ESC_ASCII_VALUE)
      quit = 0;
  }
  Torque_disable_all();

  
  printf("===== FIN DU PROGRAMME =====\n");

  // Close port
  portHandler->closePort();
  return 0;
}
