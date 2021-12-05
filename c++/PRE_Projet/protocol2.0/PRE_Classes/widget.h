#ifndef WIDGET_H
#define WIDGET_H

//#include "moteur/moteur.hpp"
#include <QWidget>
#include "moteur/moteur.hpp"

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

    //Lecture position
    void widget_lecture();

    //Utilisation Manette
    void widget_manette();
    void widget_manetteLineaire();

    //Mouvement du bras (jauges)
    void pince_moove(int pos);
    void bras1_moove(int pos);
    void bras2_moove(int pos);
    void bras3_moove(int pos);
    void base_moove(int pos);
    void test_moove(int pos, Moteur mot);

    void vitesse();
    void enregistrer_chore();
    void lire_chore();
    void goTo();
    void leap();
    void widget_camera();


    //void test_moove(int pos, Moteur moteur);
    void disable();
    void enable();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
