#ifndef PONDEUSE_H
#define PONDEUSE_H
#include "transporteur.h"
#include "Moteur/Piece/Neutre/Minerai.h"

class Pondeuse : public Transporteur {

public:
    Pondeuse(Couleur couleur)
        :Transporteur(couleur ,1){
        setTypeDeplacement(new Deplacement_terre);
    }
    Pondeuse(const Pondeuse & p)
        :Transporteur(p.getCouleur() ,1){
        setTypeDeplacement(new Deplacement_terre);
    }
    ~Pondeuse(){}


    virtual Pondeuse * clone() override{
        return new Pondeuse(*this);
    }

    // Méthodes du Jeu
    bool creerPiece(){
        /*std::vector<Piece> tmp = getEnsemblePieces();
    for(std::vector<Piece>::iterator i = tmp.begin(); i != tmp.end(); i++){
        Minerai tampon = dynamic_cast<Minerai &>((*i));
        if(tampon){
           return decharger(tampon);
        }
    }*/
        return false;
    }


    virtual typePiece type() override{
        return typePiece::PONDEUSE;
    }


    // Méthodes d'affichage
    std::string infoPiece() const  {
        std::ostringstream oss;
        oss << "Pondeuse";
        return oss.str();
    }

};

#endif // PONDEUSE_H
