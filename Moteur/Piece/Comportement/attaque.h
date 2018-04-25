#ifndef IATTAQUE_H
#define IATTAQUE_H

#include "Moteur/Jeu/Carte.h"
#include "Moteur/Piece/Piece.h"

class IAttaque{
public:
    virtual coups aPortee(Carte * carte , coordonnees source , Couleur color) =0;
    virtual ~IAttaque();
};

class Portee3 : public IAttaque{
public:
    coups aPortee(Carte * carte , coordonnees source , Couleur color) override;

};


class PorteeNulle : public IAttaque{
public:
    coups aPortee(Carte * carte , coordonnees source , Couleur color) override;

};

#endif // IATTAQUE_H
