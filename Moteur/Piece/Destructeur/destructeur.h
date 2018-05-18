#ifndef DESTRUCTEUR_H
#define DESTRUCTEUR_H
#include "Moteur/Piece/piece.h"

class Destructeur : public Piece
{

public:
    Destructeur(Couleur couleur);

    ~Destructeur();

    bool pretATirer();
    void tire();
    void rechargement();

    int getMunition() const;

    bool maj() override;

    virtual int distance();

//    bool attaque(const coordonnees & ennemi) override{
//        if(m_munition>0){
//            if(getJoueur()->getCarte()->getCase(ennemi.first,ennemi.second).hasPiece()){
//                Piece * e = getJoueur()->getCarte()->getCase(ennemi.first,ennemi.second).getPiece();

//                if(e->getCouleur()!=getCouleur()){
//                    for(auto & adv : _attaque->aPortee(getJoueur()->getCarte(),getCoordonnees(),getCouleur())){
//                        if(adv.destination ==ennemi){
//                            m_munition--;
//                            e->prendreDegats(3);
//                            return true;
//                        }
//                    }
//                }

//            }

//        }
//        return false;
//    }

private:
    int _munition;

};

#endif // DESTRUCTEUR_H
