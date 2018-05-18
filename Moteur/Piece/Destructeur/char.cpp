#include "char.h"

Char::Char(Couleur couleur)
    : Destructeur(couleur){
    setTypeDeplacement(new Deplacement_terre);
}

Char::Char(const Char &c)
    : Destructeur(c.getCouleur()){
    setTypeDeplacement(new Deplacement_terre);
}

Char::~Char(){}

Char *Char::clone(){
    return new Char(*this);
}

typePiece Char::type(){
    return typePiece::CHAR;
}

std::__cxx11::string Char::infoPiece() const {
    std::ostringstream oss;
    oss << "Char maticule ";
    return oss.str();
}
