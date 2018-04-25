#include "CaseMap.h"

CaseMap::CaseMap(): m_typeCase(TYPECASE::PLAINE), m_piece(nullptr){}

CaseMap::CaseMap(const TYPECASE type): m_typeCase(type), m_piece(nullptr){}

CaseMap::CaseMap(const TYPECASE type, Piece *piece): m_typeCase(type), m_piece(piece){}

bool CaseMap::hasPiece() const { return m_piece != nullptr; }

Piece * CaseMap::getPiece() const{ return m_piece; }

TYPECASE CaseMap::getType() const{ return m_typeCase; }

void CaseMap::detruitPiece(){ m_piece = nullptr; }

void CaseMap::nouvellePiece(Piece *piece){
    m_piece = piece; }

std::__cxx11::string CaseMap::toString() const{
    std::ostringstream oss;
    std::string type;
    oss << "Case de type ";
    switch (m_typeCase) {
    case TYPECASE::MER:       type = "MER";       break;
    case TYPECASE::PLAINE:    type = "PLAINE";    break;
    case TYPECASE::MONTAGNE:  type = "MONTAGNE";  break;
    case TYPECASE::RECIF:     type = "RECIF";     break;
    case TYPECASE::MARAIS:    type = "MARAIS";    break;
    default:        type = "VIDE";   break;
    }
    oss << type;
    /* if(m_piece != 0){
        oss << " avec une pièce " << m_piece->toString();
    }*/
    return oss.str();
}
