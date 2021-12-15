/* Gestion de l'IHM - widget.h
 * Fonctions Slot dans dossier slot:
 *    - Lecture ->  Slot tab 1
 *    - Controle -> Slot tab 2
 *    - Camera ->   Slot tab 3
 *
 * Include:
 *    - moteur.hpp
 *    - clavier.hpp
 *    - controle.cpp
 *    - enregistrer.hcpp
 *    - video.cpp
 *
 * Design de l'interface: widget.ui
 *
 *
 **/

//Bibliothèques
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <QDateTime>
#include <QMessageBox>
#include <QCoreApplication>
#include <QSignalMapper>
#include <boost/filesystem.hpp>

//Include du projet
#include "manette/controle.cpp"
#include "enregistrement/enregistrer.cpp"
#include "widget.h"
#include "moteur/moteur.hpp"
#include "clavier/clavier.hpp"
#include "ui_widget.h"
#include "camera/video.cpp"
#include "slot/camera.cpp"
#include "slot/controle.cpp"
#include "slot/lecture.cpp"
#include "Sample.cpp"

using boost::filesystem::directory_iterator;

extern Moteur base;
extern Moteur bras1;
extern Moteur bras2;
extern Moteur bras3;
extern Moteur pince;

extern QApplication a;

float x_balle;
float y_balle;

void Widget::goTo(){
  Angles anglesR=calculate_angles(ui->Counter_X->value(),ui->Counter_Y->value(),ui->Counter_Z->value());
  Angles anglesD = anglesToDegree(anglesR);
  Angles anglesP = anglesToPosition(anglesR);

  
  //Torque_enable_all();
  goToPosition(anglesP);

  //Position posPince = getPositionPince3D();
  //printf("Position  x : %g, y : %g, z : %g\n", posPince.x, posPince.y, posPince.z);

}

void Widget::goTo_Detect(){


  bras1.position(2000);
  bras2.position(1800);
  bras3.position(2000);


  usleep(3000000);

  pince.position(1000);
  Angles anglesR=calculate_angles(0.1,0.2,0.1);
  Angles anglesD = anglesToDegree(anglesR);
  Angles anglesP = anglesToPosition(anglesR);
  goToPosition(anglesP);


  usleep(4000000);

  anglesR=calculate_angles(0.1,0.04,0.1);
  anglesD = anglesToDegree(anglesR);
  anglesP = anglesToPosition(anglesR);
  goToPosition(anglesP);

  usleep(3000000);

  pince.position(400);

  usleep(3000000);

  anglesR=calculate_angles(0.1,0.04,0.1);
  anglesD = anglesToDegree(anglesR);
  anglesP = anglesToPosition(anglesR);
  goToPosition(anglesP);

}

void Widget::goTo_Cam(){
  pince.position(920);

  Angles anglesR=calculate_angles(ui->Counter_X_2->value(),0.2,ui->Counter_Z_2->value());
  Angles anglesD = anglesToDegree(anglesR);
  Angles anglesP = anglesToPosition(anglesR);
  //Torque_enable_all();
  goToPosition(anglesP);

  usleep(4000000);

  anglesR=calculate_angles(ui->Counter_X_2->value(),0.06,ui->Counter_Z_2->value());
  anglesD = anglesToDegree(anglesR);
  anglesP = anglesToPosition(anglesR);
  //Torque_enable_all();
  goToPosition(anglesP);


  usleep(4000000);

  pince.position(420);




  usleep(2000000);


  anglesR=calculate_angles(ui->Counter_X_2->value(),0.21,ui->Counter_Z_2->value());
  anglesD = anglesToDegree(anglesR);
  anglesP = anglesToPosition(anglesR);
  //Torque_enable_all();
  goToPosition(anglesP);



  usleep(3000000);

  anglesR=calculate_angles(-ui->Counter_X_2->value(),0.23,ui->Counter_Z_2->value());
  anglesD = anglesToDegree(anglesR);
  anglesP = anglesToPosition(anglesR);
  //Torque_enable_all();
  goToPosition(anglesP);

  usleep(3000000);

  pince.position(920);


  usleep(2000000);

  bras1.position(1800);
  bras2.position(2600);
  usleep(3000000);

  anglesR=calculate_angles(0.17,0.23,0.03);
  anglesD = anglesToDegree(anglesR);
  anglesP = anglesToPosition(anglesR);
  //Torque_enable_all();
  goToPosition(anglesP);
  

  usleep(3000000);


  anglesR=calculate_angles(0.17,0.03,0.03);
  anglesD = anglesToDegree(anglesR);
  anglesP = anglesToPosition(anglesR);
  //Torque_enable_all();
  goToPosition(anglesP);
  //Position posPince = getPositionPince3D();
  //printf("Position  x : %g, y : %g, z : %g\n", posPince.x, posPince.y, posPince.z);

}


