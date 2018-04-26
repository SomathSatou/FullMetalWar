#include "controleur_jeu.h"
#include<iostream>
using namespace std;

QString TYPECASEToQString(TYPECASE t) {
    switch(t) {

    case TYPECASE::PLAINE :
        return "PLAINE";

    case TYPECASE::MONTAGNE :
        return "MONTAGNE";

    case TYPECASE::MER :
        return "MER";

    case TYPECASE::MARAIS :
        return "MARAIS";

    case TYPECASE::RECIF :
        return "RECIF";

    default:
        return "VIDE";

    } // END SWITCH

} // END

QString PieceToQString(const Piece *p) {

    if(dynamic_cast<const Barge*>(p))
        return QString("BARGE");

    if(dynamic_cast<const Base*>(p))
        return QString("BASE");


    if(dynamic_cast<const Char*>(p))
        return QString("CHAR");

    if(dynamic_cast<const Crabe*>(p))
        return QString("Crabe");

    if(dynamic_cast<const GrosTas*>(p))
        return QString("GROSTAS");

    if(dynamic_cast<const Minerai*>(p))
        return QString("Minerai");

    if(dynamic_cast<const Pondeuse*>(p))
        return QString("PONDEUSE");

    if(dynamic_cast<const Vedette*>(p))
        return QString("VEDETTE");

    if(dynamic_cast<const Minerai*>(p))
        return QString("MINERAI");

    return "VIDE";
}

int COULEURToInt(Couleur c) {
    switch(c) {
    case Couleur::ROUGE :
        return 0;
    case Couleur::BLEU :
        return 1;
    case Couleur::VERT :
        return 2;
    case Couleur::JAUNE :
        return 3;
    default:
        return -1;
    } // END SWITCH

} // END

Controleur_Jeu::Controleur_Jeu(const std::vector<Joueur*>  listeJoueurs,int longueur, int largeur, QObject *parent) :
    QObject(parent),
    _parent(parent),
    _positionCurrentCase(0,0)
{
    std::vector<std::pair<typePiece,int>> listePieces;

    // liste des pieces a ajouter ************************************************************
  /*  listePieces.push_back(QuantPiece(1,TOURELLE));
     listePieces.push_back(QuantPiece(1,PONDEUSE));
    listePieces.push_back(QuantPiece(1,TOURELLE));*/


    _moteur = new Jeu(listeJoueurs,listePieces,longueur,largeur);
    _vue_jeu = new Vue_Jeu(longueur,largeur,static_cast<QWidget*>(_parent));

    // Connection de la modelisation et de la minimap pour qu'elle puisse récupérer les valeurs des cases dans le moteur
    connect(this,&Controleur_Jeu::sendCaseModelisation,_vue_jeu->getModelisation(),&ModelisationJeu::updateCase);
    connect(this,&Controleur_Jeu::sendCaseMiniMap,_vue_jeu->getMiniMap(),&MiniMap::updateCase);
    connect(this,&Controleur_Jeu::sendModelisationUnite,_vue_jeu->getModelisationUnite(),&ModelisationUnite::parametrerModelisation);

    // Connection du bouton de fin de tour
    connect(_vue_jeu->getFinDeTour(),&QPushButton::clicked,this,&Controleur_Jeu::getClickFinDeTour);

    //Connection de la modelisation pour qu'elle puisse envoyer les coordonnées de la case sélectionnée par l'utilisateur
    connect(_vue_jeu->getModelisation(),&ModelisationJeu::sendPositionClick,this,&Controleur_Jeu::getClickModelisation);

    //Connection de la modelisation pour qu'elle puisse envoyer la case d'arrivée d'une pièce lors d'un déplacement
    connect(_vue_jeu->getModelisation(),&ModelisationJeu::sendPositionDeplacement,this,&Controleur_Jeu::getPositionDeplacement);
    //connect(this,&Controleur_Jeu::sendEcouterDeplacement,_vue_jeu->getModelisation(),&ModelisationJeu::setEcouterDeplacement);

    // Connection de la vue du jeu avec les signaux du controleur qui permettront d'update les valeurs des ongletJoueur appartenant à la vue
    connect(this,&Controleur_Jeu::sendCreateOnglet,_vue_jeu,&Vue_Jeu::createOnglet);
    connect(this,&Controleur_Jeu::sendPAOnglet,_vue_jeu,&Vue_Jeu::setPAOnglet);

    // Connection de l'InfoBarre avec le signal du controleur qui permet de lui envoyer la marréé courante, la suivante et le tour actuel
    connect(this,&Controleur_Jeu::sendValuesInfoBarre,_vue_jeu->getInfoBarre(),&InfoBarre::updateInfoBarre);

    // Connection des signaux du controleur pour envoyer les informations de la pièce selectionnées au tableau de bord
    connect(this,&Controleur_Jeu::sendInformationDestructeur,_vue_jeu->getInformationPiece(),&InformationPiece::putInformationDestructeur);
    connect(this,&Controleur_Jeu::sendInformationTransporteur,_vue_jeu->getInformationPiece(),&InformationPiece::putInformationTransporteur);
    connect(this,&Controleur_Jeu::sendInformationNeutre,_vue_jeu->getInformationPiece(),&InformationPiece::putInformationNeutre);
    connect(this,&Controleur_Jeu::sendInformationVide,_vue_jeu->getInformationPiece(),&InformationPiece::putInformationVide);

    initialisation(); // On doit initialiser les valeurs dans la vue une fois que les valeurs dans le moteur sont prêtes
}


