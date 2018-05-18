#include "controleur_jeu.h"
#include<iostream>
using namespace std;

QString TYPECASEToQString(typeCase t) {
    switch(t) {

    case typeCase::PLAINE :
        return "PLAINE";

    case typeCase::MONTAGNE :
        return "MONTAGNE";

    case typeCase::MER :
        return "MER";

    case typeCase::MARAIS :
        return "MARAIS";

    case typeCase::RECIF :
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

//Controleur_Jeu::Controleur_Jeu(const std::vector<Joueur*>  listeJoueurs,int longueur, int largeur, QObject *parent) :
//    QObject(parent),
//    _parent(parent),
//    _positionCurrentCase(0,0)
//{
//    std::vector<std::pair<typePiece,int>> listePieces;

//    // liste des pieces a ajouter ************************************************************
//    /*  listePieces.push_back(QuantPiece(1,TOURELLE));
//     listePieces.push_back(QuantPiece(1,PONDEUSE));
//    listePieces.push_back(QuantPiece(1,TOURELLE));*/


//    _moteur = new Jeu(listeJoueurs[0], listeJoueurs[1], listePieces,longueur,largeur);
//    _vue_jeu = new Vue_Jeu(longueur,largeur,static_cast<QWidget*>(_parent));

//    // Connection de la modelisation et de la minimap pour qu'elle puisse récupérer les valeurs des cases dans le moteur
//    connect(this,&Controleur_Jeu::sendCaseModelisation,_vue_jeu->getModelisation(),&ModelisationJeu::updateCase);
//    connect(this,&Controleur_Jeu::sendCaseMiniMap,_vue_jeu->getMiniMap(),&MiniMap::updateCase);
//    connect(this,&Controleur_Jeu::sendModelisationUnite,_vue_jeu->getModelisationUnite(),&ModelisationUnite::parametrerModelisation);

//    // Connection du bouton de fin de tour
//    connect(_vue_jeu->getFinDeTour(),&QPushButton::clicked,this,&Controleur_Jeu::getClickFinDeTour);

//    //Connection de la modelisation pour qu'elle puisse envoyer les coordonnées de la case sélectionnée par l'utilisateur
//    connect(_vue_jeu->getModelisation(),&ModelisationJeu::sendPositionClick,this,&Controleur_Jeu::getClickModelisation);

//    //Connection de la modelisation pour qu'elle puisse envoyer la case d'arrivée d'une pièce lors d'un déplacement
//    connect(_vue_jeu->getModelisation(),&ModelisationJeu::sendPositionDeplacement,this,&Controleur_Jeu::getPositionDeplacement);
//    //connect(this,&Controleur_Jeu::sendEcouterDeplacement,_vue_jeu->getModelisation(),&ModelisationJeu::setEcouterDeplacement);

//    // Connection de la vue du jeu avec les signaux du controleur qui permettront d'update les valeurs des ongletJoueur appartenant à la vue
//    connect(this,&Controleur_Jeu::sendCreateOnglet,_vue_jeu,&Vue_Jeu::createOnglet);
//    connect(this,&Controleur_Jeu::sendPAOnglet,_vue_jeu,&Vue_Jeu::setPAOnglet);

//    // Connection de l'InfoBarre avec le signal du controleur qui permet de lui envoyer la marréé courante, la suivante et le tour actuel
//    connect(this,&Controleur_Jeu::sendValuesInfoBarre,_vue_jeu->getInfoBarre(),&InfoBarre::updateInfoBarre);

//    // Connection des signaux du controleur pour envoyer les informations de la pièce selectionnées au tableau de bord
//    connect(this,&Controleur_Jeu::sendInformationDestructeur,_vue_jeu->getInformationPiece(),&InformationPiece::putInformationDestructeur);
//    connect(this,&Controleur_Jeu::sendInformationTransporteur,_vue_jeu->getInformationPiece(),&InformationPiece::putInformationTransporteur);
//    connect(this,&Controleur_Jeu::sendInformationNeutre,_vue_jeu->getInformationPiece(),&InformationPiece::putInformationNeutre);
//    connect(this,&Controleur_Jeu::sendInformationVide,_vue_jeu->getInformationPiece(),&InformationPiece::putInformationVide);

//    initialisation(); // On doit initialiser les valeurs dans la vue une fois que les valeurs dans le moteur sont prêtes

//}


Controleur_Jeu::Controleur_Jeu(const std::vector<Joueur*> listeJoueurs,int longueur, int largeur,TypeCarte type,bool min,std::vector<std::pair<typePiece,int>> listePie, QObject *parent) :
    QObject(parent),
    _parent(parent),
    _positionCurrentCase(0,0),
    _listePieces(listePie)
{
    _moteur = new Jeu(listeJoueurs[0], listeJoueurs[1],_listePieces,longueur,largeur, type, min? 3 : 0);
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

//    for(auto c : getMoteur()->getJoueurCourantPtr()->jouer(getMoteur()->getPlateau()) ){

//        getClickModelisation(c.src.x,c.src.y);
//        getPositionDeplacement(c.dst.x,c.dst.y);
//    }
}

Controleur_Jeu::~Controleur_Jeu() {
    delete _moteur;
}

Vue_Jeu *Controleur_Jeu::getVueJeu() const { return _vue_jeu; }

void Controleur_Jeu::getCase(int i) {

    Case& c = _moteur->getPlateau().getCase(i);

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
        _couleur = COULEURToInt(c.getPiece()->getCouleur());
    }

    emit sendCaseMiniMap(_typecase,_isPiece,_couleur,i);
    emit sendCaseModelisation(_typecase,_typePiece,_couleur,i);
}

Jeu *Controleur_Jeu::getMoteur() const
{
    return _moteur;
}

void Controleur_Jeu::setMoteur(Jeu *moteur)
{
    _moteur = moteur;
}

void Controleur_Jeu::getClickFinDeTour() {
    _moteur->finDeTourJoueur();

    emit sendPAOnglet(_moteur->getJoueurCourantPtr()->getNombrePACourant(),
                      _moteur->getJoueurCourantPtr()->getNombrePAMax(),
                      _moteur->getJoueurCourant());

    static_cast<QWidget*>(_parent)->setFocus(); // Permet de redonner le focus à la MainWindow afin d'écouter les entrées clavier

    int tour = _moteur->getTour();
    std::string joueur = _moteur->getJoueurCourantPtr()->getPseudonyme();
    //    if(tour != -1)
    emit sendValuesInfoBarre(tour,joueur);
    //    else {
    //        const Joueur* gagnant = _moteur->getJoueur(0);;
    //        for(unsigned int i = 1; i<_moteur->getListeJoueurs().size(); i++){
    //            const Joueur* j = _moteur->getJoueur(i);
    //            if(j->getPseudonyme().compare("NEUTRE") != 0)
    //                if(j->getScore()>gagnant->getScore())
    //                    gagnant = j;
    //        } // END FOR

    //        emit putScoreScreen(gagnant->getPseudonyme().c_str(),gagnant->getScore());
    //    } // END ELSE


    //    if(dynamic_cast<joueurStochastique *>(_moteur->getJoueurCourrantPtr())){
    //        std::cout << "\nLe joueur stochastique joue\n";
    //        for(const auto & a : _moteur->getJoueurCourrantPtr()->joue()){
    //            int xs = a.src%_moteur->getCarte().getLongueur();
    //            int ys = (a.src-xs) / _moteur->getCarte().getLongueur();
    //            getClickModelisation(xs,ys);
    //            int xd = a.dest%_moteur->getCarte().getLongueur();
    //            int yd = (a.dest-xd) / _moteur->getCarte().getLongueur();
    //            std::cout << "\nOrdre de " << xs << "-" << ys << " a " << xd << "-" << yd << "\n";
    //            getPositionDeplacement(xd,yd);
    //            //ordre(coordonnees(xs,ys),coordonnees(xd,yd));
    //        }
    //    }

    for(auto c :_moteur->getJoueurCourantPtr()->jouer(_moteur->getPlateau()) ){

        getClickModelisation(c.src.x,c.src.y);
        getPositionDeplacement(c.dst.x,c.dst.y);
    }

} // END

void Controleur_Jeu::initialisation() {

    // Init des cartes (minimap et modelisation)
    for(int i = 0; i<_moteur->getPlateau().getTaille(); i++)
        getCase(i);

    // Création des onglets joueurs

    //    for(unsigned int i = 0; i<_moteur->getListeJoueurs().size(); i++){
    //        const Joueur* j = _moteur->getJoueur(i);
    //        if(j->getPseudonyme().compare("NEUTRE") != 0)
    //            emit sendCreateOnglet(j->getPseudonyme().c_str(),j->getNombrePACourant(),j->getNombrePAMax(),j->getCouleur());
    //    } // END FOR

    emit sendCreateOnglet(_moteur->getJoueur2()->getPseudonyme().c_str(),_moteur->getJoueur2()->getNombrePACourant(),_moteur->getJoueur2()->getNombrePAMax(),_moteur->getJoueur2()->getCouleur());
    emit sendCreateOnglet(_moteur->getJoueur1()->getPseudonyme().c_str(),_moteur->getJoueur1()->getNombrePACourant(),_moteur->getJoueur1()->getNombrePAMax(),_moteur->getJoueur1()->getCouleur());

    //Initialisation de l'InfoBarre
    emit sendValuesInfoBarre(_moteur->getTour(),_moteur->getJoueurCourantPtr()->getPseudonyme());

} // END

void Controleur_Jeu::getClickModelisation(int x, int y) {

    _positionCurrentCase.setX(x);
    if(y==_moteur->getPlateau().getLongueur())
        y=_moteur->getPlateau().getLongueur()-1;

    _positionCurrentCase.setY(y);

    if(_moteur->getPlateau().getCase(x,y).hasPiece()){
        Piece* p = _moteur->getPlateau().getCase(x,y).getPiece();

        QString proprio = _moteur->getJoueur(p->getCouleur())->getPseudonyme().c_str();
        QString nom_piece = PieceToQString(p);

        emit sendModelisationUnite(nom_piece,p->getCouleur());

        const Transporteur* transp = dynamic_cast<const Transporteur*>(p);
        if(transp) {
            emit sendInformationTransporteur(nom_piece,transp->getPointDeVie(),transp->getPointDeVieMax(),proprio,1,1);//transp->getEspaceCourant(),transp->getEspaceStockage());
        } // END IF
        else {
            const Destructeur* destr = dynamic_cast<const Destructeur*>(p);
            if(destr) {
                emit sendInformationDestructeur(nom_piece,destr->getPointDeVie(),destr->getPointDeVieMax(),proprio,destr->getMunition(),1);
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

    if(_moteur->getPlateau().getCase(x,y).hasPiece()){

        _moteur->getPlateau().coupsPossibles();

    }

    if(_moteur->getPlateau().getCase(_positionCurrentCase.x(),_positionCurrentCase.y()).hasPiece()){
        _moteur->ordre(coup (Coordonnee(_positionCurrentCase.x(),_positionCurrentCase.y()),Coordonnee(x,y),(_moteur->getPlateau().getCase(x,y).hasPiece()? typeAction::ATTAQUER : typeAction::DEPLACER)));

        int longueur = _moteur->getPlateau().getLongueur(); // getLongeur()

        getCase(longueur * y + x);
        getCase(longueur * _positionCurrentCase.y() + _positionCurrentCase.x());

        emit sendPAOnglet(_moteur->getJoueurCourantPtr()->getNombrePACourant(),
                          _moteur->getJoueurCourantPtr()->getNombrePAMax(),
                          _moteur->getJoueurCourant());

        _positionCurrentCase.setX(x);
        _positionCurrentCase.setY(y);
    }

}


