#ifndef JOUEURSTOCHASTIQUE_H
#define JOUEURSTOCHASTIQUE_H

#include "arbrestochastique.h"
#include "Moteur/Jeu/joueur.h"

class joueurStochastique : public Joueur
{
public:
    joueurStochastique(const std::string& pseudonyme, Couleur couleur,bool);

    coups jouer(Plateau p) override;

    Arbre *getArbre();

    void setArbre(Arbre *arbre);

private:
    Arbre * _arbre;
};

#endif // JOUEURSTOCHASTIQUE_H
