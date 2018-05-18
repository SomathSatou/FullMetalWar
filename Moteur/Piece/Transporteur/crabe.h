#ifndef CRABE_H
#define CRABE_H
#include "transporteur.h"

class Crabe : public Transporteur {

public:
    Crabe(Couleur couleur)
        : Transporteur(couleur ,2){
        setTypeDeplacement(new Deplacement_terre);
    }
    Crabe(const Crabe & c)
        : Transporteur(c.getCouleur() ,2){
        setTypeDeplacement(new Deplacement_terre);
    }
    ~Crabe(){}


    virtual Crabe * clone() override{
        return new Crabe(*this);
    }

    virtual typePiece type() override{
        return typePiece::CRABE;
    }

    std::string infoPiece() const {
        std::ostringstream oss;
        oss << "Crabe";
        return oss.str();
    }

};

#endif // CRABE_H
