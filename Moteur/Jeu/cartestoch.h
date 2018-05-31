#ifndef CARETESTOCH
#define CARETESTOCH
#include "vector"
#include "Moteur/Jeu/plateau.h"
#include <set>

struct Unite{
    int type;
    int pv;
    int mun;
    int proprio;
};

struct CaseStoch{
    int type;  // 1 plaines , 2 mers , 3 montagnes , 4 marais, 5recifs
    Unite piece;
};

/*
 * Ceci est un modelisation simplifier du plateau visant a alléger les manipulationdans l'arbre stochastique
 */
class CarteStoch {
    public :
        //constructeur a partir d'un plateau du moteur
        CarteStoch(Plateau const &c);

        CarteStoch(CarteStoch const &c);

        //methode qui réalise les action sur la carteStoch
        void faire(Action a);

        //renvoie ensemble des indices des cases a portee
        std::set<int> portee(int src);

        // methode de déplacement effective
        bool deplacement(int src,int dest);
        // methode de test pour le déplacement
        bool deplacementPossible(int src,int dest);

        //methode d'attaque efffective
        bool attaque(int src,int dest);
        //methode de test pour les déplacement
        bool attaquePossible(int src,int dest);

        // renoie si la carte est finie ou non
        bool fini();

        //renvoie 1 pour j1 gagne et -1 pour j2 gagne, 0 en cas d'égalité
        int gagnant();

        //reinitialise les valeurs
        void finTour();

        //affiche la carte
        void Afficher();


        //acesseur
        std::vector<CaseStoch> getPlateau() const;
        int getLongueur() const;
        int getLargeur() const;
        int getTaille() const;
        CaseStoch getCase(int x) const;
        int getType() const;

        //setters
        void setPlateau(Plateau c);
        void setLongueur(int longueur);
        void setLargeur(int largeur);
        void setTaille(int taille);
        void setPiece(Unite P,int dest);
        void setPieceType(int type,int cible);
        void setMun(int val,int src);
        void degat(int dest);
        void setType(int type);

private :
        std::vector<CaseStoch> _plateau;
        int _longueur;
        int _largeur;
        int _taille;
        int _type; // 1 plaines, 2 mers, 3 stochastique, autre random
};

#endif // CARETESTOCH

