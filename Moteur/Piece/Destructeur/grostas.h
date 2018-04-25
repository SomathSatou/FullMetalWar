#ifndef GROSTAS_H
#define GROSTAS_H
#include "destructeur.h"

class GrosTas : public Destructeur {

public:
    GrosTas(coordonnees coor, Couleur color,Joueur * j);
    ~GrosTas();
    std::string infoPiece() const;
};

#endif // GROSTAS_H
