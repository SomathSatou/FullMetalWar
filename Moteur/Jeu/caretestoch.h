#ifndef CARETESTOCH
#define CARETESTOCH
#include "vector"
#include "Moteur/Jeu/Carte.h"

struct Unite{
    int type;
    int pv;
    int mun;
    int proprio;
};

struct Case{
    int type;  // 1 plaines , 2 mers , 3 montagnes , 4 marais, 5recifs
    Unite piece;
};


class CarteStoch {
    public :
        CarteStoch(Carte const &c){setPlateau(c);}
        CarteStoch(CarteStoch const &c):_longueur(c.getLongueur()),
                                   _largeur(c.getLargeur()),
                                   _taille(c.getTaille()),
                                   _type(c.getType()){
            for(auto Case : c.getPlateau()){
                _plateau.push_back(Case);
            }
        }

        bool deplacement(int src,int dest);
        void attaque(int src,int dest);
        bool fini(){return false;}
        void finTour(){for(int i = 0;i<_taille;i++){
                      _plateau[i].piece.mun = 1;}
                      }
        void Afficher();

        //acesseur
        std::vector<Case> getPlateau() const;
        int getLongueur() const;
        int getLargeur() const;
        int getTaille() const;
        Case getCase(int x) const{return _plateau[x];}

        //setters
        void setPlateau(Carte c);
        void setLongueur(int longueur);
        void setLargeur(int largeur);
        void setTaille(int taille);
        void setPiece(Unite P,int dest){_plateau[dest].piece=P;}
        void setPieceType(int type,int cible){_plateau[cible].piece.type = type;}

        int getType() const;
        void setType(int type);

private :
        std::vector<Case> _plateau;
        int _longueur;
        int _largeur;
        int _taille;
        int _type; // 1 plaines, 2 mers, 3 stochastique, autre random
};

#endif // CARETESTOCH

