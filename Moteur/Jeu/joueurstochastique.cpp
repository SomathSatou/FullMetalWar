#include "joueurstochastique.h"

joueurStochastique::joueurStochastique(const std::string &pseudonyme, Couleur couleur,bool joueur)
    :Joueur(pseudonyme,couleur,joueur),
      _arbre(nullptr){}

coups joueurStochastique::jouer(Plateau p){
    UNUSED(p);
    coups ret;
    std::vector<Action> actions = _arbre->Courant->jouer();
    for(auto f : _arbre->Courant->getFils()){
        if (actions == f->getActions()){
            _arbre->Courant = f;
        }
    }
    for (auto a : actions){
        ret.push_back(coup(Coordonnee(a.getSrc()%(_arbre->Courant->getCarte().getLongueur()),a.getSrc()/(_arbre->Courant->getCarte().getLongueur())),Coordonnee(a.getDest()%(_arbre->Courant->getCarte().getLongueur()),a.getDest()/(_arbre->Courant->getCarte().getLongueur())),a.getFaire()));
    }

    return ret;
}

Arbre *joueurStochastique::getArbre(){return _arbre;}

void joueurStochastique::setArbre(Arbre *arbre)
{
    _arbre = arbre;
}

