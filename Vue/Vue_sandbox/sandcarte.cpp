#include "sandcarte.h"

SandCarte::SandCarte(QWidget *parent) : QWidget(parent)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int height = rec.height();
    int width = rec.width();

    setObjectName("SandCarte");
    setStyleSheet("QWidget#SandCarte { background-color : lightgrey; }");

    //Layout pour organiser les inputs pour la taille de la carte
    QGridLayout* _layout_taille_map = new QGridLayout(this);
    _layout_taille_map->setContentsMargins(width/10,height/32,width/10,height/16);

    _longueur_carte = new QSpinBox(this);
    _longueur_carte->setRange(5,40);
    _longueur_carte->setFixedWidth(width/18);

    _largeur_carte = new QSpinBox(this);
    _largeur_carte->setRange(5,40);
    _largeur_carte->setFixedWidth(width/18);

    QLabel* lab_taille = new QLabel("Taille de la carte",this);
    QFont font("Arial",height/45);
    lab_taille->setFont(font);
    lab_taille->setContentsMargins(0,0,0,height/32);


    _layout_taille_map->addWidget(lab_taille,0,1);
    _layout_taille_map->addWidget(new QLabel("Longueur",this),1,0);
    _layout_taille_map->addWidget(new QLabel("Largeur",this),1,2);
    _layout_taille_map->addWidget(_longueur_carte,2,0);
    _layout_taille_map->addWidget(_largeur_carte,2,2);

}

QSpinBox *SandCarte::getSpinBoxLongueur() const { return _longueur_carte; }

QSpinBox *SandCarte::getSpinBoxLargeur() const { return _largeur_carte; }

void SandCarte::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
