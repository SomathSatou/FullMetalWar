#ifndef JOUEURSTOCHASTIQUE_H
#define JOUEURSTOCHASTIQUE_H

#include "arbrestochastique.h"
#include "Joueur.h"

class joueurStochastique : public Joueur
{
public:
    joueurStochastique();

    std::vector<Action> joue() override;

private:
    Noeud * Racine;
    Noeud * NoeudCourant;
};

#endif // JOUEURSTOCHASTIQUE_H
