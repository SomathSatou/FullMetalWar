#ifndef MINERAI_H
#define MINERAI_H
#include "Moteur/Piece/piece.h"

class Minerai : public Piece {

public:

    Minerai(Couleur couleur);
    Minerai(const Minerai & m);

    ~Minerai();


    virtual Minerai * clone() override;

    virtual typePiece type() override;

    std::string infoPiece() const;

};

#endif // MINERAI_H
