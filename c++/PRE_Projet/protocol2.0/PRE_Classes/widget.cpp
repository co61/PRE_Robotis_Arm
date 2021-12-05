#include "widget.h"
#include "moteur/moteur.hpp"
#include "clavier/clavier.hpp"
#include "ui_widget.h"
#include <cmath>
#include <QDateTime>
#include <QMessageBox>
#include <QCoreApplication>
#include <QSignalMapper>
#include "manette/controle.cpp"
#include "enregistrement/enregistrer.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include "camera/video.cpp"
#include "slot/camera.cpp"
#include "slot/controle.cpp"
#include "slot/lecture.cpp"

using boost::filesystem::directory_iterator;

extern Moteur base;
extern Moteur bras1;
extern Moteur bras2;
extern Moteur bras3;
extern Moteur pince;



extern QApplication a;




void Widget::goTo(){
  Angles anglesR=calculate_angles(ui->Counter_X->value(),ui->Counter_Y->value(),ui->Counter_Z->value());
  //printf("Angles alpha : %g, beta : %g, gamma : %g, psi : %g\n", anglesR.alpha, anglesR.beta, anglesR.gamma, anglesR.psi);
  Angles anglesD = anglesToDegree(anglesR);
  //printf("Angles alpha : %g, beta : %g, gamma : %g, psi : %g\n", anglesD.alpha, anglesD.beta, anglesD.gamma, anglesD.psi);
  Angles anglesP = anglesToPosition(anglesR);
  //printf("Angles alpha : %g, beta : %g, gamma : %g, psi : %g\n", anglesP.alpha, anglesP.beta, anglesP.gamma, anglesP.psi);

  
  //Torque_enable_all();
  goToPosition(anglesP);

  Position posPince = getPositionPince3D();
  //printf("Position  x : %g, y : %g, z : %g\n", posPince.x, posPince.y, posPince.z);

}


void Widget::leap(){
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
/*
  base.profileVelocity(30);
  bras1.profileVelocity(30);
  bras2.profileVelocity(30);
  bras3.profileVelocity(30);
  pince.profileVelocity(30);
  */

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

  //connect(ui->dial, SIGNAL(sliderMoved(int)), ui->progressBar, SLOT(setValue(int)));
  connect(ui->dial_pince, SIGNAL(sliderMoved(int)), SLOT(pince_moove(int)));
  //connect(ui->dial_pince, SIGNAL(sliderMoved(int)), pince, SLOT(test_moove(Moteur, int)));
  connect(ui->dial_bras1, SIGNAL(sliderMoved(int)), SLOT(bras1_moove(int)));
  connect(ui->dial_bras2, SIGNAL(sliderMoved(int)), SLOT(bras2_moove(int)));
  connect(ui->dial_bras3, SIGNAL(sliderMoved(int)), SLOT(bras3_moove(int)));
  connect(ui->dial_base, SIGNAL(sliderMoved(int)), SLOT(base_moove(int)));
  connect(ui->pushButton_goto, SIGNAL(clicked()), SLOT(goTo()));
  connect(ui->pushButton_leap, SIGNAL(clicked()), SLOT(leap()));

  connect(ui->pushButton_camera, SIGNAL(clicked()), SLOT(widget_camera()));


  connect(ui->Slider_bras2, SIGNAL(valueChanged(double)), SLOT(vitesse()));
  
  ui->progressBar_enregistrer->setValue(0);
  ui->progressBar_lire->setValue(0);
  std::string path = "enregistrement/saves/";
    

  for(const auto & file : boost::filesystem::directory_iterator(path))
    ui->comboBox->addItem(file.path().c_str());

  QPixmap pix_bras("bras.jpg");
  int w = ui->label_7->width();
  int h = ui->label_7->height();
  ui->label_7->setPixmap(pix_bras.scaled(w,h,Qt::KeepAspectRatio));


  QPixmap pix_off("manette_off.jpg");
  w = ui->label_manette->width();
  h = ui->label_manette->height();
  ui->label_manette->setPixmap(pix_off.scaled(w,h,Qt::KeepAspectRatio));
  //connect(ui->pushButton_manette, SIGNAL(clicked()), SLOT(bras1_moove(int)));

  connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(disable()));
  connect(ui->pushButton_7, SIGNAL(clicked()), SLOT(enable()));
  connect(ui->checkBox_lecture, SIGNAL(stateChanged(int)), SLOT(widget_lecture()));
  connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(widget_manette()));
  connect(ui->pushButton_6, SIGNAL(clicked()), SLOT(widget_manetteLineaire()));


  connect(ui->pushButton_4, SIGNAL(clicked()), SLOT(enregistrer_chore()));
  connect(ui->pushButton_5, SIGNAL(clicked()), SLOT(lire_chore()));
}

Widget::~Widget()
{
  delete ui;
}



