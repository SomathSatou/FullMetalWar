#pragma once
#define UNUSED(expr) do { (void)(expr); } while (0)
#include "Moteur/Jeu/Carte.h"

using coordonnees = std::pair<int,int>;

class IDeplacement{
public:
    virtual std::vector<coordonnees> voisin(Carte * carte, coordonnees source)=0;
    virtual bool accessible(Carte * carte , coordonnees c) = 0;
    virtual ~IDeplacement();
};


class Deplacement_terre : public IDeplacement{
public:
    std::vector<coordonnees> voisin(Carte * carte, coordonnees source) override;

    bool accessible(Carte * carte, coordonnees c) override;
};

class Deplacement_terre_sans_mont : public IDeplacement{
public:
    std::vector<coordonnees> voisin(Carte * carte, coordonnees source) override;

    bool accessible(Carte * carte, coordonnees c) override;
};

class Deplacement_eau : public IDeplacement{
public:
    std::vector<coordonnees> voisin(Carte * carte, coordonnees source) override;

    bool accessible(Carte * carte, coordonnees c) override;
};


class Deplacement_nul : public IDeplacement{

    std::vector<coordonnees> voisin(Carte * carte, coordonnees source) override;
    bool accessible(Carte * carte, coordonnees c) override;

};

/*
int Jeu::cout_deplacement(int x_depart, int y_depart, int x_dest, int y_dest, std::vector<coordonnees> voisin ){
    std::vector<triplet> path(pathfinding_dijkstra_manhattan(x_depart, y_depart, x_dest, y_dest,voisin));
    triplet t;
    t.provenance=std::pair<int,int>( x_dest, y_dest);
    t.cout=std::pair<int,int>(0,0);
    t.sommet=std::pair<int,int>( x_dest, y_dest);
    auto result (std::find(path.begin(), path.end(), t));
    if(result == path.end())
    {
        std::cout << "\n\tcase inaccessible";
        return -1;
    }
    else
        return (*result).cout.first;
}

bool Jeu::deplacement(int x_depart, int y_depart, int x_dest, int y_dest) {

    std::cout << "\nx = " << x_depart << " y = " << y_depart;
    const Piece* p = m_carte.getCase(x_depart,y_depart).getPiece();

    if(p->getJoueur()->getCouleur() == m_joueurs[m_joueurCourrant].getCouleur()){
        int coutPA(0);
        switch (p->getClasse()) {
        case C_CHAR:
            coutPA = cout_deplacement(x_depart, y_depart, x_dest, y_dest, voisins_terre);
            std::cerr << "\n\tcout deplacement = " << coutPA << "\n\n";
            if(coutPA !=-1 && m_joueurs[m_joueurCourrant].deplacementPiece(coutPA)) {
                m_carte.getCase(x_depart,y_depart).detruitPiece();
                m_carte.getCase(x_dest,y_dest).nouvellePiece(p);
            } // END IF
            break;
        default:
            break;
        }// END SWITCH
    } // END IF
    return true;

    //
  if(!m_carte.getCase(x_dest,y_dest).hasPiece()){
      int x = (x_dest - x_depart);
      int y = (y_dest - y_depart);
      x = sqrt(x*x);
      y = sqrt(y*y);
      int coutPA = x+y;
      if(m_joueurs[m_joueurCourrant].deplacementPiece(coutPA)) {
          m_carte.getCase(x_depart,y_depart).detruitPiece();
          m_carte.getCase(x_dest,y_dest).nouvellePiece(p);
      } // END IF
  } // END IF
  else { //a changer on ne peut pas se deplacer sur un minerai
      if(dynamic_cast<const Minerai*>(m_carte.getCase(x_dest,y_dest).getPiece())){
          int x = (x_dest - x_depart);
          int y = (y_dest - y_depart);
          x = sqrt(x*x);
          y = sqrt(y*y);
          int coutPA = x+y;
          if(m_joueurs[m_joueurCourrant].deplacementPiece(coutPA)) {
              m_carte.getCase(x_depart,y_depart).detruitPiece();
              m_carte.getCase(x_dest,y_dest).nouvellePiece(p);
              m_joueurs[m_joueurCourrant].ramasserMinerai();
          } // END IF
      } // END IF
  } // END ELSE

} // END
*/
