#ifndef CASEMAP_H
#define CASEMAP_H
#include <sstream>
#include <string>

enum  class TYPECASE { PLAINE, MONTAGNE, MER, MARAIS, RECIF, VIDE };

class Piece;

class CaseMap
{
public:
    CaseMap();
    CaseMap(const TYPECASE type);
    CaseMap(const TYPECASE type, Piece * piece);
//    CaseMap(const CaseMap & C):m_typeCase(C.getType()),m_piece(C.getPiece()->clone()){}

    bool hasPiece() const;

    // Méthodes pour accéder au type
    Piece *  getPiece() const;
    TYPECASE getType()  const;

    // Méthodes pour mettre à jour la pièce
    void detruitPiece();
    void nouvellePiece(Piece * piece);

    // Méthodes d'affichage
    std::string toString() const;

private:
    TYPECASE m_typeCase;
    Piece * m_piece;
};

#endif // CASEMAP_H
