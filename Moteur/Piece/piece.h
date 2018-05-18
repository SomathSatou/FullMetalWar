#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <sstream>

#include "defineclass.h"
#include "Moteur/Piece/Comportement/allcomportements.h"

class Piece
{
public:
    Piece(Couleur couleur);

    Couleur getCouleur() const;

    void setTypeDeplacement(IDeplacement * deplacement);

    IDeplacement * _deplacement;

    int getPointDeVie() const;
    void setPointDeVie(int pointDeVie);
    int getPointDeVieMax() const;
    void setPointDeVieMax(int pointDeVieMax);

    virtual typePiece type()=0;

    void prendDesDegats();

    virtual Piece * clone()=0;

    void soin();

    virtual bool maj();


private:
    Couleur _couleur;
    int _pointDeVie;
    int _pointDeVieMax;

};

#endif // PIECE_H
