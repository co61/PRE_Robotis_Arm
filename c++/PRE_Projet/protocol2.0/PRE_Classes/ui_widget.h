/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_counter.h"
#include "qwt_slider.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox;
    QProgressBar *progressBar_lire;
    QPushButton *pushButton_lire;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QProgressBar *progressBar_enregistrer;
    QPushButton *pushButton_enregistrer;
    QTextEdit *textEdit;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLCDNumber *lcdNumber_bras1;
    QLCDNumber *lcdNumber_pince;
    QLabel *label_10;
    QLabel *label_11;
    QLCDNumber *lcdNumber_base;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_12;
    QLCDNumber *lcdNumber_bras3;
    QLabel *label_13;
    QLCDNumber *lcdNumber_bras2;
    QCheckBox *checkBox_lecture;
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;
    QwtCounter *Counter_X;
    QwtCounter *Counter_Y;
    QwtCounter *Counter_Z;
    QPushButton *pushButton_goto;
    QWidget *tab_3;
    QDial *dial_base;
    QDial *dial_bras2;
    QDial *dial_pince;
    QDial *dial_bras1;
    QDial *dial_bras3;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton_disable;
    QLabel *label_7;
    QPushButton *pushButton_3;
    QLabel *label_manette;
    QPushButton *pushButton_6;
    QwtSlider *Slider_base;
    QwtSlider *Slider_bras1;
    QwtSlider *Slider_bras2;
    QwtSlider *Slider_bras3;
    QwtSlider *Slider_pince;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QPushButton *pushButton_enable;
    QLabel *label_19;
    QLabel *label_20;
    QFrame *frame;
    QFrame *frame_2;
    QFrame *frame_3;
    QLabel *label_21;
    QWidget *tab_2;
    QPushButton *pushButton_camera;
    QPushButton *pushButton_routine;
    QwtCounter *Counter_Z_2;
    QwtCounter *Counter_X_2;
    QPushButton *pushButton_detect;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QWidget *tab_6;
    QPushButton *pushButton_leap;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1147, 724);
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1141, 701));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayoutWidget_2 = new QWidget(tab);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(610, 380, 361, 103));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(verticalLayoutWidget_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_2->addWidget(comboBox);

        progressBar_lire = new QProgressBar(verticalLayoutWidget_2);
        progressBar_lire->setObjectName(QString::fromUtf8("progressBar_lire"));
        progressBar_lire->setValue(24);

        verticalLayout_2->addWidget(progressBar_lire);

        pushButton_lire = new QPushButton(verticalLayoutWidget_2);
        pushButton_lire->setObjectName(QString::fromUtf8("pushButton_lire"));

        verticalLayout_2->addWidget(pushButton_lire);

        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(610, 190, 361, 159));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        plainTextEdit = new QPlainTextEdit(verticalLayoutWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);

        progressBar_enregistrer = new QProgressBar(verticalLayoutWidget);
        progressBar_enregistrer->setObjectName(QString::fromUtf8("progressBar_enregistrer"));
        progressBar_enregistrer->setValue(24);

        verticalLayout->addWidget(progressBar_enregistrer);

        pushButton_enregistrer = new QPushButton(verticalLayoutWidget);
        pushButton_enregistrer->setObjectName(QString::fromUtf8("pushButton_enregistrer"));

        verticalLayout->addWidget(pushButton_enregistrer);

        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(210, 340, 233, 201));
        gridLayoutWidget = new QWidget(tab);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(170, 140, 308, 191));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lcdNumber_bras1 = new QLCDNumber(gridLayoutWidget);
        lcdNumber_bras1->setObjectName(QString::fromUtf8("lcdNumber_bras1"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lcdNumber_bras1->setFont(font);
        lcdNumber_bras1->setAutoFillBackground(true);
        lcdNumber_bras1->setSmallDecimalPoint(false);

        gridLayout->addWidget(lcdNumber_bras1, 2, 1, 1, 1);

        lcdNumber_pince = new QLCDNumber(gridLayoutWidget);
        lcdNumber_pince->setObjectName(QString::fromUtf8("lcdNumber_pince"));
        lcdNumber_pince->setFont(font);
        lcdNumber_pince->setAutoFillBackground(true);

        gridLayout->addWidget(lcdNumber_pince, 5, 1, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 2, 0, 1, 1);

        label_11 = new QLabel(gridLayoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 3, 0, 1, 1);

        lcdNumber_base = new QLCDNumber(gridLayoutWidget);
        lcdNumber_base->setObjectName(QString::fromUtf8("lcdNumber_base"));
        lcdNumber_base->setFont(font);
        lcdNumber_base->setAutoFillBackground(true);
        lcdNumber_base->setFrameShape(QFrame::Box);
        lcdNumber_base->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(lcdNumber_base, 1, 1, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 1, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        gridLayout->addWidget(label_8, 0, 0, 1, 2);

        label_12 = new QLabel(gridLayoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 4, 0, 1, 1);

        lcdNumber_bras3 = new QLCDNumber(gridLayoutWidget);
        lcdNumber_bras3->setObjectName(QString::fromUtf8("lcdNumber_bras3"));
        lcdNumber_bras3->setFont(font);
        lcdNumber_bras3->setAutoFillBackground(true);

        gridLayout->addWidget(lcdNumber_bras3, 4, 1, 1, 1);

        label_13 = new QLabel(gridLayoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 5, 0, 1, 1);

        lcdNumber_bras2 = new QLCDNumber(gridLayoutWidget);
        lcdNumber_bras2->setObjectName(QString::fromUtf8("lcdNumber_bras2"));
        lcdNumber_bras2->setFont(font);
        lcdNumber_bras2->setAutoFillBackground(true);

        gridLayout->addWidget(lcdNumber_bras2, 3, 1, 1, 1);

        checkBox_lecture = new QCheckBox(gridLayoutWidget);
        checkBox_lecture->setObjectName(QString::fromUtf8("checkBox_lecture"));

        gridLayout->addWidget(checkBox_lecture, 6, 0, 1, 2);

        graphicsView = new QGraphicsView(tab);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(580, 160, 421, 351));
        graphicsView_2 = new QGraphicsView(tab);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(150, 120, 361, 441));
        Counter_X = new QwtCounter(tab);
        Counter_X->setObjectName(QString::fromUtf8("Counter_X"));
        Counter_X->setGeometry(QRect(70, 40, 241, 31));
        Counter_X->setMinimum(-0.350000000000000);
        Counter_X->setMaximum(0.350000000000000);
        Counter_Y = new QwtCounter(tab);
        Counter_Y->setObjectName(QString::fromUtf8("Counter_Y"));
        Counter_Y->setGeometry(QRect(350, 40, 241, 31));
        Counter_Y->setMinimum(0.000000000000000);
        Counter_Y->setMaximum(0.250000000000000);
        Counter_Z = new QwtCounter(tab);
        Counter_Z->setObjectName(QString::fromUtf8("Counter_Z"));
        Counter_Z->setGeometry(QRect(620, 40, 241, 31));
        Counter_Z->setMinimum(-0.250000000000000);
        Counter_Z->setMaximum(0.250000000000000);
        pushButton_goto = new QPushButton(tab);
        pushButton_goto->setObjectName(QString::fromUtf8("pushButton_goto"));
        pushButton_goto->setGeometry(QRect(940, 40, 97, 33));
        tabWidget->addTab(tab, QString());
        graphicsView_2->raise();
        graphicsView->raise();
        verticalLayoutWidget_2->raise();
        verticalLayoutWidget->raise();
        textEdit->raise();
        gridLayoutWidget->raise();
        Counter_X->raise();
        Counter_Y->raise();
        Counter_Z->raise();
        pushButton_goto->raise();
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        dial_base = new QDial(tab_3);
        dial_base->setObjectName(QString::fromUtf8("dial_base"));
        dial_base->setGeometry(QRect(160, 450, 121, 111));
        dial_base->setMaximum(4095);
        dial_base->setPageStep(9);
        dial_base->setValue(2000);
        dial_bras2 = new QDial(tab_3);
        dial_bras2->setObjectName(QString::fromUtf8("dial_bras2"));
        dial_bras2->setGeometry(QRect(510, 170, 121, 111));
        dial_bras2->setMaximum(4095);
        dial_bras2->setPageStep(9);
        dial_bras2->setValue(2000);
        dial_pince = new QDial(tab_3);
        dial_pince->setObjectName(QString::fromUtf8("dial_pince"));
        dial_pince->setGeometry(QRect(100, 160, 121, 111));
        dial_pince->setMaximum(4095);
        dial_pince->setPageStep(9);
        dial_pince->setValue(1500);
        dial_bras1 = new QDial(tab_3);
        dial_bras1->setObjectName(QString::fromUtf8("dial_bras1"));
        dial_bras1->setGeometry(QRect(510, 390, 121, 111));
        dial_bras1->setAutoFillBackground(false);
        dial_bras1->setMaximum(4095);
        dial_bras1->setPageStep(9);
        dial_bras1->setValue(2000);
        dial_bras3 = new QDial(tab_3);
        dial_bras3->setObjectName(QString::fromUtf8("dial_bras3"));
        dial_bras3->setGeometry(QRect(280, 160, 121, 111));
        dial_bras3->setMaximum(4095);
        dial_bras3->setPageStep(9);
        dial_bras3->setValue(2000);
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(550, 140, 67, 17));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(450, 430, 67, 17));
        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(310, 130, 67, 17));
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(200, 560, 67, 17));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(130, 130, 67, 17));
        pushButton_disable = new QPushButton(tab_3);
        pushButton_disable->setObjectName(QString::fromUtf8("pushButton_disable"));
        pushButton_disable->setGeometry(QRect(810, 400, 221, 61));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 10, 701, 651));
        label_7->setAutoFillBackground(false);
        pushButton_3 = new QPushButton(tab_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(780, 320, 281, 33));
        label_manette = new QLabel(tab_3);
        label_manette->setObjectName(QString::fromUtf8("label_manette"));
        label_manette->setGeometry(QRect(750, 50, 371, 261));
        pushButton_6 = new QPushButton(tab_3);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(780, 360, 281, 33));
        Slider_base = new QwtSlider(tab_3);
        Slider_base->setObjectName(QString::fromUtf8("Slider_base"));
        Slider_base->setGeometry(QRect(740, 520, 71, 121));
        Slider_base->setLowerBound(10.000000000000000);
        Slider_base->setUpperBound(75.000000000000000);
        Slider_base->setValue(30.000000000000000);
        Slider_bras1 = new QwtSlider(tab_3);
        Slider_bras1->setObjectName(QString::fromUtf8("Slider_bras1"));
        Slider_bras1->setGeometry(QRect(810, 520, 71, 121));
        Slider_bras1->setLowerBound(10.000000000000000);
        Slider_bras1->setUpperBound(75.000000000000000);
        Slider_bras1->setValue(30.000000000000000);
        Slider_bras2 = new QwtSlider(tab_3);
        Slider_bras2->setObjectName(QString::fromUtf8("Slider_bras2"));
        Slider_bras2->setGeometry(QRect(890, 520, 71, 121));
        Slider_bras2->setLowerBound(10.000000000000000);
        Slider_bras2->setUpperBound(75.000000000000000);
        Slider_bras2->setValue(30.000000000000000);
        Slider_bras3 = new QwtSlider(tab_3);
        Slider_bras3->setObjectName(QString::fromUtf8("Slider_bras3"));
        Slider_bras3->setGeometry(QRect(970, 520, 71, 121));
        Slider_bras3->setLowerBound(10.000000000000000);
        Slider_bras3->setUpperBound(75.000000000000000);
        Slider_bras3->setValue(30.000000000000000);
        Slider_bras3->setTotalSteps(100u);
        Slider_pince = new QwtSlider(tab_3);
        Slider_pince->setObjectName(QString::fromUtf8("Slider_pince"));
        Slider_pince->setGeometry(QRect(1040, 520, 71, 121));
        Slider_pince->setLowerBound(10.000000000000000);
        Slider_pince->setUpperBound(75.000000000000000);
        Slider_pince->setValue(30.000000000000000);
        label_14 = new QLabel(tab_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(850, 640, 67, 17));
        label_15 = new QLabel(tab_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(930, 640, 67, 17));
        label_16 = new QLabel(tab_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(1010, 640, 67, 17));
        label_17 = new QLabel(tab_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(1080, 640, 67, 17));
        label_18 = new QLabel(tab_3);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(780, 640, 67, 17));
        pushButton_enable = new QPushButton(tab_3);
        pushButton_enable->setObjectName(QString::fromUtf8("pushButton_enable"));
        pushButton_enable->setGeometry(QRect(270, 10, 221, 31));
        label_19 = new QLabel(tab_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(830, 490, 211, 17));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        label_19->setFont(font1);
        label_20 = new QLabel(tab_3);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(250, 60, 211, 17));
        label_20->setFont(font1);
        frame = new QFrame(tab_3);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 50, 721, 611));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(tab_3);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(740, 480, 391, 181));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_3 = new QFrame(tab_3);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(740, 10, 391, 461));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        label_21 = new QLabel(frame_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(70, 20, 281, 20));
        label_21->setFont(font1);
        tabWidget->addTab(tab_3, QString());
        frame->raise();
        frame_2->raise();
        frame_3->raise();
        label_7->raise();
        dial_base->raise();
        dial_bras2->raise();
        dial_pince->raise();
        dial_bras1->raise();
        dial_bras3->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();
        pushButton_disable->raise();
        pushButton_3->raise();
        label_manette->raise();
        pushButton_6->raise();
        Slider_base->raise();
        Slider_bras1->raise();
        Slider_bras2->raise();
        Slider_bras3->raise();
        Slider_pince->raise();
        label_14->raise();
        label_15->raise();
        label_16->raise();
        label_17->raise();
        label_18->raise();
        pushButton_enable->raise();
        label_19->raise();
        label_20->raise();
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        pushButton_camera = new QPushButton(tab_2);
        pushButton_camera->setObjectName(QString::fromUtf8("pushButton_camera"));
        pushButton_camera->setGeometry(QRect(430, 500, 241, 33));
        pushButton_routine = new QPushButton(tab_2);
        pushButton_routine->setObjectName(QString::fromUtf8("pushButton_routine"));
        pushButton_routine->setGeometry(QRect(580, 10, 241, 33));
        Counter_Z_2 = new QwtCounter(tab_2);
        Counter_Z_2->setObjectName(QString::fromUtf8("Counter_Z_2"));
        Counter_Z_2->setGeometry(QRect(320, 10, 241, 31));
        Counter_Z_2->setMinimum(-0.250000000000000);
        Counter_Z_2->setMaximum(0.250000000000000);
        Counter_X_2 = new QwtCounter(tab_2);
        Counter_X_2->setObjectName(QString::fromUtf8("Counter_X_2"));
        Counter_X_2->setGeometry(QRect(50, 10, 241, 31));
        Counter_X_2->setMinimum(-0.250000000000000);
        Counter_X_2->setMaximum(0.250000000000000);
        pushButton_detect = new QPushButton(tab_2);
        pushButton_detect->setObjectName(QString::fromUtf8("pushButton_detect"));
        pushButton_detect->setGeometry(QRect(850, 10, 241, 33));
        label_22 = new QLabel(tab_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(310, 210, 501, 20));
        label_23 = new QLabel(tab_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(310, 240, 501, 20));
        label_24 = new QLabel(tab_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(310, 270, 501, 20));
        label_25 = new QLabel(tab_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(310, 300, 501, 20));
        label_26 = new QLabel(tab_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(310, 330, 501, 20));
        label_27 = new QLabel(tab_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(310, 360, 501, 20));
        tabWidget->addTab(tab_2, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        pushButton_leap = new QPushButton(tab_6);
        pushButton_leap->setObjectName(QString::fromUtf8("pushButton_leap"));
        pushButton_leap->setGeometry(QRect(380, 440, 321, 33));
        label_28 = new QLabel(tab_6);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(310, 200, 501, 20));
        label_29 = new QLabel(tab_6);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(310, 170, 501, 20));
        label_30 = new QLabel(tab_6);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(340, 290, 501, 20));
        label_31 = new QLabel(tab_6);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(310, 230, 501, 20));
        label_32 = new QLabel(tab_6);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(340, 260, 501, 20));
        label_33 = new QLabel(tab_6);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(310, 140, 501, 20));
        tabWidget->addTab(tab_6, QString());

        retranslateUi(Widget);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButton_lire->setText(QApplication::translate("Widget", "Lancer la chor\303\251graphie", nullptr));
        plainTextEdit->setPlainText(QApplication::translate("Widget", "NomDuFichier", nullptr));
        pushButton_enregistrer->setText(QApplication::translate("Widget", "Lancer enregistrement", nullptr));
        label_10->setText(QApplication::translate("Widget", "Bras 1", nullptr));
        label_11->setText(QApplication::translate("Widget", "Bras 2", nullptr));
        label_9->setText(QApplication::translate("Widget", "Base", nullptr));
        label_8->setText(QApplication::translate("Widget", "Lecture des positions des moteurs", nullptr));
        label_12->setText(QApplication::translate("Widget", "Bras 3", nullptr));
        label_13->setText(QApplication::translate("Widget", "Pince", nullptr));
        checkBox_lecture->setText(QApplication::translate("Widget", "Activer lecture des positions", nullptr));
        pushButton_goto->setText(QApplication::translate("Widget", "GoToXYZ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Widget", "Lecture et Enregistrement", nullptr));
        label_2->setText(QApplication::translate("Widget", "Bras 2", nullptr));
        label_3->setText(QApplication::translate("Widget", "Bras 1", nullptr));
        label_4->setText(QApplication::translate("Widget", "Bras 3", nullptr));
        label_5->setText(QApplication::translate("Widget", "Base", nullptr));
        label_6->setText(QApplication::translate("Widget", "Pince", nullptr));
        pushButton_disable->setText(QApplication::translate("Widget", "Disable en position initiale", nullptr));
        label_7->setText(QApplication::translate("Widget", "TextLabel", nullptr));
        pushButton_3->setText(QApplication::translate("Widget", "Connecter manette (Non Lin\303\251aire)", nullptr));
        label_manette->setText(QApplication::translate("Widget", "TextLabel", nullptr));
        pushButton_6->setText(QApplication::translate("Widget", "Connecter manette (Lin\303\251aire)", nullptr));
        label_14->setText(QApplication::translate("Widget", "Bras 1", nullptr));
        label_15->setText(QApplication::translate("Widget", "Bras 2", nullptr));
        label_16->setText(QApplication::translate("Widget", "Bras 3", nullptr));
        label_17->setText(QApplication::translate("Widget", "Pince", nullptr));
        label_18->setText(QApplication::translate("Widget", "Base", nullptr));
        pushButton_enable->setText(QApplication::translate("Widget", "Enable le torque", nullptr));
        label_19->setText(QApplication::translate("Widget", "Vitesse des moteurs", nullptr));
        label_20->setText(QApplication::translate("Widget", "Position des moteurs", nullptr));
        label_21->setText(QApplication::translate("Widget", "Utilisation de la Manette", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Widget", "Controle", nullptr));
        pushButton_camera->setText(QApplication::translate("Widget", "Camera", nullptr));
        pushButton_routine->setText(QApplication::translate("Widget", "Routine", nullptr));
        pushButton_detect->setText(QApplication::translate("Widget", "Detect", nullptr));
        label_22->setText(QApplication::translate("Widget", "Il faut d'abord \"Disable en position initiale le robot", nullptr));
        label_23->setText(QApplication::translate("Widget", "En cliquant sur Camera le robot se positionne selon le bon angle", nullptr));
        label_24->setText(QApplication::translate("Widget", "Les fen\303\252tres li\303\251es \303\240 la cam\303\251ra s'ouvrent", nullptr));
        label_25->setText(QApplication::translate("Widget", "Une fois la balle d\303\251tect\303\251e, il faut cliquer sur echap dans le terminal", nullptr));
        label_26->setText(QApplication::translate("Widget", "Le robot lance donc sa manoeuvre", nullptr));
        label_27->setText(QApplication::translate("Widget", "Il va attrapper la balle et la lache dans le carton devant la camera", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Widget", "Camera", nullptr));
        pushButton_leap->setText(QApplication::translate("Widget", "Leap Motion", nullptr));
        label_28->setText(QApplication::translate("Widget", "Cliquer sur \"Leap Motion\"", nullptr));
        label_29->setText(QApplication::translate("Widget", "Lancer \"sudo leapd\" dans un terminal pour ouvrir le serveur Leap", nullptr));
        label_30->setText(QApplication::translate("Widget", "- Cliquer sur entr\303\251e pour quitter le mode", nullptr));
        label_31->setText(QApplication::translate("Widget", "Dans le Terminal:", nullptr));
        label_32->setText(QApplication::translate("Widget", "- Les touches A et Q ouvrent et ferment la pinces", nullptr));
        label_33->setText(QApplication::translate("Widget", "Le robot peut \303\252tre control\303\251 avec un leap motion (d\303\251tection de la main)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("Widget", "Leap Motion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
