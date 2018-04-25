#include "Minerai.h"

Minerai::Minerai(coordonnees coor, Couleur color, Joueur *proprietaire):
    Piece(coor ,color,1 , proprietaire){
    setTypeDeplacement(new Deplacement_nul);
    setTypeAttaque(new PorteeNulle);
}

Minerai::Minerai::~Minerai(){}

std::string Minerai::Minerai::infoPiece() const {
    std::ostringstream oss;
    oss << "Minerai";
    return oss.str();
}
