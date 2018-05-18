#ifndef ASTRONEF_H
#define ASTRONEF_H

#include<vector>

#include"piece.h"

class Base : public Piece{

public:
    Base(Couleur couleur);

    Base(const Base & b);

    ~Base();

    virtual Base * clone() override;

    std::string infoPiece() const;

    virtual typePiece type() override;


    int getPoids();

private:
    std::vector<Piece *> _unitesEmbarquees;

};

#endif // ASTRONEF_H
