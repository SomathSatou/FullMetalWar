#ifndef PIECE_H
#define PIECE_H
#define UNUSED(expr) do { (void)(expr); } while (0)
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "defineclass.h"

enum class typePiece { CHAR , GROS_TAS , VEDETTE , MINERAI , PONTON , BARGE , CRABE , PONDEUSE , BASE };

using coordonnees = std::pair<int,int>;

struct coup{
    coordonnees source;
    coordonnees destination;
    int cout;
};

bool operator==(const coup &a, const coup &b);


bool operator<(coup const & a , coup const & b);

using coups = std::vector<coup>;



bool operator==(std::pair<int,int> const & a , std::pair<int,int> const & b);

typedef struct{
    std::pair<int,int> provenance;
    std::pair<int,int> cout;
    std::pair<int,int> sommet;
}triplet;

bool operator<(triplet const & a , triplet const & b);
bool operator==(triplet const & a , triplet const & b);

#include"Moteur/Piece/Comportement/allcomportements.h"

class IAttaque;

class Joueur;

class Piece {
    /*
     * Classe Piece
     *
     */

public:
    // Construction d'une pièce avec tous les paramètres nécessaires
    Piece(coordonnees coor, Couleur color, int pointDeVieMax, Joueur * proprietaire);
    // Constructeur par recopie
    Piece(const Piece& p);
    virtual ~Piece();

    // Méthodes d'accès aux données de la pièce
    int getPositionX() const;
    int getPositionY() const;
    coordonnees getCoordonnees() const;
    int getPointDeVie() const;
    int getPointDeVieMax() const;
    Couleur getCouleur() const;
    virtual int getPoids() const;
    std::vector<triplet> cases_a_portee(int portee);

    // Méthodes de mise à jour des données
    void setCoordonnee(const coordonnees & c);
    void setPointDeVie(const int pointDeVie);

    // Méthodes d'affichage
    std::string toString() const;
    // Méthode abstraite appelée par toString(), pour permettre d'afficher des informations différentes selon la pièce qui est affichée
    virtual std::string infoPiece() const =0;

    IDeplacement * _deplacement;
    IAttaque * _attaque;

    void setTypeDeplacement(IDeplacement * typeDepla);
    void setTypeAttaque(IAttaque * typeAtk);
    void setJoueur(Joueur *proprietaire);

    Joueur * getJoueur() const;

    int deplacement(const coordonnees & destination) const;

    virtual bool attaque(const coordonnees & ennemi);

    coups actionsPossibles();

    bool prendreDegats(int d);


    std::vector<triplet> pathfinding_dijkstra_manhattan(const coordonnees & source , const coordonnees & destination) const;
    int manhattan(const coordonnees & source , const coordonnees & destination) const;

    coups voisins();


private:
    coordonnees m_coordonnee;
    Couleur m_color;
    int m_pointDeVie;
    int m_pointDeVieMax;
    Joueur * m_proprietaire;

};

#endif // PIECE_H
