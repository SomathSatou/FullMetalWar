#include "caretestoch.h"
#include "Carte.h"
#include "CaseMap.h"

std::vector<Case> CarteStoch::getPlateau(){return _plateau;}

void CarteStoch::setPlateau(Carte c){
       for(auto oldCase : c.getListe()){
           Case newCase;
           switch(oldCase.getType()){
               case TYPECASE::MONTAGNE:

                   break;
               case TYPECASE::PLAINE:

                   break;
               case TYPECASE::MER:

                   break;
               case TYPECASE::MARAIS:

                   break;
               case TYPECASE::RECIF:

                   break;
               default:

                   break;
           }
      }
}

void CarteStoch::deplacer(int dest){}

void CarteStoch::attaquer(int dest){}

int CarteStoch::getLongueur() const{return _longueur;}

int CarteStoch::getLargeur() const{return _largeur;}

int CarteStoch::getTaille() const{return _taille;}

void CarteStoch::setLongueur(int longueur){_longueur=longueur;}

void CarteStoch::setLargeur(int largeur){_largeur=largeur;}

void CarteStoch::setTaille(int taille){_taille=taille;}
