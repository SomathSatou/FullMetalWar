#include "sand_reglage_carte.h"
#include <iostream>

Sand_reglage_carte::Sand_reglage_carte(QWidget *parent) : QWidget(parent)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int height = rec.height();
    int width = rec.width();

    setObjectName("SandReglageCarte");
    setStyleSheet("QWidget#SandReglageCarte { background-color : lightgray; }");

    QGridLayout* _layout_reglage_map = new QGridLayout(this);
    _layout_reglage_map->setContentsMargins(width/10,height/32,width/10,height/16);

    QLabel* lab_reglage = new QLabel("Parametre de la map",this);
    QFont font("Arial",height/45);
    lab_reglage->setFont(font);
    lab_reglage->setContentsMargins(0,0,0,height/32);

    _layout_reglage_map->addWidget(lab_reglage,0,1,1,3);

    _typeCarte = new QComboBox(this);
    QStringList typeList;
    typeList <<"aleatoire" << "Plaines" << "Mer" << "Stochastique";
    _typeCarte->addItems(typeList);

    _layout_reglage_map->addWidget(_typeCarte,1,0,1,2);

    _minerais = new QCheckBox("Minerais",this);

    _layout_reglage_map->addWidget(_minerais,1,2,1,1);

    connect(_typeCarte,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&Sand_reglage_carte::typeChanged);
    connect(_minerais,static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged),this,&Sand_reglage_carte::mineraisChanged);
}

void Sand_reglage_carte::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Sand_reglage_carte::typeChanged(int value){
    emit sendType(value);

}

void Sand_reglage_carte::mineraisChanged(int value){
    emit sendMinerais(value);

}
