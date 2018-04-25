#include "grostas.h"

GrosTas::GrosTas(coordonnees coor, Couleur color, Joueur *j)
    :Destructeur(coor, color, 5,j){
    setTypeDeplacement(new Deplacement_terre_sans_mont);
}

GrosTas::~GrosTas(){}

std::__cxx11::string GrosTas::infoPiece() const {
    std::ostringstream oss;
    oss << "Gros tas";
    return oss.str();
}
