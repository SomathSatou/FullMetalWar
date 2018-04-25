#include "transporteur.h"

Transporteur::Transporteur(coordonnees coor, Couleur color, Joueur *proprietaire, int espaceMax)
    :Piece(coor , color , 4 ,proprietaire),
      m_espaceMax(espaceMax){
    setTypeAttaque(new PorteeNulle);
}

Transporteur::~Transporteur(){}

int Transporteur::getEspaceStockage() const { return m_espaceMax; }

int Transporteur::getEspaceCourant() const {     int ret = 0;
                                                 for(auto p : m_ensemblePiecesTransportees){
                                                     ret += p->getPoids();
                                                     }
                                                 return ret;
                                                 }


const std::vector<Piece *> &Transporteur::getEnsemblePieces() const { return m_ensemblePiecesTransportees; }

void Transporteur::setEspaceStockage(const int espace) {m_espaceMax = espace; }

void Transporteur::setEnsemblePieces(const std::vector<Piece *> en) { m_ensemblePiecesTransportees = en; }
