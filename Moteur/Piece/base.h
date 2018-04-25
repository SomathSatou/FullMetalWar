#ifndef ASTRONEF_H
#define ASTRONEF_H

#include<vector>

#include"Piece.h"

class Base : public Piece{

public:
    Base(coordonnees coor,Couleur coul,Joueur * j);
    ~Base();
    std::string infoPiece() const;
    int getPoids();

private:
    std::vector<Piece *> _unitesEmbarquees;

};

#endif // ASTRONEF_H
