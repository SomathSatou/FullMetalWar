#include "crabe.h"

Crabe::Crabe(coordonnees coor, Couleur color, Joueur *j)
    : Transporteur(coor , color, j,2){
    setTypeDeplacement(new Deplacement_terre);
}

Crabe::~Crabe(){}

std::string Crabe::infoPiece() const {
    std::ostringstream oss;
    oss << "Crabe";
    return oss.str();
}
