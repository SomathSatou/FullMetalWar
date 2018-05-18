#ifndef TRANSPORTEUR_H
#define TRANSPORTEUR_H
#include "Moteur/Piece/piece.h"
#include <vector>

class Transporteur : public Piece {

public:
    Transporteur(Couleur couleur,int espaceMax)
        :Piece(couleur),
          m_espaceMax(espaceMax){
    }
    ~Transporteur(){}
/*
    // Méthodes d'accès aux données
    int getEspaceStockage() const { return m_espaceMax; }
    int getEspaceCourant() const {
        int ret = 0;
        for(auto p : m_ensemblePiecesTransportees){
            ret += p->getPoids();
        }
        return ret;
    }
    const std::vector<Piece *>& getEnsemblePieces() const { return m_ensemblePiecesTransportees; }

    // Méthodes de mise à jour des données
    void setEspaceStockage(const int espace) {m_espaceMax = espace; }
    void setEspaceCourant(const int espace);
    void setEnsemblePieces(const std::vector<Piece *> en) { m_ensemblePiecesTransportees = en; }

*/
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
