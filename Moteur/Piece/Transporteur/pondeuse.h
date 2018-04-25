#ifndef PONDEUSE_H
#define PONDEUSE_H
#include "transporteur.h"
#include "Moteur/Piece/Neutre/Minerai.h"

class Pondeuse : public Transporteur {

    /*
     * Classe Pondeuse Météorologique
     * La pondeuse a la capacité spéciale de pouvoir créer des pièces
     */
public:
    Pondeuse(coordonnees coor, Couleur color, Joueur * proprietaire);
    ~Pondeuse();

    // Méthodes du Jeu
   bool creerPiece();

    // Méthodes d'affichage
    std::string infoPiece() const ;

};

#endif // PONDEUSE_H
