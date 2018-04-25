#ifndef CARETESTOCH
#define CARETESTOCH
#include "vector"

struct Unite{
    int type;
    int pv;
    int mun;
    int proprio;
};

struct Case{
    int type;
    Unite piece;
};

class Carte;

class CarteStoch {
    public :
        void deplacer(int dest);
        void attaquer(int dest);

        //acesseur
        std::vector<Case> getPlateau();
        int getLongueur() const;
        int getLargeur() const;
        int getTaille() const;

        //setters
        void setPlateau(Carte c);
        void setLongueur(int longueur);
        void setLargeur(int largeur);
        void setTaille(int taille);

private :
        std::vector<Case> _plateau;
        int _longueur;
        int _largeur;
        int _taille;
};

#endif // CARETESTOCH

