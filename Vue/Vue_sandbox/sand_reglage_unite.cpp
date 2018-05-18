#include "sand_reglage_unite.h"

void Sand_reglage_unite::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

Sand_reglage_unite::Sand_reglage_unite(QWidget *parent) : QWidget(parent)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int height = rec.height();
    int width = rec.width();

    setObjectName("SandReglageCarte");
    setStyleSheet("QWidget#SandReglageCarte { background-color : lightgray; }");

    QGridLayout* _layout_reglage_map = new QGridLayout(this);
    _layout_reglage_map->setContentsMargins(width/10,height/32,width/10,height/16);

    _char = new QSpinBox(this);
    _char->setRange(0,32);
    _char->setFixedWidth(width/18);

    _grosTas = new QSpinBox(this);
    _grosTas->setRange(0,1);
    _grosTas->setFixedWidth(width/18);

    _crabe = new QSpinBox(this);
    _crabe->setRange(0,4);
    _crabe->setFixedWidth(width/18);

    _pondeuse = new QSpinBox(this);
    _pondeuse->setRange(0,1);
    _pondeuse->setFixedWidth(width/18);

    _base = new QSpinBox(this);
    _base->setRange(0,1);
    _base->setFixedWidth(width/18);

    _barge = new QSpinBox(this);
    _barge->setRange(0,4);
    _barge->setFixedWidth(width/18);

    _vedette = new QSpinBox(this);
    _vedette->setRange(0,10);
    _vedette->setFixedWidth(width/18);


    QLabel* lab_reglage = new QLabel("Parametre des unités",this);
    QFont font("Arial",height/45);
    lab_reglage->setFont(font);
    lab_reglage->setContentsMargins(0,0,0,height/32);

    QLabel* _label_Char = new QLabel(this);
    _label_Char->setText(" Char :");

    QLabel* _label_GrosTas = new QLabel(this);
    _label_GrosTas->setText(" Gros Tas :");

    QLabel* _label_Crabe = new QLabel(this);
    _label_Crabe->setText(" Crabe :");

    QLabel* _label_Pondeuse = new QLabel(this);
    _label_Pondeuse->setText(" Pondeuse :");

    QLabel* _label_base = new QLabel(this);
    _label_base->setText(" Base :");

    QLabel* _label_Barge = new QLabel(this);
    _label_Barge->setText(" Barge :");

    QLabel* _label_Vedette = new QLabel(this);
    _label_Vedette->setText(" Vedette :");

    _layout_reglage_map->addWidget(lab_reglage,0,1,1,3);

    _layout_reglage_map->addWidget(_label_Char,1,0);
    _layout_reglage_map->addWidget(_char,2,0);

    _layout_reglage_map->addWidget(_label_GrosTas,1,1);
    _layout_reglage_map->addWidget(_grosTas,2,1);

    _layout_reglage_map->addWidget(_label_Crabe,1,2);
    _layout_reglage_map->addWidget(_crabe,2,2);

    _layout_reglage_map->addWidget(_label_Pondeuse,1,3);
    _layout_reglage_map->addWidget(_pondeuse,2,3);

    _layout_reglage_map->addWidget(_label_base,3,0);
    _layout_reglage_map->addWidget(_base,4,0);

    _layout_reglage_map->addWidget(_label_Barge,3,1);
    _layout_reglage_map->addWidget(_barge,4,1);

    _layout_reglage_map->addWidget(_label_Vedette,3,2);
    _layout_reglage_map->addWidget(_vedette,4,2);

    connect(_char,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&Sand_reglage_unite::charChanged);
    connect(_grosTas,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&Sand_reglage_unite::grosTasChanged);
    connect(_crabe,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&Sand_reglage_unite::crabeChanged);
    connect(_pondeuse,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&Sand_reglage_unite::pondeuseChanged);
    connect(_base,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&Sand_reglage_unite::baseChanged);
    connect(_barge,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&Sand_reglage_unite::bargeChanged);
    connect(_vedette,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&Sand_reglage_unite::vedetteChanged);


}

QSpinBox *Sand_reglage_unite::getChar() const { return _char; }

QSpinBox *Sand_reglage_unite::getGrosTas() const { return _grosTas; }

QSpinBox *Sand_reglage_unite::getCrabe() const { return _crabe; }

QSpinBox *Sand_reglage_unite::getPondeuse() const { return _pondeuse; }

QSpinBox *Sand_reglage_unite::getBase() const { return _base; }

QSpinBox *Sand_reglage_unite::getBarge() const { return _barge; }

QSpinBox *Sand_reglage_unite::getVedette() const { return _vedette; }

void Sand_reglage_unite::charChanged(int i){
    emit sendChar(i);
}

void Sand_reglage_unite::grosTasChanged(int i){
    emit sendGrosTas(i);
}
void Sand_reglage_unite::crabeChanged(int i){
    emit sendCrabe(i);
}
void Sand_reglage_unite::pondeuseChanged(int i){
    emit sendPondeuse(i);
}
void Sand_reglage_unite::baseChanged(int i){
    emit sendBase(i);
}
void Sand_reglage_unite::bargeChanged(int i){
    emit sendBarge(i);
}
void Sand_reglage_unite::vedetteChanged(int i){
    emit sendVedette(i);
}