Controleur_Jeu::Controleur_Jeu(const std::vector<Joueur*> listeJoueurs,int longueur, int largeur,TypeCarte type,bool min,std::vector<std::pair<typePiece,int>> listePie, QObject *parent) :
    QObject(parent),
    _parent(parent),
    _positionCurrentCase(0,0),
    _listePieces(listePie)
{

    _moteur = new Jeu(listeJoueurs,_listePieces,type,min,longueur,largeur);
    _vue_jeu = new Vue_Jeu(longueur,largeur,static_cast<QWidget*>(_parent));

    // Connection de la modelisation et de la minimap pour qu'elle puisse récupérer les valeurs des cases dans le moteur
    connect(this,&Controleur_Jeu::sendCaseModelisation,_vue_jeu->getModelisation(),&ModelisationJeu::updateCase);
    connect(this,&Controleur_Jeu::sendCaseMiniMap,_vue_jeu->getMiniMap(),&MiniMap::updateCase);
    connect(this,&Controleur_Jeu::sendModelisationUnite,_vue_jeu->getModelisationUnite(),&ModelisationUnite::parametrerModelisation);

    // Connection du bouton de fin de tour
    connect(_vue_jeu->getFinDeTour(),&QPushButton::clicked,this,&Controleur_Jeu::getClickFinDeTour);

    //Connection de la modelisation pour qu'elle puisse envoyer les coordonnées de la case sélectionnée par l'utilisateur
    connect(_vue_jeu->getModelisation(),&ModelisationJeu::sendPositionClick,this,&Controleur_Jeu::getClickModelisation);

    //Connection de la modelisation pour qu'elle puisse envoyer la case d'arrivée d'une pièce lors d'un déplacement
    connect(_vue_jeu->getModelisation(),&ModelisationJeu::sendPositionDeplacement,this,&Controleur_Jeu::getPositionDeplacement);
    //connect(this,&Controleur_Jeu::sendEcouterDeplacement,_vue_jeu->getModelisation(),&ModelisationJeu::setEcouterDeplacement);

    // Connection de la vue du jeu avec les signaux du controleur qui permettront d'update les valeurs des ongletJoueur appartenant à la vue
    connect(this,&Controleur_Jeu::sendCreateOnglet,_vue_jeu,&Vue_Jeu::createOnglet);
    connect(this,&Controleur_Jeu::sendPAOnglet,_vue_jeu,&Vue_Jeu::setPAOnglet);

    // Connection de l'InfoBarre avec le signal du controleur qui permet de lui envoyer la marréé courante, la suivante et le tour actuel
    connect(this,&Controleur_Jeu::sendValuesInfoBarre,_vue_jeu->getInfoBarre(),&InfoBarre::updateInfoBarre);

    // Connection des signaux du controleur pour envoyer les informations de la pièce selectionnées au tableau de bord
    connect(this,&Controleur_Jeu::sendInformationDestructeur,_vue_jeu->getInformationPiece(),&InformationPiece::putInformationDestructeur);
    connect(this,&Controleur_Jeu::sendInformationTransporteur,_vue_jeu->getInformationPiece(),&InformationPiece::putInformationTransporteur);
    connect(this,&Controleur_Jeu::sendInformationNeutre,_vue_jeu->getInformationPiece(),&InformationPiece::putInformationNeutre);
    connect(this,&Controleur_Jeu::sendInformationVide,_vue_jeu->getInformationPiece(),&InformationPiece::putInformationVide);

    initialisation(); // On doit initialiser les valeurs dans la vue une fois que les valeurs dans le moteur sont prêtes
}

Controleur_Jeu::~Controleur_Jeu() {
    delete _moteur;
}

void Controleur_Jeu::getCase(int i) {

    const CaseMap& c = _moteur->getCarte().getCase(i);

    QString _typecase = TYPECASEToQString(c.getType());
    QString _typePiece;
    bool _isPiece;
    int _couleur;

    if(!c.hasPiece()) {
        _isPiece = false;
        _couleur = -1;
        _typePiece = "VIDE";
    }
    else {
        _isPiece = true;
        const Piece* p = c.getPiece();
        _typePiece = PieceToQString(p);
        _couleur = COULEURToInt(c.getPiece()->getJoueur()->getCouleur());
    }

    emit sendCaseMiniMap(_typecase,_isPiece,_couleur,i);
    emit sendCaseModelisation(_typecase,_typePiece,_couleur,i);
}

