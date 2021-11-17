// pou install la lib en root,  sudo make install

// #include "manette/controle.cpp"

#include "Sample.cpp"
//#include "manette/controle.hpp"
//#include "manette/controle.cpp"
//#include "controle.cpp"

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QVBoxLayout>
//Variables globales
//initialisé dans moteur.cpp
dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;

#define INIT_POSE1    2280
#define INIT_POSE2    2040
#define INIT_POSE3    2850

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

  int taille = 199;

  Torque_enable_all();

  Positions tab_pose[taille];
int angle1[199] = {2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2053,2058,2064,2069,2074,2080,2086,2092,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2347,2356,2365,2376,2376,2385};

int angle2[199] = {2351,2351,2352,2352,2352,2353,2353,2353,2353,2353,2353,2353,2353,2353,2353,2353,2353,2353,2352,2352,2351,2351,2351,2350,2349,2349,2348,2348,2347,2346,2345,2344,2344,2343,2342,2341,2340,2339,2338,2336,2335,2334,2333,2332,2330,2329,2327,2326,2325,2323,2322,2320,2318,2317,2315,2313,2312,2310,2308,2306,2304,2302,2300,2298,2296,2294,2292,2290,2288,2286,2284,2281,2279,2277,2274,2272,2269,2267,2264,2262,2259,2256,2254,2251,2248,2245,2242,2239,2236,2233,2230,2227,2224,2221,2217,2214,2211,2207,2204,2200,2196,2193,2189,2185,2181,2177,2173,2169,2165,2161,2156,2152,2147,2142,2138,2133,2128,2122,2117,2112,2106,2100,2094,2088,2082,2075,2068,2061,2054,2046,2038,2029,2020,2010,2000,1988,1975,1961,1943,1920,1864,1869,1874,1879,1885,1890,1896,1902,1907,2163,2160,2157,2153,2150,2146,2143,2139,2136,2132,2128,2124,2120,2116,2112,2108,2104,2099,2095,2090,2085,2081,2075,2070,2065,2060,2054,2048,2042,2036,2029,2022,2015,2008,2000,1992,1983,1974,1964,1953,1940,1926,1910,1889,1855,1864,1873,1884,1852,1861};

