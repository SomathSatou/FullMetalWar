#include "vue_formulaire.h"

Vue_Formulaire::Vue_Formulaire(QWidget *parent) :
    QWidget(parent),
    _nombreJoueur(2)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int width = rec.width();

    UNUSED(width);

    setObjectName("Formulaire");
    setStyleSheet("QWidget#Formulaire { background-image : url(:/Files/Ressources/Images/fond_form.jpg); }");

    _controleur = new Controleur_Formulaire(this);

    //Layout principal qui contiendra l'ensemble du formulaire
    _layout_principal = new QVBoxLayout();

    //Layout pour afficher les formulaires pour la selection des joueurs
    _grid_layout = new QGridLayout();
    _grid_layout->setSpacing(0);
    _grid_layout->setMargin(0);
    //_grid_layout->setContentsMargins(width/8,0,width/8,0);

    //Bouton pour ajouter une ligne de joueur
    _ajouter_joueur = new QPushButton("+ AJOUTER JOUEUR",this);
    _supprimer_joueur = new QPushButton("- SUPPRIMER JOUEUR",this);
    _supprimer_joueur->setEnabled(false);

    LigneFormJoueur* j1 = new LigneFormJoueur(0,this); // Ligne du joueur 1
    LigneFormJoueur* j2 = new LigneFormJoueur(1,this); // Ligne du joueur 2

    _grid_layout->addWidget(j1,0,0,1,0);
    _grid_layout->addWidget(j2,1,0,1,0);
    _grid_layout->addWidget(_ajouter_joueur,_nombreJoueur,0);
    _grid_layout->addWidget(_supprimer_joueur,_nombreJoueur,1);

    _layout_principal->addStretch(1);
    _layout_principal->addLayout(_grid_layout);

    //Layout de la partie inférieure du formulaire
    _layout_bas = new QHBoxLayout();
    //_layout_bas->setContentsMargins(width/8,0,width/8,0);

    _formCarte = new FormulaireCarte(this);
    _layout_bas->addWidget(_formCarte);

    _formBouton = new FormulaireBouton(this);
    _layout_bas->addWidget(_formBouton);

    _layout_principal->addLayout(_layout_bas);
    _layout_principal->addStretch(1);

    QHBoxLayout* layout_test = new QHBoxLayout(this);

    layout_test->addStretch(1);
    layout_test->addLayout(_layout_principal);
    layout_test->addStretch(1);

    // Connection des bouton pour ajouter/enlever une ligne de formulaire pour joueur à leur slot respectif
    connect(_ajouter_joueur,&QPushButton::clicked,this,&Vue_Formulaire::addLigneJoueur);
    connect(_supprimer_joueur,&QPushButton::clicked,this,&Vue_Formulaire::supprLigneJoueur);

    //Connection des QSpinBox au controleur
    connect(_formCarte->getSpinBoxLongueur(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),_controleur,&Controleur_Formulaire::setLongueur);
    connect(_formCarte->getSpinBoxLargeur(),static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),_controleur,&Controleur_Formulaire::setLargeur);

    //Connection des LigneFormJoueurs au Controleur_Formulaire pour récupérer les informations, il y a en a 2 par défaut
    connect(j1,&LigneFormJoueur::sendNom,_controleur,&Controleur_Formulaire::setNom);
    connect(j1,&LigneFormJoueur::sendCouleur,_controleur,&Controleur_Formulaire::setCouleur);
    connect(j1,&LigneFormJoueur::sendPAturn,_controleur,&Controleur_Formulaire::setPAturn);
    connect(j1,&LigneFormJoueur::sendPAmax,_controleur,&Controleur_Formulaire::setPAmax);

    connect(j2,&LigneFormJoueur::sendNom,_controleur,&Controleur_Formulaire::setNom);
    connect(j2,&LigneFormJoueur::sendCouleur,_controleur,&Controleur_Formulaire::setCouleur);
    connect(j2,&LigneFormJoueur::sendPAturn,_controleur,&Controleur_Formulaire::setPAturn);
    connect(j2,&LigneFormJoueur::sendPAmax,_controleur,&Controleur_Formulaire::setPAmax);

    // Connection du bouton "JOUER" du formulaire au signal qui sera émis en fonction de la cohérence des infos
    connect(_controleur,&Controleur_Formulaire::sendEnableJouer,_formBouton,&FormulaireBouton::enableJouer);

}

Vue_Formulaire::~Vue_Formulaire(){
    delete _controleur;
}

QPushButton *Vue_Formulaire::getBoutonRetour() const { return _formBouton->getBoutonRetour(); }

QPushButton *Vue_Formulaire::getBoutonJouer() const { return _formBouton->getBoutonJouer(); }

Controleur_Formulaire *Vue_Formulaire::getControleur() const { return _controleur; }

void Vue_Formulaire::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Vue_Formulaire::addLigneJoueur(){

        LigneFormJoueur* j = new LigneFormJoueur(_nombreJoueur,this);

        _grid_layout->addWidget(j,_nombreJoueur,0,1,0);
        _grid_layout->addWidget(_ajouter_joueur,_nombreJoueur+1,0);
        _grid_layout->addWidget(_supprimer_joueur,_nombreJoueur+1,1);

        _controleur->addJoueur();

        connect(j,&LigneFormJoueur::sendNom,_controleur,&Controleur_Formulaire::setNom);
        connect(j,&LigneFormJoueur::sendCouleur,_controleur,&Controleur_Formulaire::setCouleur);
        connect(j,&LigneFormJoueur::sendPAturn,_controleur,&Controleur_Formulaire::setPAturn);
        connect(j,&LigneFormJoueur::sendPAmax,_controleur,&Controleur_Formulaire::setPAmax);
        _nombreJoueur++;

        if(!_supprimer_joueur->isEnabled())
            _supprimer_joueur->setEnabled(true);

        if(_nombreJoueur == 4)
            _ajouter_joueur->setEnabled(false);

}

void Vue_Formulaire::supprLigneJoueur(){

        QLayoutItem* child;

        child = _grid_layout->takeAt(_nombreJoueur-1);
        child->widget()->deleteLater();
        delete child;

        _controleur->supprJoueur();

        _grid_layout->addWidget(_ajouter_joueur,_nombreJoueur-1,0);
        _grid_layout->addWidget(_supprimer_joueur,_nombreJoueur-1,1);

        _nombreJoueur--;

        if(!_ajouter_joueur->isEnabled())
            _ajouter_joueur->setEnabled(true);

        if(_nombreJoueur == 2)
            _supprimer_joueur->setEnabled(false);

}
