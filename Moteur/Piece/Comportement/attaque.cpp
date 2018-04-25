#include "attaque.h"

coups Portee3::aPortee(Carte *carte, coordonnees source, Couleur color){
    coups ennemis;
    coups marque;
    coups file;
    coup t;


    for( auto & v : carte->voisins(source)){
        t.source=source;
        t.destination=v;
        t.cout=1;
        file.push_back(t);
    }
    std::sort(file.begin(),file.end());

    coup c;

    while(!file.empty() ){
        c = file.back();
        file.pop_back();

        if ( std::find(marque.begin(), marque.end(), c) == marque.end() ){
            if(carte->getCase(c.destination.first,c.destination.second).hasPiece())
                if(carte->getCase(c.destination.first,c.destination.second).getPiece()->getCouleur() != color)
                    ennemis.push_back(c);
            marque.push_back(c);

            if(c.cout<3){
                for( auto v : carte->voisins(c.destination)){
                    t.source = c.destination;
                    t.cout = c.cout+1;
                    t.destination = v;
                    auto present = std::find(file.begin(), file.end(), t);
                    if ( (present != file.end()) && ((*present).cout> t.cout) ){
                        file.erase(present);
                    }
                    file.push_back(t);
                }
                std::sort(file.begin(),file.end());
            }
        }
    }


    return ennemis;

}

coups PorteeNulle::aPortee(Carte *carte, coordonnees source, Couleur color){
    UNUSED(carte);
    UNUSED(source);
    UNUSED(color);
    coups nul;
    nul.clear();
    return nul;
}

IAttaque::~IAttaque(){}
