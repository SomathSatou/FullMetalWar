#include "joueur.h"



Joueur::Joueur(std::string nom, Couleur couleur, bool joueur)
    : _nom(nom),
      _couleur(couleur),
      _pointAction(5),
      _pointActionMax(5),
      _joueur(joueur)
{}

std::string Joueur::getPseudonyme() const {
    return _nom;
}

Couleur Joueur::getCouleur() const {
    return _couleur;
}

void Joueur::setPseudonyme(std::string p){
    _nom=p;
}

void Joueur::setCouleur(Couleur c){
    _couleur=c;
}

int Joueur::getNombrePACourant() const {
    return _pointAction;
}

int Joueur::getNombrePAMax() const {
    return _pointActionMax;
}

void Joueur::setNombrePADebut(int p){
    _pointAction=p;
}

void Joueur::setNombrePAMax(int p){
    _pointAction=p;
}

bool Joueur::utilisationPAPossible(){
    return _pointAction > 0;
}

bool Joueur::utilisationPA(){
    if(_pointAction > 0 ){
        _pointAction--;
        return true;
    }
    return false;
}

void Joueur::majTour(){
    _pointAction = _pointActionMax;
}

coups Joueur::jouer(Plateau p){
    coups a;
    UNUSED(p);
    return a;
}

bool Joueur::getJoueur() const
{
    return _joueur;
}

