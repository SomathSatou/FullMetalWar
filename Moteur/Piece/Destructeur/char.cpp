#include "char.h"

Char::Char(coordonnees coor, Couleur color, Joueur *proprietaire)
    : Destructeur(coor ,  color ,5 , proprietaire){
    setTypeDeplacement(new Deplacement_terre);
}

Char::~Char(){}

std::string Char::infoPiece() const {
    std::ostringstream oss;
    oss << "Char maticule ";
    return oss.str();
}
