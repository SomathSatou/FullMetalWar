#include "piece.h"



Piece::Piece(Couleur couleur)
    : _deplacement(nullptr),
      _couleur(couleur),
      _pointDeVie(2),
      _pointDeVieMax(2)
{}

Couleur Piece::getCouleur() const{
    return _couleur;
}

void Piece::setTypeDeplacement(IDeplacement *deplacement){
    if(_deplacement!=nullptr)
        delete _deplacement;

    _deplacement = deplacement;

}

int Piece::getPointDeVie() const
{
    return _pointDeVie;
}

int Piece::getPointDeVieMax() const
{
    return _pointDeVieMax;
}

void Piece::setPointDeVie(int pointDeVie)
{
    _pointDeVie = pointDeVie;
}

void Piece::setPointDeVieMax(int pointDeVieMax)
{
    _pointDeVieMax = pointDeVieMax;
}

void Piece::prendDesDegats(){
    _pointDeVie--;
}

void Piece::soin(){
    if(_pointDeVie<_pointDeVieMax)
        _pointDeVie++;
}

bool Piece::maj(){
    return _pointDeVie>=0;
}
