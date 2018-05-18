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


class CarteStoch {
    public :
        CarteStoch(Plateau const &c);
        CarteStoch(CarteStoch const &c);
        void faire(Action a);

        std::set<int> portee(int src);
        bool deplacement(int src,int dest);
        bool deplacementPossible(int src,int dest);
        bool attaque(int src,int dest);
        bool attaquePossible(int src,int dest);

        bool fini();
        int gagnant();
        void finTour();
        void Afficher();


        //acesseur
        std::vector<CaseStoch> getPlateau() const;
        int getLongueur() const;
        int getLargeur() const;
        int getTaille() const;
        CaseStoch getCase(int x) const;

        //setters
        void setPlateau(Plateau c);
        void setLongueur(int longueur);
        void setLargeur(int largeur);
        void setTaille(int taille);
        void setPiece(Unite P,int dest);
        void setPieceType(int type,int cible);
        void setMun(int val,int src);
        void degat(int dest);

        int getType() const;
        void setType(int type);

private :
        std::vector<CaseStoch> _plateau;
        int _longueur;
        int _largeur;
        int _taille;
        int _type; // 1 plaines, 2 mers, 3 stochastique, autre random
};

#endif // CARETESTOCH

