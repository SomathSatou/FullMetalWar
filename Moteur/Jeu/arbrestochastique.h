#pragma once

#include <fstream>
#include <string>
#include <utility>
#include "Moteur/Jeu/plateau.h"
#include "Moteur/Jeu/cartestoch.h"



std::vector<Action> randomAction(Plateau & c);

class Noeud {
    public:
        // constructeur
        Noeud(const Plateau & c); // constuit de la racine racine
        Noeud(std::vector<Action> Actions,Noeud* pere); // constructeur des noeuds

        // methode stochastique
        int roll_out(); // permet de générer la fin de la partie de façons aléatoire et renvoi la valeur a mettre a jour

        void update(int val); // mets a jour des façons récusif les noeuds de l'abre

        std::vector<Action> jouer();

        //acceseur
        int getNbrR();
        int getNbrV();
        CarteStoch getCarte() const;
        std::vector<Noeud *> getFils();
        int getProf() const;
        std::vector<Action> getActions() const;
        Noeud *getPere() const;

        //setters
        void setNbrV(int v);
        void setNbrR(int r);
        void setCarte(Plateau c);
        void addFils(Noeud * n);        
        void setProf(int prof);
        void setActions(const std::vector<Action> &Actions);
        void setPere(Noeud *pere);

        // methode pour la sauvegarde et la lecture du fichier
        void save();
        void load();
        void AjouterFils(std::ifstream &f);

        //me pour faire apparaitre l'abre grave a latk ( à coder )
        void toLatek();

        //traduit un ligne du fichier en vector d'action
        std::vector<Action> trad(std::ifstream &f);

        //permet de crée les fils d'un noeud a partir du fichier de sauvegarde
        void saveFils(std::ofstream &f);

        //verifie si il existe déjà un fils avec le même vector action que act
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
