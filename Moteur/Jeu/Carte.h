#ifndef _CARTE_H_
#define _CARTE_H_
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "RegleCarte.h"
#include "defineclass.h"




int randNombre100(); // permet de générer un nombre entre 1 et 100

// Génère une case aléatoire en fonction des probabilités entrées en paramètre
CaseMap randCaseMap(int plaine, int montagne, int mer, int marais, int recif);

class Carte {
    /*
   * La Carte est instanciée par le Jeu.
   * Elle stocke l'ensemble des cases et s'occupe de leur destruction.
   *
   */
public:
    Carte(int longueur = 37, int largeur = 23);     // Construction d'une carte en appelant la generationProcedurale()
    Carte(int &longueur, int &largeur,TypeCarte type);

    ~Carte();

    // Méthodes pour accéder aux cases
    CaseMap& getCase(int i);
    CaseMap& getCase(int x, int y);       // L'accès à la case permet également la modification de celle ci
//    const CaseMap& getCase(int i) const;
//    const CaseMap& getCase(int x, int y) const;
//    const CaseMap& getCase(const std::pair<int,int> & c) const;
    TypeCarte getType()const {return _type;}


    std::vector<std::pair<int,int>> voisins(std::pair<int,int> source) const;

    int fini(){ return 0; }

    bool isCaseExistante(int x, int y) const;
    bool isCaseExistante(std::pair<int,int> c) const;
    bool isCaseTerreEtMontagne(int x, int y) const;
    bool isCaseTerreSansMontagne(int x, int y) const;
    bool isCaseEau(int x, int y) const;

    int getLongueur() const;
    int getLargeur() const;
    int getTaille() const;

    // Méthodes d'affichage
    std::string toString() const;

    std::vector<CaseMap> getListe() const;

private:
    void generationProcedurale();// Génère la carte de manière procédurale
    void generationPlaine();
    void generationMer();
    void generationStochastique(int&,int&);

    int m_longueur;
    int m_largeur;
    int m_taille;
    std::vector<CaseMap> m_cases;
    RegleCarte m_regles;
    TypeCarte _type;

};

#endif // _CARTE_H_
