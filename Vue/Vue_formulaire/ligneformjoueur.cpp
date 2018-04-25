#include "ligneformjoueur.h"


LigneFormJoueur::LigneFormJoueur(int numeroJoueur,QWidget *parent) : QWidget(parent), _numeroJoueur(numeroJoueur)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int height = rec.height();
    int width = rec.width();

    setFixedHeight(height/25);

    setObjectName("ligneJoueur");
    setStyleSheet("QWidget#ligneJoueur { background-color : lightgray; }");

    _layout = new QHBoxLayout(this);
    _layout->setMargin(0);

    _nomJoueur = new QLineEdit(this);

    _listeCouleur = new QComboBox(this);
    _listeCouleur->addItem("Bleu");
    _listeCouleur->addItem("Rouge");
    _listeCouleur->addItem("Vert");
    _listeCouleur->addItem("Jaune");

    _PA_turn = new QSpinBox(this);
    _PA_turn->setRange(10,40);
    _PA_turn->setFixedWidth(width/18);

    _PA_max = new QSpinBox(this);
    _PA_max->setRange(25,40);
    _PA_max->setFixedWidth(width/18);

    QLabel* _label_nom = new QLabel(this);
    _label_nom->setText("  Nom :");

    QLabel* _label_couleur = new QLabel(this);
    _label_couleur->setText("  Equipe :");

    QLabel* _label_PA = new QLabel(this);
    _label_PA->setText("  PA/tour :");

    QLabel* _label_PAmax = new QLabel(this);
    _label_PAmax->setText("  PA max :");

    _layout->addStretch(2);

    _layout->addWidget(_label_nom);
    _layout->addWidget(_nomJoueur);

    _layout->addWidget(_label_couleur);
    _layout->addWidget(_listeCouleur);

    _layout->addStretch(1);

    _layout->addWidget(_label_PA);
    _layout->addWidget(_PA_turn);

    _layout->addWidget(_label_PAmax);
    _layout->addWidget(_PA_max);

    _layout->addStretch(2);

    connect(_nomJoueur,&QLineEdit::textEdited,this,&LigneFormJoueur::nomChanged);
    connect(_listeCouleur,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&LigneFormJoueur::couleurChanged);
    connect(_PA_turn,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&LigneFormJoueur::PA_turnChanged);
    connect(_PA_max,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&LigneFormJoueur::PA_maxChanged);
}

void LigneFormJoueur::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void LigneFormJoueur::nomChanged(const QString& nom){
    emit sendNom(_numeroJoueur,nom);
}

void LigneFormJoueur::couleurChanged(int indexCouleur){
    emit sendCouleur(_numeroJoueur,indexCouleur);
}

void LigneFormJoueur::PA_turnChanged(int value){
    emit sendPAturn(_numeroJoueur,value);
}

void LigneFormJoueur::PA_maxChanged(int value){
    emit sendPAmax(_numeroJoueur,value);
}


