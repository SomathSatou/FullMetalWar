#ifndef DESTRUCTEUR_H
#define DESTRUCTEUR_H
#include "Moteur/Piece/Piece.h"

class Destructeur : public Piece
{
public:
    // Constructeur avec les informations nécessaires à la création d'un Destructeur
    Destructeur(coordonnees coor, Couleur color, int pointDeVieMax , Joueur * proprietaire);
    ~Destructeur();

    void Reload();
    int getCurrentMunition() const;
    int getMunition() const;

    bool attaque(const coordonnees & ennemi) override;

private:
    int m_munition;

};

#endif // DESTRUCTEUR_H
