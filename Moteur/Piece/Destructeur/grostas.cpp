#include "grostas.h"



GrosTas::GrosTas(Couleur couleur)
    :Destructeur(couleur){
    setTypeDeplacement(new Deplacement_terre_sans_mont);
}

GrosTas::GrosTas(const GrosTas &g)
    :Destructeur(g.getCouleur()){
    setTypeDeplacement(new Deplacement_terre_sans_mont);
}

GrosTas::~GrosTas(){}

GrosTas *GrosTas::clone(){
    return new GrosTas(*this);
}

std::string GrosTas::infoPiece() const {
    std::ostringstream oss;
    oss << "Gros tas";
    return oss.str();
}

typePiece GrosTas::type(){
    return typePiece::GROS_TAS;
}

int GrosTas::distance(){
    return 3;
}