int angle3[199] = {1992,1997,2002,2008,2013,2019,2024,2029,2034,2040,2045,2050,2055,2060,2065,2070,2075,2081,2086,2091,2096,2101,2106,2111,2116,2120,2125,2130,2135,2140,2145,2150,2155,2160,2164,2169,2174,2179,2184,2188,2193,2198,2203,2208,2212,2217,2222,2227,2231,2236,2241,2246,2251,2255,2260,2265,2270,2274,2279,2284,2289,2293,2298,2303,2308,2313,2317,2322,2327,2332,2337,2342,2347,2351,2356,2361,2366,2371,2376,2381,2386,2391,2396,2401,2406,2411,2416,2421,2427,2432,2437,2442,2448,2453,2458,2464,2469,2475,2480,2486,2491,2497,2502,2508,2514,2520,2526,2532,2538,2544,2550,2556,2562,2569,2575,2582,2589,2595,2602,2609,2617,2624,2632,2639,2647,2655,2664,2672,2681,2690,2700,2710,2720,2732,2744,2756,2771,2787,2805,2830,2886,2881,2876,2871,2865,2859,2853,2847,2841,2428,2433,2439,2445,2450,2456,2462,2468,2473,2479,2485,2491,2498,2504,2510,2516,2523,2529,2536,2542,2549,2556,2563,2570,2577,2585,2592,2600,2608,2616,2624,2633,2642,2651,2661,2671,2681,2692,2704,2716,2730,2746,2764,2786,2821,2808,2794,2777,2810,2795};





  for (int i =0; i<taille;i++){
    tab_pose[i].base = 1000;
    tab_pose[i].bras1 = angle1[i];
    tab_pose[i].bras2 = angle2[i];
    tab_pose[i].bras3 = angle3[i];
    tab_pose[i].pince = 1000;
  }

  positionBase(tab_pose[0].base);
  positionBras1(tab_pose[0].bras1);
  positionBras2(tab_pose[0].bras2);
  positionBras3(tab_pose[0].bras3);
  positionPince(tab_pose[0].pince);

  printf("Attente \n");

  profileVelocity(70,70,70,70,70);
  getch();

  printf("Début \n");
  for (int i=0; i<taille;i++){
      positionBase(tab_pose[i].base);
      positionBras1(tab_pose[i].bras1);
      positionBras2(tab_pose[i].bras2);
      positionBras3(tab_pose[i].bras3);
      positionPince(tab_pose[i].pince);

      printf("%d", i);

      usleep(10000);

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
      positionBras1(tab_pos[i].bras1-10);
      positionBras2(tab_pos[i].bras2-10);
      positionBras3(tab_pos[i].bras3-10);
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
  Angles anglesR=calculate_angles(0.1,0.15,0.00);
  printf("Angles alpha : %g, beta : %g, gamma : %g, psi : %g\n", anglesR.alpha, anglesR.beta, anglesR.gamma, anglesR.psi);
  Angles anglesD = anglesToDegree(anglesR);
  printf("Angles alpha : %g, beta : %g, gamma : %g, psi : %g\n", anglesD.alpha, anglesD.beta, anglesD.gamma, anglesD.psi);
  Angles anglesP = anglesToPosition(anglesR);
  printf("Angles alpha : %g, beta : %g, gamma : %g, psi : %g\n", anglesP.alpha, anglesP.beta, anglesP.gamma, anglesP.psi);
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


void calvierLineaire(){
  printf("\n================================\n(Echap pour revenir en arrière)\n");
  int chr;
  Position posPince;
  Angles anglesR;
  Angles anglesP;
  int dt;
  int dtbase = 40;

  int dxl_lecture = 0;  // Read 4 byte Position data

  Torque_enable_all();
  while(1){
    chr = getch();
    dt = 0;
    
    if (chr == ESC_ASCII_VALUE)
      break;
    posPince = getPositionPince3D();
    printf("Position  x : %g, y : %g, z : %g\n", posPince.x, posPince.y, posPince.z);
    switch(chr)
    {      
      //forward
      case 'z':
        anglesR=calculate_angles(posPince.x, posPince.y, posPince.z,0.01);
        anglesP = anglesToPosition(anglesR);
        goToPosition(anglesP);
        break;
      //back
      case 's':
        anglesR=calculate_angles(posPince.x, posPince.y, posPince.z,-0.01);
        anglesP = anglesToPosition(anglesR);
        goToPosition(anglesP);
        break;
      //right
      case 'd':
        anglesR=calculate_angles(posPince.x, posPince.y, posPince.z);
        anglesP = anglesToPosition(anglesR, 15);
        goToPosition(anglesP);
        break;
      //left
      case 'q':
        anglesR=calculate_angles(posPince.x, posPince.y, posPince.z );
        anglesP = anglesToPosition(anglesR, -15);
        goToPosition(anglesP);
        break;

      //up
      case 't':
        anglesR=calculate_angles(posPince.x, posPince.y+0.01, posPince.z);
        anglesP = anglesToPosition(anglesR);
        goToPosition(anglesP,-15);
        break;
        //down
      case 'g':
        anglesR=calculate_angles(posPince.x, posPince.y-0.005, posPince.z);
        anglesP = anglesToPosition(anglesR);
        goToPosition(anglesP,-5);
        break;
      case 'f':
        moovePince(dtbase);
        break;
      case 'h':
        moovePince(-dtbase);
        break;
      
    }


  }
  

}


int main(int argv, char **args) {

  if(!init());
  //  return 0;

  printf("Lancement du programme.\n");
  while(1) {
    printf("\n============================================\nb -> bouger\nl -> lire\np -> paramétrer\nm -> manette\nk -> Leap\ne -> enregistrer\n");
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
    case 'C':
        calvierLineaire();
        break;
    case 'M':
        manetteLineaire();
        break;
    default:
        break;
    }
  }

	QApplication app(argv, args);

	QWidget fenetre;

	QGroupBox *groupe = new QGroupBox("Coucou");
	groupe->setCheckable(true);
	groupe->setChecked(false);
	groupe->setEnabled(true);

	QPushButton *bouton = new QPushButton("Manette");
	bouton->setEnabled(true);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget(bouton);
	groupe->setLayout(vbox);

  app.connect(bouton, SIGNAL(clicked()),SLOT(manette()));

	QVBoxLayout *vboxPrincipal = new QVBoxLayout(&fenetre);
	vboxPrincipal->addWidget(groupe);

	fenetre.show();
	return app.exec();
  /*
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
  */
}
