#include "formulairebouton.h"

FormulaireBouton::FormulaireBouton(QWidget *parent) : QWidget(parent)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int height = rec.height();
    int width = rec.width();

    setObjectName("FormulaireBouton");
    setStyleSheet("QWidget#FormulaireBouton { background-color : lightgray }");

    QHBoxLayout* _layout = new QHBoxLayout(this);

    _jouer = new QPushButton("JOUER",this);
    _jouer->setFixedSize(width/8,height/18);
    _jouer->setEnabled(false);

    _retour = new QPushButton("RETOUR",this);
    _retour->setFixedSize(width/8,height/18);

    _layout->addWidget(_jouer);
    _layout->addWidget(_retour);
}

void FormulaireBouton::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FormulaireBouton::enableJouer(bool state) {
    _jouer->setEnabled(state);
}
