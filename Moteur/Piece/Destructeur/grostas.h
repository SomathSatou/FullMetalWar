#ifndef GROSTAS_H
#define GROSTAS_H
#include "destructeur.h"

class GrosTas : public Destructeur {

public:
    GrosTas(Couleur couleur);

    GrosTas(const GrosTas & g);

    ~GrosTas();


    virtual GrosTas * clone() override;

    std::string infoPiece() const;

    virtual typePiece type() override;

    int distance();
};

#endif // GROSTAS_H
