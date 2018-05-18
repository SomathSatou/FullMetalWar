#include "vue_sandbox.h"

Vue_Sandbox::Vue_Sandbox(QWidget *parent) :
    QWidget(parent),
    _nombreJoueur(2)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int width = rec.width();

    UNUSED(width);

    setObjectName("Formulaire");
    setStyleSheet("QWidget#Formulaire { background-image : url(:/Files/Ressources/Images/fond_form.jpg); }");

    _controleur = new Controleur_Sandbox(this);

    //Layout principal qui contiendra l'ensemble du formulaire
    _layout_principal = new QVBoxLayout();

    //Layout pour afficher les formulaires pour la selection des joueurs
    _grid_layout = new QGridLayout();
    _grid_layout->setSpacing(0);
    _grid_layout->setMargin(0);
    //_grid_layout->setContentsMargins(width/8,0,width/8,0);

    //Bouton pour ajouter une ligne de joueur
//    _ajouter_joueur = new QPushButton("+ AJOUTER JOUEUR",this);
//    _supprimer_joueur = new QPushButton("- SUPPRIMER JOUEUR",this);
//    _supprimer_joueur->setEnabled(false);

    LigneSandJoueur* j1 = new LigneSandJoueur(0,this); // Ligne du joueur 1
    LigneSandJoueur* j2 = new LigneSandJoueur(1,this); // Ligne du joueur 2

    _grid_layout->addWidget(j1,0,0,1,0);
    _grid_layout->addWidget(j2,1,0,1,0);
//    _grid_layout->addWidget(_ajouter_joueur,_nombreJoueur,0);
//    _grid_layout->addWidget(_supprimer_joueur,_nombreJoueur,1);

    _layout_principal->addStretch(1);
    _layout_principal->addLayout(_grid_layout);

    //Layout de la partie inférieure du formulaire
    _layout_bas = new QHBoxLayout();
    //_layout_bas->setContentsMargins(width/8,0,width/8,0);

    _formCarte = new SandCarte(this);
    _layout_bas->addWidget(_formCarte);

    _formBouton = new SandBouton(this);
    _layout_bas->addWidget(_formBouton);

    _layout_principal->addLayout(_layout_bas);
   // _layout_principal->addStretch(1);

    _layout_carte  = new QHBoxLayout();

    _sandCarte = new Sand_reglage_carte(this);
    _layout_carte->addWidget(_sandCarte);

    _layout_principal->addLayout(_layout_carte);

    _layout_unite = new QHBoxLayout();

    _sandUnite = new Sand_reglage_unite(this);
    _layout_unite->addWidget(_sandUnite);

    _layout_principal->addLayout(_layout_unite);
    _layout_principal->addStretch(1);


    QHBoxLayout* layout_test = new QHBoxLayout(this);

    layout_test->addStretch(1);
    layout_test->addLayout(_layout_principal);
    layout_test->addStretch(1);

    // Connection des bouton pour ajouter/enlever une ligne de formulaire pour joueur à leur slot respectif
