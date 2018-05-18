#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>

#include "defineclass.h"
#include "plateau.h"

class Joueur
{
public:
    Joueur(std::string nom , Couleur couleur, bool joueur);

    std::string getPseudonyme() const;

    Couleur getCouleur() const;

    void setPseudonyme(std::string p);

    void setCouleur(Couleur c);

    int getNombrePACourant() const;

    int getNombrePAMax() const;

    void setNombrePADebut(int p);
    void setNombrePAMax(int p);

    bool utilisationPAPossible();

    bool utilisationPA();

    void majTour();

    virtual coups jouer(Plateau p);

    bool getJoueur() const;

private:
    std::string _nom;
    Couleur _couleur;
    int _pointAction;
    int _pointActionMax;
    bool _joueur;
};

#endif // JOUEUR_H
