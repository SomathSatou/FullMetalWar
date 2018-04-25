#ifndef TRANSPORTEUR_H
#define TRANSPORTEUR_H
#include "Moteur/Piece/Piece.h"
#include <vector>

class Transporteur : public Piece {

    /*
     * Classe abstraite Transporteur
     * Un transporteur est caractérisé par :
     *      - un espace de stockage maximum
     *      - l'espace de stockage courant
     *      - la liste des pièces stockées
     */

public:
    // Constructeur avec les informations nécessaires à la création d'un Transporteur
    Transporteur(coordonnees coor, Couleur color,Joueur * proprietaire  ,int espaceMax);
    ~Transporteur();

    // Méthodes d'accès aux données
    int getEspaceStockage() const;
    int getEspaceCourant() const;
    const std::vector<Piece *>& getEnsemblePieces() const;

    // Méthodes de mise à jour des données
    void setEspaceStockage(const int espace);
    void setEspaceCourant(const int espace);
    void setEnsemblePieces(const std::vector<Piece *> en);


    /*
    bool Transporteur::charger(Piece * p){
        if( (m_espaceCourant+p->getEncombrement()) > m_espaceStockage)
            return false;
        else {
            m_espaceCourant+=p->getEncombrement();
            m_ensemblePiecesTransportees.push_back(p);
            return true;
        }
    }
    */

    //bool Transporteur::decharger(Piece * p){
        /*for(std::vector<Piece>::iterator i = m_ensemblePiecesTransportees.begin(); i != m_ensemblePiecesTransportees.end(); i++){
            if(p != (*i))
                nouveau.push_back((*i));
        }
        if(nouveau.size() != m_ensemblePiecesTransportees.size()){
            setEnsemblePieces(nouveau);
            return true;
        } else {
            return false;
        }*/
    //    return false;
    //}

private:
    int m_espaceMax;
    std::vector<Piece *> m_ensemblePiecesTransportees;

};

#endif // TRANSPORTEUR_H
