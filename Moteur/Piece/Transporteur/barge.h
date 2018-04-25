#ifndef BARGE_H
#define BARGE_H
#include "transporteur.h"

class Barge : public Transporteur {

public:
    Barge(coordonnees coor, Couleur color,Joueur * j);
  ~Barge();
  std::string infoPiece() const;
};

#endif // BARGE_H
