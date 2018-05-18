#ifndef PLATEAU_H
#define PLATEAU_H

#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

#include "defineclass.h"
#include "Moteur/Piece/allpieces.h"
#include "RegleCarte.h"

class Case{
public:
    Case(const typeCase type);

    Case(const Case & c);

    bool hasPiece();

    Piece * getPiece();

    typeCase getType() const;

    void setPiece(Piece * p);

    void setType(typeCase t);

    std::string toString() const;


private:
    typeCase _type;
    Piece * _piece;
};

int randNombre100();
/*
 *	Génère un CASEMAP en fonction des probabilités en pourcentage passées en paramètre,
 *	par défaut VIDE est renvoyé.
 */
Case randCase(int p_plaine, int p_montagne, int p_mer, int p_marais, int p_recif);

class Plateau
{
public:
    Plateau(int xPlateau , int yPlateau , TypeCarte typePlateau , int repartitionRessources , Couleur cj1 , Couleur cj2 );

    Plateau(const Plateau & p);

    void generationProcedurale();

    void generationPlaine();

    void generationMer();

    void generationStochastique(int &largeur, int &longueur);

    Case & getCase(int i);

    Case & getCase(int x , int y);

    Case & getCase(Coordonnee c);

    int getTaille();

    int getLongueur();

    int getLargeur();

    int getX();

    int getY();

    void finDeTourJoueur();

    void checkPieces();

    void inverseJoueur();

    bool creationPiece(Coordonnee c , typePiece p, Couleur couleur);

    bool isCaseExistante(Coordonnee c) const;

    std::vector<Coordonnee > voisins(Coordonnee source) const;

    coups coupsPossibles();

    bool fin();

    int eval();

    void annulerCoups(int n);

    void annulerCoup();

    coups aPortee(const Coordonnee & c);

    bool ordre(coup c);

    void ordre(coups c);

    bool jouerCoups(coups l);

    bool jouerCoup(coup c);

    bool getJoueurCourant() const;

    void setJoueurCourant(bool joueurCourant);

    coups getnDerniersCoups(int n);

    std::vector<Case> getListe();

    TypeCarte getType();

private:
    int _x;
    int _y;
    TypeCarte _type;
    std::vector<Case> _cases;
    RegleCarte _regles;
    Couleur _couleurj1;
    Couleur _couleurj2;
    bool _joueurCourant;
    std::vector<Piece *> _cimetiere;
    coups _coups;
};

#endif // PLATEAU_H
