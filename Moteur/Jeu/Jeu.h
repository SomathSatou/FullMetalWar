#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <memory>

#include "Joueur.h"
#include "joueurstochastique.h"
#include "Carte.h"
#include "Moteur/Piece/allpieces.h"

class Jeu {
    /*
 * Un jeu possède une carte et une liste de joueurs.
 * Il mémorise également l'ensemble des paramètres de la partie.
 * C'est le Jeu qui attribue à chaque réserve de joueur les pièces jouables
 * C'est le Jeu qui crée la carte
 */
public :

    /*
     * Constructeur de Jeu :
     * 1- Génère les minerais et le Joueur Neutre
     * 2- Copie  la liste des joueurs fournis et s'occupe de copier la liste des pièces jouables dans les réserves des Joueurs
     * 3- Génère la liste des marées
     */

    Jeu(std::vector<Joueur *> joueurs, std::vector<std::pair<typePiece, int> > &liste_pieces, int longueur, int largeur ,  int nombreToursMax = 25, int repartitionRessource = 3 );
    Jeu(std::vector<Joueur *> joueurs, std::vector<std::pair<typePiece,int>> &pieces, TypeCarte type , bool minerais, int &longueur, int &largeur, int nombreToursMax = 25, int repartitionRessource = 3);
    bool ordre(const coordonnees & source, const coordonnees & objectif );

    ~Jeu();

    // Méthodes d'accès aux données
    Carte& getCarte();
    //    const std::vector<Joueur>& getListeJoueurs() const { return m_joueurs; }
    //    const Joueur& getJoueur(int index) const { return m_joueurs[index]; }
    int getJoueurCourrant() const;
    int getTourCourrant() const;

    std::vector<Joueur *> getListeJoueurs();
    Joueur * getJoueur(int i);

    // Méthodes d'affichage
    std::string toString() const;

    void checkJoueurs();

    void listeOrdre(std::vector<Action> actions){
        for(const auto & a : actions){
            int xs = a.src%m_carte.getLongueur();
            int ys = (a.src-xs) / m_carte.getLongueur();
            int xd = a.dest%m_carte.getLongueur();
            int yd = (a.dest-xd) / m_carte.getLongueur();
            ordre(coordonnees(xs,ys),coordonnees(xd,yd));
        }
    }

    void finDeTourJoueur();

private :
    std::vector<Joueur *> m_joueurs;
    int m_tourMax;
    Carte m_carte;
    int m_joueurCourant;
    int m_tourCourrant;
};
