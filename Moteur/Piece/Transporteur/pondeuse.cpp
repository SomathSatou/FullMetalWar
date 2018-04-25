#include "pondeuse.h"

Pondeuse::Pondeuse(coordonnees coor, Couleur color, Joueur *proprietaire)
    :Transporteur(coor , color, proprietaire,1){
    setTypeDeplacement(new Deplacement_terre);
}

Pondeuse::~Pondeuse(){}

bool Pondeuse::creerPiece(){
    /*std::vector<Piece> tmp = getEnsemblePieces();
    for(std::vector<Piece>::iterator i = tmp.begin(); i != tmp.end(); i++){
        Minerai tampon = dynamic_cast<Minerai &>((*i));
        if(tampon){
           return decharger(tampon);
        }
    }*/
    return false;
}

std::string Pondeuse::infoPiece() const {
    std::ostringstream oss;
    oss << "Pondeuse";
    return oss.str();
}
