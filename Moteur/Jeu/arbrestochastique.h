#pragma once

#include <fstream>
#include <string>
#include <utility>
#include "Moteur/Jeu/Carte.h"

enum class typeAction {DEPLACER, ATTAQUER};

struct Action{
    typeAction faire;
    int src;
    int dest;
    };

std::vector<Action> randomAction(Carte & c);

class Noeud {
    public:
        Noeud(const Carte & c); // racine
        Noeud(std::vector<Action> Actions,Noeud* pere); // noeud

        // methode stochastique
        int roll_out();

        void update(int val,Noeud *  n);

        std::vector<Action> jouer();

        //acceseur
        int getNbrR();
        int getNbrV();
        Carte getCarte();

        void setNbrV(int v);
        void setNbrR(int r);
        void setCarte(Carte c);

        // methode pour la sauvegarde et la lecture du fichier
        void save();
        void load();
        void AjouterFils(std::ifstream &f);

        void toLatek();
        std::vector<Action> trad(std::ifstream &f);

    private:
        Carte _carte;
        int _nbr_recherche;
        int _nbr_valeur;
        std::vector<Noeud *> _fils;
        std::vector<Action> _Actions;
        Noeud * _pere;
        int _prof;
};
