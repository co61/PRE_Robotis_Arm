#ifndef WIDGET_H
#define WIDGET_H

//#include "moteur/moteur.hpp"
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();
    void widget_lecture();

    void widget_manette();

    void pince_moove(int pos);
    void bras1_moove(int pos);
    void bras2_moove(int pos);
    void bras3_moove(int pos);
    void base_moove(int pos);

    void enregistrer_chore();
    void lire_chore();


    //void test_moove(int pos, Moteur moteur);
    void disable();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
