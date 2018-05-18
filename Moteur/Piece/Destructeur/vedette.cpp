#include "vedette.h"

Vedette::Vedette(Couleur couleur)
    :Destructeur(couleur){
    setTypeDeplacement(new Deplacement_eau);
}

Vedette::Vedette(const Vedette &v)
    :Destructeur(v.getCouleur()){
    setTypeDeplacement(new Deplacement_eau);
}

Vedette::~Vedette(){}

Vedette *Vedette::clone(){
    return new Vedette(*this);
}

typePiece Vedette::type(){
    return typePiece::VEDETTE;
}

std::__cxx11::string Vedette::infoPiece() const {
    std::ostringstream oss;
    oss << "Vedette";
    return oss.str();
}
