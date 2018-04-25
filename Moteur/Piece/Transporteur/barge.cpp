#include "barge.h"

Barge::Barge(coordonnees coor, Couleur color,Joueur * j)
    : Transporteur(coor , color , j,4){
    setTypeDeplacement(new Deplacement_eau);
}

Barge::~Barge(){}

std::string Barge::infoPiece() const {
    std::ostringstream oss;
    oss << "Barge";
    return oss.str();
}