void Controleur_Jeu::getClickFinDeTour() {
    _moteur->finDeTourJoueur();

    emit sendPAOnglet(_moteur->getJoueur(_moteur->getJoueurCourrant())->getNombrePACourant(),
                                         _moteur->getJoueur(_moteur->getJoueurCourrant())->getNombrePAMax(),
                                         _moteur->getJoueurCourrant());

    static_cast<QWidget*>(_parent)->setFocus(); // Permet de redonner le focus à la MainWindow afin d'écouter les entrées clavier

    int tour = _moteur->getTourCourrant();
    std::string joueur = _moteur->getListeJoueurs()[_moteur->getJoueurCourrant()]->getPseudonyme();
    if(tour != -1)
        emit sendValuesInfoBarre(tour,joueur);
    else {
        const Joueur* gagnant = _moteur->getJoueur(0);;
        for(unsigned int i = 1; i<_moteur->getListeJoueurs().size(); i++){
            const Joueur* j = _moteur->getJoueur(i);
            if(j->getPseudonyme().compare("NEUTRE") != 0)
                if(j->getScore()>gagnant->getScore())
                    gagnant = j;
        } // END FOR

        emit putScoreScreen(gagnant->getPseudonyme().c_str(),gagnant->getScore());
    } // END ELSE
} // END

void Controleur_Jeu::initialisation() {

    // Init des cartes (minimap et modelisation)
    for(int i = 0; i<_moteur->getCarte().getTaille(); i++)
        getCase(i);

    // Création des onglets joueurs
    for(unsigned int i = 0; i<_moteur->getListeJoueurs().size(); i++){
        const Joueur* j = _moteur->getJoueur(i);
        if(j->getPseudonyme().compare("NEUTRE") != 0)
            emit sendCreateOnglet(j->getPseudonyme().c_str(),j->getNombrePACourant(),j->getNombrePAMax(),j->getCouleur());
    } // END FOR

    //Initialisation de l'InfoBarre
    emit sendValuesInfoBarre(_moteur->getTourCourrant(),_moteur->getListeJoueurs()[0]->getPseudonyme());

} // END

void Controleur_Jeu::getClickModelisation(int x, int y) {

    _positionCurrentCase.setX(x);
    if(y==_moteur->getCarte().getLongueur())
        y=_moteur->getCarte().getLongueur()-1;

    _positionCurrentCase.setY(y);

    if(_moteur->getCarte().getCase(x,y).hasPiece()){
        const Piece* p = _moteur->getCarte().getCase(x,y).getPiece();

        QString proprio = p->getJoueur()->getPseudonyme().c_str();
        QString nom_piece = PieceToQString(p);

        emit sendModelisationUnite(nom_piece,p->getJoueur()->getCouleur());

        const Transporteur* transp = dynamic_cast<const Transporteur*>(p);
        if(transp) {
            emit sendInformationTransporteur(nom_piece,transp->getPointDeVie(),transp->getPointDeVieMax(),proprio,transp->getEspaceCourant(),transp->getEspaceStockage());
        } // END IF
        else {
            const Destructeur* destr = dynamic_cast<const Destructeur*>(p);
            if(destr) {
                emit sendInformationDestructeur(nom_piece,destr->getPointDeVie(),destr->getPointDeVieMax(),proprio,destr->getCurrentMunition(),destr->getMunition());
            } // END IF
            else {
                    emit sendInformationNeutre(nom_piece,p->getPointDeVie(),p->getPointDeVieMax(),proprio);
            } // END ELSE

        } // END ELSE
    }
   else {
        emit sendInformationVide();
        emit sendModelisationUnite("VIDE",Couleur::NEUTRE);
    }
}

void Controleur_Jeu::getPositionDeplacement(int x, int y) {


    if(_moteur->getCarte().getCase(x,y).hasPiece()){

        _moteur->getCarte().getCase(x,y).getPiece()->actionsPossibles();

    }

    if(_moteur->getCarte().getCase(_positionCurrentCase.x(),_positionCurrentCase.y()).hasPiece()){

        _moteur->ordre(coordonnees(_positionCurrentCase.x(),_positionCurrentCase.y()),coordonnees(x,y));

        int longueur = _moteur->getCarte().getLongueur(); // getLongeur()

        getCase(longueur * y + x);
        getCase(longueur * _positionCurrentCase.y() + _positionCurrentCase.x());

        emit sendPAOnglet(_moteur->getJoueur(_moteur->getJoueurCourrant())->getNombrePACourant(),
                                             _moteur->getJoueur(_moteur->getJoueurCourrant())->getNombrePAMax(),
                                             _moteur->getJoueurCourrant());

        _positionCurrentCase.setX(x);
        _positionCurrentCase.setY(y);
    }

}


