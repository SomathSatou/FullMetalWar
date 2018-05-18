#ifndef BARGE_H
#define BARGE_H
#include "transporteur.h"

class Barge : public Transporteur {

public:
    Barge(Couleur couleur)
        : Transporteur(couleur ,4){
        setTypeDeplacement(new Deplacement_eau);
    }
    Barge(const Barge & b)
        : Transporteur(b.getCouleur(),4){
        setTypeDeplacement(new Deplacement_eau);
    }

    ~Barge(){}

    virtual Barge * clone() override{
        return new Barge(*this);
    }

    virtual typePiece type() override{
        return typePiece::BARGE;
    }

    std::string infoPiece() const {
        std::ostringstream oss;
        oss << "Barge";
        return oss.str();
    }
};

#endif // BARGE_H
