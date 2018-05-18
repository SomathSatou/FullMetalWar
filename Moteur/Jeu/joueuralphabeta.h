#ifndef JOUEURALPHABETA_H
#define JOUEURALPHABETA_H

#include "defineclass.h"
#include "plateau.h"
#include "joueur.h"

#define PA_MAX 5
#define PROFONDEUR 2

class JoueurAlphaBeta : public Joueur
{
public:
    JoueurAlphaBeta(std::string nom , Couleur couleur,bool joueur);

    virtual coups jouer(Plateau p)override;

    coups alpha_beta(Plateau & p);

    int alpha_beta_E(Plateau & p , int alpha , int beta , int profondeur , int PA);

    int alpha_beta_U(Plateau & p , int alpha , int beta , int profondeur , int PA);

    int maximum(int a , int b);

    int minimum(int a , int b);

    coups alpha_beta_coup_par_coup(Plateau & p);

    int alpha_beta_E_coup_par_coup(Plateau & p , int alpha , int beta , int profondeur , int PA);

    int alpha_beta_U_coup_par_coup(Plateau & p , int alpha , int beta , int profondeur , int PA);

    void coupsAJouer(Plateau & p, std::vector<coups> & liste , int PA);

private:
    int _profondeur;
    coups _listeEnCours;
};

#endif // JOUEURALPHABETA_H
