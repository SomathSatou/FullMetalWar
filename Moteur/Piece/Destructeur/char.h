#ifndef CHAR_H
#define CHAR_H
#include "destructeur.h"

class Char : public Destructeur {

public:
    Char(Couleur couleur);

    Char(const Char & c);

    ~Char();


    virtual Char * clone() override;

    virtual typePiece type() override;

    std::string infoPiece() const;
};


#endif // CHAR_H
