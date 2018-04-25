#include "caretestoch.h"
#include "Carte.h"
#include "CaseMap.h"
#include "Moteur/Piece/allpieces.h"

std::vector<Case> CarteStoch::getPlateau(){return _plateau;}

void CarteStoch::setPlateau(Carte c){
    int i=0;
       for(auto oldCase : c.getListe()){
           std::cout<<" tour "<<i++<<std::endl<<std::endl;
           _longueur = c.getLongueur();
           _largeur = c.getLargeur();
           _taille = c.getTaille();
           switch(c.getType()){
               case TypeCarte::PLAINES :
                   _type = 1;
                   break;
               case TypeCarte::MERS:
                   _type = 2;
                   break;
               case TypeCarte::STOCHASTIQUE:
                   _type = 3;
                   break;
               default:
                   _type = 4;
                   break;
           }

           Case newCase;
           switch(oldCase.getType()){
               case TYPECASE::MONTAGNE:
                   newCase.type = 3;
                   break;
               case TYPECASE::PLAINE:
                   newCase.type = 1;
                   break;
               case TYPECASE::MER:
                   newCase.type = 2;
                   break;
               case TYPECASE::MARAIS:
                   newCase.type =4;
                   break;
               case TYPECASE::RECIF:
                   newCase.type = 5;
                   break;
               default:
                   std::cerr<<"mauvais type de case stocha"<<std::endl;
                   break;
           }
           if (dynamic_cast<Char *>(oldCase.getPiece())){
               std::cout<<"un char"<<std::endl;
                 Unite temp;
                 temp.mun = 1;
                 temp.proprio = 0; // a modifier
                 temp.pv = 5;
                 temp.type = 1; // 1 pour char
                 }
           //rajouter des dynamic cast pour avoir plus de piece
           _plateau.push_back(newCase);
      }
}

void CarteStoch::deplacement(int src,int dest){}

void CarteStoch::attaque(int src, int dest){}

int CarteStoch::getLongueur() const{return _longueur;}

int CarteStoch::getLargeur() const{return _largeur;}

int CarteStoch::getTaille() const{return _taille;}

void CarteStoch::setLongueur(int longueur){_longueur=longueur;}

void CarteStoch::setLargeur(int largeur){_largeur=largeur;}

void CarteStoch::setTaille(int taille){_taille=taille;}


int CarteStoch::getType() const
{
return _type;
}

void CarteStoch::setType(int type)
{
_type = type;
}
