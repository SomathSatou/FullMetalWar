#include "jeu.h"
#include "joueurstochastique.h"


Jeu::Jeu(Joueur *joueur1, Joueur *joueur2, std::vector<std::pair<typePiece, int> > &listePieces, int xPlateau, int yPlateau, TypeCarte typePlateau, int repartitionRessources)
    : _joueur1(joueur1),
      _joueur2(joueur2),
      _plateau(xPlateau,yPlateau,typePlateau,repartitionRessources,joueur1->getCouleur(),joueur2->getCouleur()),
      _nbTours(20),
      _tour(1),
      _joueurCourant(true)
{
    UNUSED(listePieces);

    _plateau.creationPiece(Coordonnee(0,0),typePiece::CHAR,_joueur1->getCouleur());
    _plateau.creationPiece(Coordonnee(xPlateau-1,yPlateau-1),typePiece::CHAR,_joueur2->getCouleur());
//    _plateau.creationPiece(Coordonnee(0,1),typePiece::CHAR,_joueur1->getCouleur());
//    _plateau.creationPiece(Coordonnee(xPlateau-1,yPlateau-2),typePiece::CHAR,_joueur2->getCouleur());
//    _plateau.creationPiece(Coordonnee(1,0),typePiece::CHAR,_joueur1->getCouleur());
//    _plateau.creationPiece(Coordonnee(xPlateau-2,yPlateau-1),typePiece::CHAR,_joueur2->getCouleur());
    init();
        if (joueurStochastique *j1 = dynamic_cast<joueurStochastique*>(joueur1)){
            j1->setArbre(&_stochastique);
        }
        if (joueurStochastique * j2 = dynamic_cast<joueurStochastique*>(joueur2)){
            j2->setArbre(&_stochastique);
        }
}

Plateau &Jeu::getPlateau(){
    return _plateau;
}

int Jeu::getJoueurCourant() const {
    return _joueurCourant;
}

Joueur *Jeu::getJoueur1(){
    return _joueur1;
}

Joueur *Jeu::getJoueur2(){
    return _joueur2;
}

Joueur *Jeu::getJoueur(Couleur c) {
    if(_joueur1->getCouleur()==c)
        return _joueur1;
    else
        if(_joueur2->getCouleur()==c)
            return _joueur2;
        else
            return nullptr;
}

Joueur *Jeu::getJoueurCourantPtr(){
    return (_joueurCourant? _joueur1 : _joueur2);
}

int Jeu::getTour() const {
    return _tour;
}

bool Jeu::ordre(coup c){
    if(_joueurCourant? _joueur1->utilisationPAPossible() : _joueur2->utilisationPAPossible()){
        if(_plateau.ordre(c)){
            _joueurCourant? _joueur1->utilisationPA() : _joueur2->utilisationPA();
            return true;
        }
    }
    return false;
}

void Jeu::ordre(coups c){
    for(auto co : c)
        ordre(co);
}

void Jeu::finDeTourJoueur(){
    _joueurCourant=!_joueurCourant;
    _plateau.finDeTourJoueur();
    _joueur1->majTour();
    _joueur2->majTour();
}

void Jeu::init(){Noeud *tmp = new Noeud(_plateau);
                 _stochastique.Courant = tmp;
                              _stochastique.Racine = tmp;}

Arbre Jeu::getStochastique() const
{
    return _stochastique;
}

void Jeu::setStochastique(const Arbre &stochastique)
{
    _stochastique = stochastique;
}
