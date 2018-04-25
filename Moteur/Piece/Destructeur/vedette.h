#ifndef VEDETTE_H
#define VEDETTE_H
#include "destructeur.h"

class Vedette : public Destructeur
{

public:
    Vedette(coordonnees coor, Couleur color,Joueur *j)
        :Destructeur(coor, color,5, j){
        setTypeDeplacement(new Deplacement_eau);
    }
    ~Vedette(){}
    std::string infoPiece() const {
        std::ostringstream oss;
        oss << "Vedette";
        return oss.str();
    }

};

#endif // VEDETTE_H
