#include "Sample.cpp"
//#include "manette/controle.hpp"
//#include "manette/controle.cpp"
//#include "controle.cpp"
//Variables globales


//initialisé dans moteur.cpp
dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;

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

void enregistrer(){


  printf("Libérer les moteurs = appuie sur une touche\n");
  getch();

  Torque_disable_all();


  printf("Début enregistrement = appuie sur une touche\n");
  getch();

  int taille = 1500;

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

    sleep(0.3);

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

    while(i < taille){

      printf("aller positon: %d\n", i);

      positionBase(tab_pos[i].base);
      positionBras1(tab_pos[i].bras1);
      positionBras2(tab_pos[i].bras2);
      positionBras3(tab_pos[i].bras3);
      positionPince(tab_pos[i].pince);

      sleep(0.3);

      i++;



    }
    i=0;


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
    default:
        break;
    }
  }

  
  

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
