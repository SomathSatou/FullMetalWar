#ifndef CRABE_H
#define CRABE_H
#include "transporteur.h"

class Crabe : public Transporteur {

public:
    Crabe(coordonnees coor, Couleur color,Joueur * j);
    ~Crabe();
    std::string infoPiece() const;

};

#endif // CRABE_H
