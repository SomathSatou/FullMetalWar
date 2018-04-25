#include "infobarre.h"
#include <QApplication>

InfoBarre::InfoBarre(QWidget *parent) : QWidget(parent)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int height = rec.height();
    int width = rec.width();

    setFixedHeight(height/18);

    _layout = new QHBoxLayout(this);
    _layout->setMargin(0);
    _layout->setSpacing(0);
    //_layout->setContentsMargins(width/8,0,0,0);

    _label_tour = new QLabel(this);

    _option = new QPushButton("X",this);
    _option->setStyleSheet("background-color : red");
    _option->setFixedSize(width/32,height/18);

    _layout->addStretch(1);
    _layout->addWidget(_label_tour);
    _layout->addStretch(1);
    _layout->addWidget(_option);

    connect(_option,&QPushButton::clicked,&QApplication::quit);

}

void InfoBarre::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void InfoBarre::updateInfoBarre(int tour, std::string joueur) {


    std::ostringstream oss;
    oss << "Tour : " << tour << " | Joueur : "<<joueur;
    QString nb_tour = oss.str().c_str();

    _label_tour->setText(nb_tour);

}
