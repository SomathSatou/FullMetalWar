#include "vue_menuprincipal.h"

Vue_MenuPrincipal::Vue_MenuPrincipal(QWidget *parent) : QWidget(parent)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int height = rec.height();
    int width = rec.width();

    setObjectName("MenuPrincipal");
    setStyleSheet("QWidget#MenuPrincipal { background-image : url(:/Files/Ressources/Images/fond.jpg); }");
    _layout = new QVBoxLayout(this);

    _bouton_jouer = new QPushButton("JOUER",this);
    _bouton_jouer->setFixedSize(QSize(width/9,height/20));

    _bouton_sandbox = new QPushButton("SANDBOX",this);
    _bouton_sandbox->setFixedSize(QSize(width/9,height/20));

    _bouton_quitter = new QPushButton("QUITTER",this);
    _bouton_quitter->setFixedSize(QSize(width/9,height/20));

    _bouton_test_s = new QPushButton("TEST STOCHASTIQUE",this);
    _bouton_test_s->setFixedSize(QSize(width/9,height/20));

    _bouton_test_a = new QPushButton("TEST ALPHA-BETA",this);
    _bouton_test_a->setFixedSize(QSize(width/9,height/20));


    _layout->addStretch(1);
    _layout->addWidget(_bouton_jouer,0,Qt::AlignCenter);
    _layout->addWidget(_bouton_sandbox,0,Qt::AlignCenter);
    _layout->addWidget(_bouton_test_s,0,Qt::AlignCenter);
    _layout->addWidget(_bouton_test_a,0,Qt::AlignCenter);
    _layout->addWidget(_bouton_quitter,0,Qt::AlignCenter);
    _layout->addStretch(1);

    connect(_bouton_quitter,&QPushButton::clicked,&QApplication::quit);
}

void Vue_MenuPrincipal::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
