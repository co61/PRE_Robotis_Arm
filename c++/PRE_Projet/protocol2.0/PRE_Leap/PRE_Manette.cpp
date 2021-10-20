#include "Sample.cpp"
//Variables globales

int GOAL_POSE1=2280;
int GOAL_POSE2=2040;
int GOAL_POSE3=2850;
int GOAL_POSE_PINCE=1500;


//initialisé dans moteur.cpp
dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;

struct Positions{
    int base;
    int bras1;
    int bras2; 
    int bras3;
    int pince;
};


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

  Torque_disable_all();

  printf("Début enregistrement");
  int chr = getch();

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


  printf("Enregistrement Termine");
  Torque_enable_all();

  positionBase(tab_pos[0].base);
  positionBras1(tab_pos[0].bras1);
  positionBras2(tab_pos[0].bras2);
  positionBras3(tab_pos[0].bras3);
  positionPince(tab_pos[0].pince);
  chr = getch();


  i = 0;
  
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

////////////////////////////////////////////////////
// Pose le bras au sol avant de disable le Torque //
////////////////////////////////////////////////////
void position(){
  //Controle les moteurs
  Torque_enable_all();

  positionBras1(GOAL_POSE1);
  positionBras2(GOAL_POSE2);
  positionBras3(GOAL_POSE3);
  sleep(2);
  positionPince(GOAL_POSE_PINCE);

  printf("POSITION TERMINE\n");
}



void leap(){
  // Create a sample listener and controller
  SampleListener listener;
  Controller controller;

  Torque_enable_all();
  // Have the sample listener receive events from the controller
  controller.addListener(listener);

  //if (argc > 1 && strcmp(argv[1], "--bg") == 0)
  //  vef
  controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  Torque_disable_all();
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
                position();
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
  position();
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
        /*
    case '1':
      GOAL_POSE1=2000;
      GOAL_POSE2=2000;
      GOAL_POSE3=2000;
      position();
      break;
    case '2':
      GOAL_POSE1=1825;
      GOAL_POSE2=2500;
      GOAL_POSE3=2700;
      GOAL_POSE_PINCE=2300;
      position();
      break;
    case '3':
      GOAL_POSE1=2700;
      GOAL_POSE2=2014;
      GOAL_POSE3=1300;
      GOAL_POSE_PINCE=2000;
      position();
      break;
      */
    default:
        break;
    }
  }



  // Close port
  portHandler->closePort();
  return 0;
}
