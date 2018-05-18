#include "base.h"

Base::Base(Couleur couleur):
    Piece(couleur){
    setTypeDeplacement(new Deplacement_nul);
}

Base::Base(const Base &b):
    Piece(b.getCouleur()){
    setTypeDeplacement(new Deplacement_nul);
}

Base::~Base(){}

Base *Base::clone(){
    return new Base(*this);
}

std::__cxx11::string Base::infoPiece() const{
    std::ostringstream oss;
    oss << "Base ";
    return oss.str();
}

typePiece Base::type(){
    return typePiece::BASE;
}

int Base::getPoids(){return 15;}
