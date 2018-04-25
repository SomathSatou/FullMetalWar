#include "sandbouton.h"

SandBouton::SandBouton(QWidget *parent) : QWidget(parent)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int height = rec.height();
    int width = rec.width();

    setObjectName("SandBouton");
    setStyleSheet("QWidget#SandBouton { background-color : lightgray }");

    QHBoxLayout* _layout = new QHBoxLayout(this);

    _jouer = new QPushButton("JOUER",this);
    _jouer->setFixedSize(width/8,height/18);
    _jouer->setEnabled(false);

    _retour = new QPushButton("RETOUR",this);
    _retour->setFixedSize(width/8,height/18);

    _layout->addWidget(_jouer);
    _layout->addWidget(_retour);
}

void SandBouton::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SandBouton::enableJouer(bool state) {
    _jouer->setEnabled(state);
}
