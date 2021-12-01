#include "widget.h"
#include "moteur/moteur.h"
#include "ui_widget.h"
#include <cmath>
#include <QDateTime>
#include <QMessageBox>

void widget_lecture(){
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

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->dial, SIGNAL(sliderMoved(int)), ui->progressBar, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), ui->spinBox, SLOT(setValue(int)));
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

ui->checkBox->setChecked(!ui->checkBox->isChecked());
ui->checkBox_2->setChecked(state==1);
ui->radioButton->setChecked(state==2);
ui->label->setText("hello world!");
ui->dial->setValue(rand()%ui->dial->maximum());
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
    widget_lecture();
    //int response = QMessageBox::question(this, "Quitter", "Etes vous sur ?", QMessageBox::Yes | QMessageBox::No);
    //if (response== QMessageBox::Yes) close();
}
