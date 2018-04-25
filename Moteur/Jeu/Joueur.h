#ifndef _JOUEUR_H_
#define _JOUEUR_H_
#include <string>
#include <vector>
#include <memory>

#include "Moteur/Piece/allpieces.h"
class jeu;

class Joueur {

    /*
   * Un joueur possède un pseudo, une couleur.
   * On souhaite également qu'il stocke son score, son nombre de PA au début du jeu ainsi que le nombre de PA max qu'il puisse avoir.
   * Un joueur possède également sa liste de pièces que l'on peut nommer réserve. Elle est déterminée une fois les règles établies.
   * Elle doit être copiée dans Joueur à travers la méthode setPieces().
   */
public:
    // Construction du joueur neutre
    Joueur();
    // Construction d'un joueur avec la connaissance de son handicap
    Joueur(const std::string& pseudonyme, Couleur couleur);

    ~Joueur();

    void creationArmee(const std::vector<std::pair<typePiece,int>> & liste_pieces , Carte * carte);
    Piece * appartient(coordonnees c);

    coups actionPossibles();

    void maj_nouveau_tour(){
        m_PACourant=m_PAMax;
        for(std::vector<Piece *>::const_iterator i = m_pieces.begin(); i != m_pieces.end(); i++)
            if(!(*i)->maj_nouveau_tour())
                m_pieces.erase(i);
    }

    //Methode pour les actions du jeu
    void ramasserMinerai();
    void ajouterPiece(Piece *p);

    int getPA() const;

    bool retirePA(int PA);

    void checkPieces(){
        for(std::vector<Piece *>::const_iterator i = m_pieces.begin(); i != m_pieces.end(); i++)
            if((*i)->getPointDeVie()<=0)
                m_pieces.erase(i);
    }

    void setPseudonyme(const std::string& pseudo);
    void setCouleur(const Couleur couleur);
    void setScore(const int score);
    void setNombrePADebut(int deb);
    void setNombrePAMax(int max);

    int getScore() const;
    Couleur getCouleur() const;
    const std::string& getPseudonyme() const;
    std::vector<Piece * > getArmee();
    int getNombrePACourant() const;
    int getNombrePAMax() const;
    Carte * getCarte() const;

    // Méthode d'affichage
    std::string toString() const;
    std::string toStringPieces() const;

private:
    std::string m_pseudonyme;
    Couleur m_couleur;
    int m_score;
    int m_PACourant;
    int m_PAMax;
    std::vector<Piece *> m_pieces;
    Carte * m_carte;
};

/* Méthode : setPieces(const vector< Piece >& pieces)
 * Nous récupérons les pièces.
 * Ces pièces ont été créées sans propriétaire
 * C'est pourquoi nous allons leur en affecter un
 */
/*void setPieces(const std::vector<Piece *>& pieces)
{
    m_pieces = pieces;*/
/*for(std::vector<Piece *>::iterator i = m_pieces.begin(); i != m_pieces.end(); i++)
(*i)->setJoueur(this);*/
//}

#endif