//    connect(_ajouter_joueur,&QPushButton::clicked,this,&Vue_Sandbox::addLigneJoueur);
//    connect(_supprimer_joueur,&QPushButton::clicked,this,&Vue_Sandbox::supprLigneJoueur);

    //Connection des QSpinBox au controleur
    connect(_formCarte->getSpinBoxLongueur(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),_controleur,&Controleur_Sandbox::setLongueur);
    connect(_formCarte->getSpinBoxLargeur(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),_controleur,&Controleur_Sandbox::setLargeur);

    //Connection des LigneFormJoueurs au Controleur_Sandbox pour récupérer les informations, il y a en a 2 par défaut
    connect(j1,&LigneSandJoueur::sendNom,_controleur,&Controleur_Sandbox::setNom);
    connect(j1,&LigneSandJoueur::sendCouleur,_controleur,&Controleur_Sandbox::setCouleur);
    connect(j1,&LigneSandJoueur::sendPAturn,_controleur,&Controleur_Sandbox::setPAturn);
    connect(j1,&LigneSandJoueur::sendPAmax,_controleur,&Controleur_Sandbox::setPAmax);

    connect(j2,&LigneSandJoueur::sendNom,_controleur,&Controleur_Sandbox::setNom);
    connect(j2,&LigneSandJoueur::sendCouleur,_controleur,&Controleur_Sandbox::setCouleur);
    connect(j2,&LigneSandJoueur::sendPAturn,_controleur,&Controleur_Sandbox::setPAturn);
    connect(j2,&LigneSandJoueur::sendPAmax,_controleur,&Controleur_Sandbox::setPAmax);

    // Connection des valeur des reglages de la catre
    connect(_sandCarte,&Sand_reglage_carte::sendType,_controleur,&Controleur_Sandbox::setType);
    connect(_sandCarte,&Sand_reglage_carte::sendMinerais,_controleur,&Controleur_Sandbox::setMinerais);

    // Connnection des réglages des unité
    connect(_sandUnite->getChar(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),_controleur,&Controleur_Sandbox::setChar);
    connect(_sandUnite->getGrosTas(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),_controleur,&Controleur_Sandbox::setGrosTas);
    connect(_sandUnite->getCrabe(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),_controleur,&Controleur_Sandbox::setCrabe);
    connect(_sandUnite->getPondeuse(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),_controleur,&Controleur_Sandbox::setPondeuse);
    connect(_sandUnite->getBase(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),_controleur,&Controleur_Sandbox::setBase);
    connect(_sandUnite->getBarge(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),_controleur,&Controleur_Sandbox::setBarge);
    connect(_sandUnite->getVedette(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),_controleur,&Controleur_Sandbox::setVedette);

    // Connection du bouton "JOUER" du formulaire au signal qui sera émis en fonction de la cohérence des infos
    connect(_controleur,&Controleur_Sandbox::sendEnableJouer,_formBouton,&SandBouton::enableJouer);
}

Vue_Sandbox::~Vue_Sandbox(){
    delete _controleur;
}

QPushButton *Vue_Sandbox::getBoutonRetour() const { return _formBouton->getBoutonRetour(); }

QPushButton *Vue_Sandbox::getBoutonJouer() const { return _formBouton->getBoutonJouer(); }

Controleur_Sandbox *Vue_Sandbox::getControleur() const { return _controleur; }

void Vue_Sandbox::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//void Vue_Sandbox::addLigneJoueur(){

//        LigneSandJoueur* j = new LigneSandJoueur(_nombreJoueur,this);

//        _grid_layout->addWidget(j,_nombreJoueur,0,1,0);
//        _grid_layout->addWidget(_ajouter_joueur,_nombreJoueur+1,0);
//        _grid_layout->addWidget(_supprimer_joueur,_nombreJoueur+1,1);

//        _controleur->addJoueur();

//        connect(j,&LigneSandJoueur::sendNom,_controleur,&Controleur_Sandbox::setNom);
//        connect(j,&LigneSandJoueur::sendCouleur,_controleur,&Controleur_Sandbox::setCouleur);
//        connect(j,&LigneSandJoueur::sendPAturn,_controleur,&Controleur_Sandbox::setPAturn);
//        connect(j,&LigneSandJoueur::sendPAmax,_controleur,&Controleur_Sandbox::setPAmax);
//        _nombreJoueur++;

//        if(!_supprimer_joueur->isEnabled())
//            _supprimer_joueur->setEnabled(true);

//        if(_nombreJoueur == 4)
//            _ajouter_joueur->setEnabled(false);

//}

//void Vue_Sandbox::supprLigneJoueur(){

//        QLayoutItem* child;

//        child = _grid_layout->takeAt(_nombreJoueur-1);
//        child->widget()->deleteLater();
//        delete child;

//        _controleur->supprJoueur();

//        _grid_layout->addWidget(_ajouter_joueur,_nombreJoueur-1,0);
//        _grid_layout->addWidget(_supprimer_joueur,_nombreJoueur-1,1);

//        _nombreJoueur--;

//        if(!_ajouter_joueur->isEnabled())
//            _ajouter_joueur->setEnabled(true);

//        if(_nombreJoueur == 2)
//            _supprimer_joueur->setEnabled(false);

//}
