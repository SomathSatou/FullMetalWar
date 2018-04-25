#ifndef VUE_MENUPRINCIPAL_H
#define VUE_MENUPRINCIPAL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QStyleOption>
#include <QPainter>
#include <QRect>
#include <QDesktopWidget>

class Vue_MenuPrincipal : public QWidget
{
    Q_OBJECT
public:
    explicit Vue_MenuPrincipal(QWidget *parent = 0);


    QPushButton* getBoutonJouer() const { return _bouton_jouer; }
    QPushButton* getBoutonSand() const { return _bouton_sandbox; }
    QPushButton* getBoutonTestA() const { return _bouton_test_a; }
    QPushButton* getBoutonTestS() const { return _bouton_test_s; }

protected:
    void paintEvent(QPaintEvent *e);

private:

    QVBoxLayout* _layout;

    QPushButton* _bouton_jouer;
    QPushButton* _bouton_quitter;
    QPushButton* _bouton_sandbox;
    QPushButton* _bouton_test_a;
    QPushButton* _bouton_test_s;



};

#endif // VUE_MENUPRINCIPAL_H
