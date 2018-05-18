#pragma once

#include <fstream>
#include <string>
#include <utility>
#include "Moteur/Jeu/plateau.h"
#include "Moteur/Jeu/cartestoch.h"



std::vector<Action> randomAction(Plateau & c);

class Noeud {
    public:
        Noeud(const Plateau & c); // racine
        Noeud(std::vector<Action> Actions,Noeud* pere); // noeud

        // methode stochastique
        int roll_out();

        void update(int val);

        std::vector<Action> jouer();

        //acceseur
        int getNbrR();
        int getNbrV();
        CarteStoch getCarte() const;
        std::vector<Noeud *> getFils();

        void setNbrV(int v);
        void setNbrR(int r);
        void setCarte(Plateau c);
        void addFils(Noeud * n);

        // methode pour la sauvegarde et la lecture du fichier
        void save();
        void load();
        void AjouterFils(std::ifstream &f);

        void toLatek();
        std::vector<Action> trad(std::ifstream &f);

        int getProf() const;
        void setProf(int prof);

        std::vector<Action> getActions() const;
        void setActions(const std::vector<Action> &Actions);

        void saveFils(std::ofstream &f);
        Noeud *getPere() const;
        void setPere(Noeud *pere);

        bool estFils(std::vector<Action> act);
private:
        CarteStoch _carte;
        int _nbr_recherche;
        int _nbr_valeur;
        std::vector<Noeud *> _fils;
        std::vector<Action> _Actions;
        Noeud * _pere;
        int _prof;
};

struct Arbre {
    Noeud* Racine;
    Noeud* Courant;
};
