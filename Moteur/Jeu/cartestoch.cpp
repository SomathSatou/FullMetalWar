#include "caretestoch.h"
#include "Carte.h"
#include "CaseMap.h"
#include "Moteur/Piece/allpieces.h"

std::vector<Case> CarteStoch::getPlateau() const {return _plateau;}

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
                   newCase.type = 4;
                   break;
               case TYPECASE::MARAIS:
                   newCase.type =2;
                   break;
               case TYPECASE::RECIF:
                   newCase.type = 5;
                   break;
               default:
                   newCase.type = 0;
                   std::cerr<<"mauvais type de case stocha"<<std::endl;
                   break;
           }
           Unite temp;
           if (dynamic_cast<Char *>(oldCase.getPiece())){
               std::cout<<"un char"<<std::endl;
                 temp.mun = 1;
                 if(oldCase.getPiece()->getCouleur() == Couleur::BLEU){temp.proprio =0;}
                 else{temp.proprio = 1;}
                 temp.pv = 5;
                 temp.type = 1; // 1 pour char
                 }

           else{                 temp.mun = 1;
               temp.proprio = 0; // a modifier
               temp.pv = 5;
               temp.type = 0; // 1 pour char
            }
                            newCase.piece = temp;
           //rajouter des dynamic cast pour avoir plus de piece
           _plateau.push_back(newCase);
      }
}

bool CarteStoch::deplacement(int src,int dest){
    if(src>=0 && src<_taille){
        std::cout<<"type :" <<getPlateau()[src].piece.type<< " src : "<< src << "dest : "<<dest <<std::endl;
        switch(getPlateau()[src].piece.type){
            case 0:
                std::cerr<<"pas de piece"<<std::endl;
                return false;
                break;
            case 1: //cas d'un tank
                if (dest>=0 && dest<_taille){
                     if (getPlateau()[dest].type<4){
                         setPiece(getPlateau()[src].piece,dest);
                         setPieceType(0,src);
                         return true;}
                     else{std::cerr<<"deplacement interdit"<<src<<" "<<dest<<std::endl;
                          return false;}
                    }
                else{std::cerr<<"dest invalide"<<std::endl;
                    return false;}
                break;
            default: // case piece non implémenter
                std::cerr<<"faire les different cas du switch déplacement"<<std::endl;
                break;
        }
    }
    else{std::cerr<<"src invalide"<<std::endl;
        return false;}
    return false;
}

void CarteStoch::attaque(int src, int dest){src = dest;}

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

void CarteStoch::Afficher(){
    for(int i = 0;i<_largeur;i++){
        if(i%2==0){
            for (int j = 0;j<_longueur;j++)
                {std::cout<< "/\\";}
            std::cout<<std::endl<<"|";
            for (int j = 0;j<_longueur;j++)
                {
                if (_plateau[_longueur*j+i].piece.type == 1) {
                    if(_plateau[_longueur*j+i].piece.proprio == 0){std::cout<<"\033[1;31mC\033[0m|";}

                    else{std::cout<<"\033[1;34mC\033[0m|";}}
                else {std::cout<<" |";}
                }
            std::cout<<std::endl;
            }
        else
            {
            std::cout<<"\\";
            for (int j = 0;j<_longueur;j++)
                    {std::cout<< "/\\";}
                std::cout<<std::endl<<" |";
                for (int j = 0;j<_longueur;j++)
                    {
                    if (_plateau[_longueur*j+i].piece.type == 1) {
                        if(_plateau[_longueur*j+i].piece.proprio == 0){std::cout<<"\033[1;31mC\033[0m|";}

                        else{std::cout<<"\033[1;34mC\033[0m|";}}
                    else {std::cout<<" |";}
                    }
                std::cout<<std::endl;
                }
            }
         for (int j = 0;j<_longueur;j++)
            {std::cout<< "\\/";}
         std::cout<<std::endl;
    }
