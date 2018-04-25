#include "base.h"

Base::Base(coordonnees coor, Couleur coul, Joueur *j):
    Piece(coor,coul,15,j){
    setTypeDeplacement(new Deplacement_nul);
    setTypeAttaque(new PorteeNulle);
}

Base::~Base(){}

std::string Base::infoPiece() const{
    std::ostringstream oss;
    oss << "Base ";
    return oss.str();
}

int Base::getPoids(){return 15;}
