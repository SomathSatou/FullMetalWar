#include "destructeur.h"

#include "Moteur/Jeu/Joueur.h"

Destructeur::Destructeur(coordonnees coor, Couleur color, int pointDeVieMax, Joueur *proprietaire)
    :Piece(coor, color , pointDeVieMax, proprietaire),
      m_munition(1){
    setTypeAttaque(new Portee3);
}

Destructeur::~Destructeur(){}

void Destructeur::Reload() {m_munition = 1;}

int Destructeur::getCurrentMunition() const {return m_munition;}

int Destructeur::getMunition()  const {return 1;}

bool Destructeur::attaque(const coordonnees &ennemi){
    if(m_munition>0){
        if(getJoueur()->getCarte()->getCase(ennemi.first,ennemi.second).hasPiece()){
            Piece * e = getJoueur()->getCarte()->getCase(ennemi.first,ennemi.second).getPiece();

            if(e->getCouleur()!=getCouleur()){
                for(auto & adv : _attaque->aPortee(getJoueur()->getCarte(),getCoordonnees(),getCouleur())){
                    if(adv.destination ==ennemi){
                        m_munition--;
                        e->prendreDegats(3);
                        return true;
                    }
                }
            }

        }

    }
    return false;
}


