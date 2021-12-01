#include "widget.h"
#include "moteur/moteur.hpp"
#include "clavier/clavier.hpp"
#include "ui_widget.h"
#include <cmath>
#include <QDateTime>
#include <QMessageBox>
#include <QCoreApplication>
#include "manette/controle.cpp"
#include "enregistrement/enregistrer.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

using boost::filesystem::directory_iterator;

extern Moteur base;
extern Moteur bras1;
extern Moteur bras2;
extern Moteur bras3;
extern Moteur pince;



extern QApplication a;

int getch_widget() {
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

int kbhit_widget(void) {
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


void Widget::widget_lecture(){

    usleep(1000000);

    while(ui->checkBox_lecture->isChecked()){
    char test[200];
    sprintf(test, "POSITIONS:\nBase: %d\nBras 1: %d\nBras 2: %d\nBras 3: %d\nPince: %d\n", base.read(), bras1.read(), bras2.read(), bras3.read(),pince.read());

    ui->lcdNumber_base->display(base.read());
    ui->lcdNumber_bras1->display(bras1.read());
    ui->lcdNumber_bras2->display(bras2.read());
    ui->lcdNumber_bras3->display(bras3.read());
    ui->lcdNumber_pince->display(pince.read());

    ui->textEdit->setText(test);
    ui->textEdit->update();

    QApplication::processEvents();

    usleep(250000);

    }


    ui->textEdit->setText("POSITIONS:\nBase: xxx\nBras 1: xxx\nBras 2: xxx\nBras 3: xxx\nPince: xxx\n");
    ui->textEdit->update();

}

void Widget::pince_moove(int pos){

    pince.Torque_enable();
    pince.profileVelocity(30);
    pince.position(pos);

}

void Widget::bras1_moove(int pos){

    bras1.Torque_enable();
    bras1.profileVelocity(30);
    bras1.position(pos);

}


void Widget::bras2_moove(int pos){

  bras2.Torque_enable();
  bras2.profileVelocity(30);
  bras2.position(pos);

}


/*
void Widget::test_moove(int pos, Moteur mot){
  mot.Torque_enable();
  mot.profileVelocity(30);
  mot.position(pos);
}
*/

void Widget::bras3_moove(int pos){

  bras3.Torque_enable();
  bras3.profileVelocity(30);
  bras3.position(pos);

}

void Widget::base_moove(int pos){
  base.Torque_enable();
  base.profileVelocity(30);
  base.position(pos);
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

void Widget::widget_manette(){

  QPixmap pix_on("manette_on.jpg");
  int w = ui->label_manette->width();
  int h = ui->label_manette->height();
  ui->label_manette->setPixmap(pix_on.scaled(w,h,Qt::KeepAspectRatio));


  QApplication::processEvents();
  
  manette();


  QPixmap pix_off("manette_off.jpg");
  ui->label_manette->setPixmap(pix_off.scaled(w,h,Qt::KeepAspectRatio));
}
void Widget::enregistrer_chore(){
    FILE* fichier = NULL;
    char saves[50] = "";
    sprintf(saves, "enregistrement/saves/%s.txt", ui->plainTextEdit->toPlainText().toUtf8().constData());
    ui->comboBox->addItem(saves);
    fichier = fopen(saves, "w");

    Widget::disable();

  int taille = 2500;

  int i = 0;
  
    while(i < taille){
      if((i%50)==0){
        ui->progressBar_2->setValue((int)(i/25));
        QApplication::processEvents();
      }


      char chaine[512] = "";
      sprintf(chaine, "%d\n", base.read());
      sprintf(chaine, "%s%d\n", chaine,bras1.read());
      sprintf(chaine, "%s%d\n", chaine,bras2.read());
      sprintf(chaine, "%s%d\n", chaine,bras3.read());
      sprintf(chaine, "%s%d\n", chaine,pince.read());

      fputs(chaine, fichier);

      sleep(0.1);

      i++;
    }
    
    fclose(fichier);
}



void Widget::lire_chore(){
    FILE* fichier = NULL;
    
    fichier = fopen(ui->comboBox->currentText().toUtf8().constData(), "r");
    printf(ui->comboBox->currentText().toUtf8().constData());
    //Widget::disable();

    int taille = 2500;

    int i = 0;
  
    while(i < taille){
      
      char chaine1[512] = "";
      fgets(chaine1, 512, fichier);
      printf("base %d\n", std::atoi(chaine1));
      base.position(std::atoi(chaine1));
      
      char chaine2[512] = "";
      fgets(chaine2, 512, fichier);
      printf("Bras1 %d\n", std::atoi(chaine2));
      bras1.position(std::atoi(chaine2));
      

      char chaine3[512] = "";
      fgets(chaine3, 512, fichier);
      printf("Bras2 %d\n", std::atoi(chaine3));
      bras2.position(std::atoi(chaine3));


      char chaine4[512] = "";
      fgets(chaine4, 512, fichier);
      printf("Bras3 %d\n", std::atoi(chaine4));
      bras3.position(std::atoi(chaine4));
      

      char chaine5[512] = "";
      fgets(chaine5, 512, fichier);

      printf("Pince %d\n", std::atoi(chaine5));
      pince.position(std::atoi(chaine5));

      printf("Test recup %d\n", std::stoi("10",nullptr,10));

      sleep(0.1);

      i++;
    }
    
    printf(ui->comboBox->currentText().toUtf8().constData());
    fclose(fichier);
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


  
  ui->progressBar_2->setValue(0);
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
  //connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), ui->spinBox, SLOT(setValue(int)));
  connect(ui->checkBox_lecture, SIGNAL(stateChanged(int)), SLOT(widget_lecture()));
  connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(widget_manette()));


  connect(ui->pushButton_4, SIGNAL(clicked()), SLOT(enregistrer_chore()));
  connect(ui->pushButton_5, SIGNAL(clicked()), SLOT(lire_chore()));
}

Widget::~Widget()
{
  delete ui;
}



void Widget::on_buttonBox_accepted()
{

static int state =0;
QString phrase = "au clair de la lune mon ami Pierrot";
QStringList mots = phrase.split(" ");


ui->checkBox_lecture->setChecked(!ui->checkBox_lecture->isChecked());
ui->checkBox_2->setChecked(state==1);
ui->radioButton->setChecked(state==2);
ui->label->setText("hello world!");
ui->progressBar->setValue(state*10);
ui->doubleSpinBox->setValue(M_PI);
ui->calendarWidget->showToday();
ui->timeEdit->setDateTime(QDateTime().currentDateTime());
ui->lcdNumber->setHexMode();
ui->lcdNumber->display(rand()%16);
QRect r = ui->buttonBox->geometry();
r.moveCenter(r.center()+QPoint(0, -1));
ui->buttonBox->setGeometry(r);

ui->tabWidget->setCurrentIndex(state%2);
ui->toolBox->setCurrentIndex(!ui->tabWidget->currentIndex());
ui->lineEdit->setText(QString().setNum(state));
QString br;
br.sprintf("click sur le bouton, position: %d, %d", r.x(), r.y());
ui->textEdit->append(br);
this->setCursor(state==5 ? Qt::WaitCursor : Qt::ArrowCursor);

ui->groupBox->setTitle(mots[state%mots.size()]);
state = (state+1)%10;
}

void Widget::on_buttonBox_rejected()
{
    //int response = QMessageBox::question(this, "Quitter", "Etes vous sur ?", QMessageBox::Yes | QMessageBox::No);
    //if (response== QMessageBox::Yes) close();
}
