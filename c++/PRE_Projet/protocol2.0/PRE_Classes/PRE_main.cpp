
//Bibliothèques Qt
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QVBoxLayout>

//Include du projet
#include "moteur/moteur.cpp"
//Variables globales - initialisé dans moteur.cpp
dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;

#define INIT_POSE1    2280
#define INIT_POSE2    2040
#define INIT_POSE3    2850

int GOAL_POSE1=2280;
int GOAL_POSE2=2040;
int GOAL_POSE3=2850;
int GOAL_POSE_PINCE=1500;

Moteur base = Moteur(11);
Moteur bras1= Moteur(12);
Moteur bras2= Moteur(13);
Moteur bras3= Moteur(14);
Moteur pince= Moteur(15);

int main(int argc, char **argv) {


  base = Moteur(11);
  bras1 = Moteur(12);
  bras2 = Moteur(13);
  bras3 = Moteur(14);
  pince = Moteur(15);

  if(!Moteur::init());

	
  QApplication a(argc, argv);
  Widget w;
  w.show();

  return a.exec();
  
  
  //position();

  int quit = 1;
  while(quit){
    printf("Pret pour lacher les moteurs ? Appuie sur Echap\n");
    int chr = 1;
    if (chr == ESC_ASCII_VALUE)
      quit = 0;
  }
  //Moteur::Torque_disable_all();

  
  printf("===== FIN DU PROGRAMME =====\n");

  // Close port
  portHandler->closePort();
  return 0;
  
}

