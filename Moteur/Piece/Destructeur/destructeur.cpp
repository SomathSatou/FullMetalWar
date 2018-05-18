#include "destructeur.h"

Destructeur::Destructeur(Couleur couleur)
    : Piece(couleur),
      _munition(1){
}

Destructeur::~Destructeur(){}

bool Destructeur::pretATirer(){return _munition>0;}

void Destructeur::tire(){ _munition--;}

void Destructeur::rechargement() {_munition = 1;}

int Destructeur::getMunition() const {return _munition;}

bool Destructeur::maj(){
    _munition=1;
    return Piece::maj();
}

int Destructeur::distance(){
    return 2;
}
