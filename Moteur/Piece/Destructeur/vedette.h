#ifndef VEDETTE_H
#define VEDETTE_H
#include "destructeur.h"

class Vedette : public Destructeur
{

public:
    Vedette(Couleur couleur);

    Vedette(const Vedette & v);

    ~Vedette();


    virtual Vedette * clone() override;

    virtual typePiece type() override;


    std::string infoPiece() const;

};

#endif // VEDETTE_H
