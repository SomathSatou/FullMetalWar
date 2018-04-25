#include <iostream>
#include "Joueur.h"
#include "Piece.h"
#include "Jeu.h"

int main(int argc, char **argv) {




  // CREATION DES JOUEURS
    std::vector<Joueur> mesJoueurs;

    Joueur joueurUn("Nhitro", ROUGE);
    joueurUn.setNombrePADebut(10);
    joueurUn.setNombrePAMax(20);

    Joueur joueurDeux("Vin Diesel", NOIR);
    joueurDeux.setNombrePADebut(15);
    joueurDeux.setNombrePAMax(45);

    mesJoueurs.push_back(joueurUn);
    mesJoueurs.push_back(joueurDeux);

    // CREATION DES PIECES
    std::vector<QuantPiece> mesPieces;

    QuantPiece tank(5,CHAR);
    QuantPiece barge(2, BARGE);

    mesPieces.push_back(tank);
    mesPieces.push_back(barge);
    //--------------------------------------
    // CREATION JEU
    Jeu monJeu(mesJoueurs, mesPieces, 25, 10, 3, 1, 4);
    std::cout << "Pointeur listeJoueurs :" << (&mesJoueurs) << std::endl;
    std::cout << "Pointeur listePieces :" << (&mesPieces) << std::endl;
    std::cout << monJeu.toString() << std::endl;

    return 0;
}
