#ifndef CHAR_H
#define CHAR_H
#include "destructeur.h"

class Char : public Destructeur {
public:
    Char(coordonnees coor, Couleur color , Joueur * proprietaire );
    ~Char();

    std::string infoPiece() const;
};


#endif // CHAR_H