void Widget::widget_leap(){
  leap();
}




void Widget::vitesse(){
  /*
  printf("vitesse");
  QApplication::processEvents();
  */
  Moteur::profileVelocity((int)ui->Slider_base->value(),
                          (int)ui->Slider_bras1->value(),
                          (int)ui->Slider_bras2->value(),
                          (int)ui->Slider_bras3->value(),
                          (int)ui->Slider_pince->value());

}

void  Widget::disable(){

  base.profileVelocity(30);
  bras1.profileVelocity(30);
  bras2.profileVelocity(30);
  bras3.profileVelocity(30);
  pince.profileVelocity(30);

  usleep(1000000);

  //Position Bras au sol
  bras1.position(2280);
  bras2.position(2040);
  bras3.position(2850);

  usleep(5000000);

  base.Torque_disable();
  bras1.Torque_disable();
  bras2.Torque_disable();
  bras3.Torque_disable();
  pince.Torque_disable();  
}

void  Widget::enable(){

  base.Torque_enable();
  bras1.Torque_enable();
  bras2.Torque_enable();
  bras3.Torque_enable();
  pince.Torque_enable();  
}


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget) 
{
  ui->setupUi(this);


  //Images du tab Controle
  QPixmap pix_bras("bras.jpg");
  int w = ui->label_7->width();
  int h = ui->label_7->height();
  ui->label_7->setPixmap(pix_bras.scaled(w,h,Qt::KeepAspectRatio));

  QPixmap pix_off("manette_off.jpg");
  w = ui->label_manette->width();
  h = ui->label_manette->height();
  ui->label_manette->setPixmap(pix_off.scaled(w,h,Qt::KeepAspectRatio));


  //Tab ENREGISTRER

  connect(ui->pushButton_goto, SIGNAL(clicked()), SLOT(goTo()));
  connect(ui->checkBox_lecture, SIGNAL(stateChanged(int)), SLOT(widget_lecture()));     //Lecture des positions du bras
  connect(ui->pushButton_enregistrer, SIGNAL(clicked()), SLOT(enregistrer_chore()));    //Enregistrer une chorégraphie
  connect(ui->pushButton_lire, SIGNAL(clicked()), SLOT(lire_chore()));                  //Lire une chorégraphie 

  ui->progressBar_enregistrer->setValue(0);
  ui->progressBar_lire->setValue(0);
  std::string path = "enregistrement/saves/";
    
  //Rempli la combobox des fichiers de sauvegarde de choré
  for(const auto & file : boost::filesystem::directory_iterator(path))
    ui->comboBox->addItem(file.path().c_str());

  // Tab CONTROLE
  connect(ui->pushButton_disable, SIGNAL(clicked()), SLOT(disable()));
  connect(ui->pushButton_enable, SIGNAL(clicked()), SLOT(enable()));

  connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(widget_manette()));
  connect(ui->pushButton_6, SIGNAL(clicked()), SLOT(widget_manetteLineaire()));

  connect(ui->dial_pince, SIGNAL(sliderMoved(int)), SLOT(pince_moove(int)));    //Slider Moteur pince
  connect(ui->dial_bras1, SIGNAL(sliderMoved(int)), SLOT(bras1_moove(int)));    //Slider Moteur bras 1
  connect(ui->dial_bras2, SIGNAL(sliderMoved(int)), SLOT(bras2_moove(int)));    //Slider Moteur bras 2
  connect(ui->dial_bras3, SIGNAL(sliderMoved(int)), SLOT(bras3_moove(int)));    //Slider Moteur bras 3
  connect(ui->dial_base, SIGNAL(sliderMoved(int)), SLOT(base_moove(int)));      //Slider Moteur base

  // ATTENTION: ne s'active que sur mouvement de la vitesse du bras2 = "Sécurité"
  connect(ui->Slider_bras2, SIGNAL(valueChanged(double)), SLOT(vitesse()));     //Lis tous les sliders et donne la vitesse aux moteurs

  // Tab CAMERA
  connect(ui->pushButton_routine, SIGNAL(clicked()), SLOT(goTo_Cam()));
  connect(ui->pushButton_detect, SIGNAL(clicked()), SLOT(goTo_Detect()));
  connect(ui->pushButton_camera, SIGNAL(clicked()), SLOT(widget_camera()));

  // Tab LEAP
  connect(ui->pushButton_leap, SIGNAL(clicked()), SLOT(widget_leap()));

  base.profileVelocity(30);
  bras1.profileVelocity(30);
  bras2.profileVelocity(30);
  bras3.profileVelocity(30);
  pince.profileVelocity(30);
}

Widget::~Widget()
{
  delete ui;
}



