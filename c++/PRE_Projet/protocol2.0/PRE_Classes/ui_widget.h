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
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDial>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QKeySequenceEdit>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox;
    QPushButton *pushButton_5;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QProgressBar *progressBar_2;
    QPushButton *pushButton_4;
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
    QPushButton *pushButton_2;
    QLabel *label_7;
    QPushButton *pushButton_3;
    QLabel *label_manette;
    QWidget *tab_6;
    QTextEdit *textEdit_2;
    QWidget *tab_4;
    QTimeEdit *timeEdit;
    QLineEdit *lineEdit;
    QKeySequenceEdit *keySequenceEdit;
    QLCDNumber *lcdNumber;
    QRadioButton *radioButton;
    QGroupBox *groupBox;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QSpinBox *spinBox;
    QRadioButton *radioButton_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QProgressBar *progressBar;
    QSlider *horizontalSlider;
    QDoubleSpinBox *doubleSpinBox;
    QToolBox *toolBox;
    QWidget *page;
    QWidget *page_2;
    QCommandLinkButton *commandLinkButton;
    QToolButton *toolButton;
    QPushButton *pushButton;
    QDialogButtonBox *buttonBox;
    QTextBrowser *textBrowser;
    QCalendarWidget *calendarWidget;
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1147, 724);
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(-10, 0, 1141, 701));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayoutWidget_2 = new QWidget(tab);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(610, 390, 361, 80));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(verticalLayoutWidget_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_2->addWidget(comboBox);

        pushButton_5 = new QPushButton(verticalLayoutWidget_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        verticalLayout_2->addWidget(pushButton_5);

        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(610, 200, 361, 159));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        plainTextEdit = new QPlainTextEdit(verticalLayoutWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);

        progressBar_2 = new QProgressBar(verticalLayoutWidget);
        progressBar_2->setObjectName(QString::fromUtf8("progressBar_2"));
        progressBar_2->setValue(24);

        verticalLayout->addWidget(progressBar_2);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(210, 380, 233, 141));
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
        lcdNumber_bras1->setAutoFillBackground(true);
        lcdNumber_bras1->setSmallDecimalPoint(false);

        gridLayout->addWidget(lcdNumber_bras1, 2, 1, 1, 1);

        lcdNumber_pince = new QLCDNumber(gridLayoutWidget);
        lcdNumber_pince->setObjectName(QString::fromUtf8("lcdNumber_pince"));
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
        lcdNumber_base->setAutoFillBackground(true);
        lcdNumber_base->setFrameShape(QFrame::Box);
        lcdNumber_base->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(lcdNumber_base, 1, 1, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 1, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 0, 1, 2);

        label_12 = new QLabel(gridLayoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 4, 0, 1, 1);

        lcdNumber_bras3 = new QLCDNumber(gridLayoutWidget);
        lcdNumber_bras3->setObjectName(QString::fromUtf8("lcdNumber_bras3"));
        lcdNumber_bras3->setAutoFillBackground(true);

        gridLayout->addWidget(lcdNumber_bras3, 4, 1, 1, 1);

        label_13 = new QLabel(gridLayoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 5, 0, 1, 1);

        lcdNumber_bras2 = new QLCDNumber(gridLayoutWidget);
        lcdNumber_bras2->setObjectName(QString::fromUtf8("lcdNumber_bras2"));
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
        tabWidget->addTab(tab, QString());
        graphicsView_2->raise();
        graphicsView->raise();
        verticalLayoutWidget_2->raise();
        verticalLayoutWidget->raise();
        textEdit->raise();
        gridLayoutWidget->raise();
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        dial_base = new QDial(tab_3);
        dial_base->setObjectName(QString::fromUtf8("dial_base"));
        dial_base->setGeometry(QRect(210, 450, 121, 111));
        dial_base->setMaximum(4095);
        dial_base->setPageStep(9);
        dial_base->setValue(2000);
        dial_bras2 = new QDial(tab_3);
        dial_bras2->setObjectName(QString::fromUtf8("dial_bras2"));
        dial_bras2->setGeometry(QRect(560, 170, 121, 111));
        dial_bras2->setMaximum(4095);
        dial_bras2->setPageStep(9);
        dial_bras2->setValue(2000);
        dial_pince = new QDial(tab_3);
        dial_pince->setObjectName(QString::fromUtf8("dial_pince"));
        dial_pince->setGeometry(QRect(150, 160, 121, 111));
        dial_pince->setMaximum(4095);
        dial_pince->setPageStep(9);
        dial_pince->setValue(1500);
        dial_bras1 = new QDial(tab_3);
        dial_bras1->setObjectName(QString::fromUtf8("dial_bras1"));
        dial_bras1->setGeometry(QRect(560, 390, 121, 111));
        dial_bras1->setAutoFillBackground(false);
        dial_bras1->setMaximum(4095);
        dial_bras1->setPageStep(9);
        dial_bras1->setValue(2000);
        dial_bras3 = new QDial(tab_3);
        dial_bras3->setObjectName(QString::fromUtf8("dial_bras3"));
        dial_bras3->setGeometry(QRect(330, 160, 121, 111));
        dial_bras3->setMaximum(4095);
        dial_bras3->setPageStep(9);
        dial_bras3->setValue(2000);
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(600, 140, 67, 17));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(500, 430, 67, 17));
        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(360, 130, 67, 17));
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(250, 560, 67, 17));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(180, 130, 67, 17));
        pushButton_2 = new QPushButton(tab_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(820, 490, 221, 61));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 10, 711, 651));
        pushButton_3 = new QPushButton(tab_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(810, 330, 231, 33));
        label_manette = new QLabel(tab_3);
        label_manette->setObjectName(QString::fromUtf8("label_manette"));
        label_manette->setGeometry(QRect(740, 50, 381, 261));
        tabWidget->addTab(tab_3, QString());
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
        pushButton_2->raise();
        pushButton_3->raise();
        label_manette->raise();
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        textEdit_2 = new QTextEdit(tab_6);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(63, 16, 671, 621));
        tabWidget->addTab(tab_6, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        timeEdit = new QTimeEdit(tab_4);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(480, 190, 118, 27));
        timeEdit->setCalendarPopup(true);
        lineEdit = new QLineEdit(tab_4);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(200, 0, 113, 27));
        keySequenceEdit = new QKeySequenceEdit(tab_4);
        keySequenceEdit->setObjectName(QString::fromUtf8("keySequenceEdit"));
        keySequenceEdit->setGeometry(QRect(310, 200, 113, 27));
        lcdNumber = new QLCDNumber(tab_4);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(300, 130, 64, 23));
        radioButton = new QRadioButton(tab_4);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(-160, 10, 100, 22));
        groupBox = new QGroupBox(tab_4);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(440, 10, 120, 81));
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(10, 20, 100, 22));
        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setGeometry(QRect(10, 40, 100, 22));
        radioButton_5 = new QRadioButton(groupBox);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setGeometry(QRect(10, 60, 100, 22));
        spinBox = new QSpinBox(tab_4);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(80, 140, 45, 27));
        radioButton_2 = new QRadioButton(tab_4);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(-160, 40, 100, 22));
        checkBox_3 = new QCheckBox(tab_4);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(0, 70, 86, 22));
        checkBox_2 = new QCheckBox(tab_4);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(0, 40, 86, 22));
        progressBar = new QProgressBar(tab_4);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(-140, 180, 161, 23));
        progressBar->setValue(24);
        horizontalSlider = new QSlider(tab_4);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(-140, 140, 160, 21));
        horizontalSlider->setOrientation(Qt::Horizontal);
        doubleSpinBox = new QDoubleSpinBox(tab_4);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(80, 180, 62, 27));
        toolBox = new QToolBox(tab_4);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        toolBox->setGeometry(QRect(140, 230, 161, 141));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 100, 30));
        toolBox->addItem(page, QString::fromUtf8("Page 1"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 161, 79));
        toolBox->addItem(page_2, QString::fromUtf8("Page 2"));
        commandLinkButton = new QCommandLinkButton(tab_4);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(250, 430, 168, 41));
        toolButton = new QToolButton(tab_4);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(160, 420, 22, 25));
        pushButton = new QPushButton(tab_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 430, 85, 27));
        buttonBox = new QDialogButtonBox(tab_4);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(310, 310, 176, 27));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        textBrowser = new QTextBrowser(tab_4);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(500, 360, 256, 192));
        calendarWidget = new QCalendarWidget(tab_4);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(650, 0, 272, 200));
        label = new QLabel(tab_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(640, 220, 131, 17));
        tabWidget->addTab(tab_4, QString());

        retranslateUi(Widget);

        tabWidget->setCurrentIndex(1);
        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButton_5->setText(QApplication::translate("Widget", "Lancer la chor\303\251graphie", nullptr));
        plainTextEdit->setPlainText(QApplication::translate("Widget", "NomDuFichier", nullptr));
        pushButton_4->setText(QApplication::translate("Widget", "Lancer enregistrement", nullptr));
        label_10->setText(QApplication::translate("Widget", "Bras 1", nullptr));
        label_11->setText(QApplication::translate("Widget", "Bras 2", nullptr));
        label_9->setText(QApplication::translate("Widget", "Base", nullptr));
        label_8->setText(QApplication::translate("Widget", "Lecture des positions des moteurs", nullptr));
        label_12->setText(QApplication::translate("Widget", "Bras 3", nullptr));
        label_13->setText(QApplication::translate("Widget", "Pince", nullptr));
        checkBox_lecture->setText(QApplication::translate("Widget", "Activer lecture des positions", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Widget", "Lecture et Enregistrement", nullptr));
        label_2->setText(QApplication::translate("Widget", "Bras 2", nullptr));
        label_3->setText(QApplication::translate("Widget", "Bras 1", nullptr));
        label_4->setText(QApplication::translate("Widget", "Bras 3", nullptr));
        label_5->setText(QApplication::translate("Widget", "Base", nullptr));
        label_6->setText(QApplication::translate("Widget", "Pince", nullptr));
        pushButton_2->setText(QApplication::translate("Widget", "Disable en position initiale", nullptr));
        label_7->setText(QApplication::translate("Widget", "TextLabel", nullptr));
        pushButton_3->setText(QApplication::translate("Widget", "Connecter manette", nullptr));
        label_manette->setText(QApplication::translate("Widget", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Widget", "Controle", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("Widget", "Logs", nullptr));
        radioButton->setText(QApplication::translate("Widget", "RadioButton", nullptr));
        groupBox->setTitle(QApplication::translate("Widget", "GroupBox", nullptr));
        radioButton_3->setText(QApplication::translate("Widget", "RadioButton", nullptr));
        radioButton_4->setText(QApplication::translate("Widget", "RadioButton", nullptr));
        radioButton_5->setText(QApplication::translate("Widget", "RadioButton", nullptr));
        radioButton_2->setText(QApplication::translate("Widget", "RadioButton", nullptr));
        checkBox_3->setText(QApplication::translate("Widget", "CheckBox", nullptr));
        checkBox_2->setText(QApplication::translate("Widget", "CheckBox", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("Widget", "Page 1", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("Widget", "Page 2", nullptr));
        commandLinkButton->setText(QApplication::translate("Widget", "CommandLinkButton", nullptr));
        toolButton->setText(QApplication::translate("Widget", "...", nullptr));
        pushButton->setText(QApplication::translate("Widget", "PushButton", nullptr));
        label->setText(QApplication::translate("Widget", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("Widget", "Autre", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
