#include "Minerai.h"



Minerai::Minerai(Couleur couleur):
    Piece(couleur){
    setTypeDeplacement(new Deplacement_nul);
}

Minerai::Minerai(const Minerai &m):
    Piece(m.getCouleur()){
    setTypeDeplacement(new Deplacement_nul);
}

Minerai::~Minerai(){}

Minerai *Minerai::clone(){
    return new Minerai(*this);
}

typePiece Minerai::type(){
    return typePiece::MINERAI;
}

std::string Minerai::infoPiece() const {
    std::ostringstream oss;
    oss << "Minerai";
    return oss.str();
}
