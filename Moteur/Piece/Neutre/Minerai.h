#ifndef MINERAI_H
#define MINERAI_H
#include "Moteur/Piece/Piece.h"

class Minerai : public Piece {

public:

    Minerai(coordonnees coor, Couleur color, Joueur * proprietaire);
    ~Minerai();
    bool seDeplacer(int positionX, int positionY);
    std::string infoPiece() const;

};

#endif // MINERAI_H
