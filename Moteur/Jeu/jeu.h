#ifndef JEU_H
#define JEU_H

#include <vector>

#include "defineclass.h"
#include "plateau.h"
#include "joueur.h"
#include "arbrestochastique.h"

class Jeu
{
public:
    Jeu(Joueur * joueur1, Joueur * joueur2 ,
        std::vector<std::pair<typePiece,int>> & listePieces,
        int xPlateau , int yPlateau , TypeCarte typePlateau , int repartitionRessources );

    Plateau & getPlateau();

    int getJoueurCourant() const;

    Joueur * getJoueur1();

    Joueur * getJoueur2();

    Joueur * getJoueur(Couleur c);

    Joueur * getJoueurCourantPtr();

    int getTour() const;

    bool ordre(coup c);

    void ordre(coups c);

    void finDeTourJoueur();

    void init();


    Arbre getStochastique() const;
    void setStochastique(const Arbre &stochastique);

private:
    Joueur * _joueur1;
    Joueur * _joueur2;
    Plateau _plateau;
    int _nbTours;
    int _tour;
    bool _joueurCourant; //false : joueur2 ; true : joueur1
    Arbre _stochastique;

};

#endif // JEU_H
