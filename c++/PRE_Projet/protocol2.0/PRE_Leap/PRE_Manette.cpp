
#include "Sample.cpp"
//Variables globales

int GOAL_POSE1=2280;
int GOAL_POSE2=2040;
int GOAL_POSE3=2850;


//initialisé dans moteur.cpp
dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;


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
      printf("11: %s: %03d\n", lecture_str.c_str(), dxl_lecture);


      dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS1, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
      printError(dxl_comm_result, dxl_error);
      printf("12: %s: %03d\n", lecture_str.c_str(), dxl_lecture);


      dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS2, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
      printError(dxl_comm_result, dxl_error);
      printf("13: %s: %03d\n", lecture_str.c_str(), dxl_lecture);


      dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_BRAS3, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
      printError(dxl_comm_result, dxl_error);
      printf("14: %s: %03d\n", lecture_str.c_str(), dxl_lecture);


      dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_PRESENT_POSITION, (uint32_t*)&dxl_lecture, &dxl_error);
      printError(dxl_comm_result, dxl_error);
      printf("15: %s: %03d\n", lecture_str.c_str(), dxl_lecture);

      
      /*
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


void pose_init(int &dt1, int &dt2, int &dt3){
  int dxl_comm_result = COMM_TX_FAIL;              // Communication result
  uint8_t dxl_error = 0;                           // DYNAMIXEL error

  int32_t dxl_lecture = 0;
  int delta = 50;

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

  int dxl_lecture1 = 0;
  int dxl_lecture2 = 0;
  int dxl_lecture3 = 0;

  //Ouverture pince
  dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_PINCE, ADDR_GOAL_POSITION, 1740, &dxl_error);

  while(goal){
    //Récupération de la position des moteurs
    if((dxl_lecture1 > GOAL_POSE1 + 20)||(dxl_lecture1 < GOAL_POSE1 - 20))
      dxl_lecture1 = mooveBras1(dt1);
    else
      done1 = 1;

    if((dxl_lecture2 > GOAL_POSE2 + 20)||(dxl_lecture2 < GOAL_POSE2 - 20))
      dxl_lecture2 = mooveBras2(dt2);
    else
      done2 = 1;

    if((dxl_lecture3 > GOAL_POSE3 + 20)||(dxl_lecture3 < GOAL_POSE3 - 20))
      dxl_lecture3 = mooveBras3(dt3);
    else
      done3 = 1;

    sleep(0.2);
    printf("IN:  %d  %d  %d\n", done1, done2, done3);
    printf("POS:  %d  %d  %d\n", dxl_lecture1, dxl_lecture2, dxl_lecture3);

    if((done1)&&(done2)&&(done3))
      goal = 0;
  }
}

////////////////////////////////////////////////////
// Pose le bras au sol avant de disable le Torque //
////////////////////////////////////////////////////
void pose(){
  //Controle les moteurs
  Torque_enable_all();

  int dt1, dt2, dt3;

  //Récupération du sens de rotation voulue
  pose_init(dt1, dt2, dt3);

  //Mouvement des moteurs
  pose_moove(dt1, dt2, dt3);

  //Relache les moteurs
  //Torque_disable_all();

  printf("INIT POSE TERMINE\n");

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

void leap(){
  // Create a sample listener and controller
  SampleListener listener;
  Controller controller;

  Torque_enable(DXL_ID_PINCE);
  // Have the sample listener receive events from the controller
  controller.addListener(listener);

  //if (argc > 1 && strcmp(argv[1], "--bg") == 0)
  //  controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  Torque_disable(DXL_ID_PINCE);
  //return 0;

}


void manette(){
  Torque_enable_all();
  
  int dt_base = 0;
  int dt_bras1 = 0;
  int dt_bras2 = 0;
  int dt_bras3 = 0;
  int dt_pince = 0;

  //Variables Joystick
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
    case 'k' :
    	  leap();
    	  break;
    case '1':
      GOAL_POSE1=2280;
      GOAL_POSE2=2040;
      GOAL_POSE3=2850;
      pose();
      break;
    case '2':
      GOAL_POSE1=1825;
      GOAL_POSE2=2500;
      GOAL_POSE3=2700;
      pose();
      break;
    case '3':
      GOAL_POSE1=2791;
      GOAL_POSE2=2014;
      GOAL_POSE3=1300;
      pose();
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
