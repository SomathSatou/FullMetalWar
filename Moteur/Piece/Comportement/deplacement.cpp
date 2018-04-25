#include"deplacement.h"

std::vector<coordonnees> Deplacement_nul::voisin(Carte *carte, coordonnees source){
    UNUSED(carte);
    UNUSED(source);
    std::vector<coordonnees> voisin;
    return voisin;
}

bool Deplacement_nul::accessible(Carte *carte, coordonnees c){
    UNUSED(carte);
    UNUSED(c);
    return false;
}

std::vector<coordonnees> Deplacement_terre::voisin(Carte *carte, coordonnees source){
    std::vector<coordonnees> voisin;
    for(auto & v : carte->voisins(source))
        if(accessible(carte,v))
            voisin.push_back(v);
    return voisin;
}

bool Deplacement_terre::accessible(Carte *carte, coordonnees c){
    return (c.first>=0 && carte->isCaseTerreEtMontagne(c.first,c.second) && !carte->getCase(c.first,c.second).hasPiece());
}

std::vector<coordonnees> Deplacement_eau::voisin(Carte *carte, coordonnees source){
    std::vector<coordonnees> voisin;
    for(auto & v : carte->voisins(source))
        if(accessible(carte,v))
            voisin.push_back(v);
    return voisin;
}

bool Deplacement_eau::accessible(Carte *carte, coordonnees c){
    return (c.first>=0 && carte->isCaseEau(c.first,c.second) && !carte->getCase(c.first,c.second).hasPiece());
}

std::vector<coordonnees> Deplacement_terre_sans_mont::voisin(Carte *carte, coordonnees source){
    std::vector<coordonnees> voisin;
    for(auto & v : carte->voisins(source))
        if(accessible(carte,v))
            voisin.push_back(v);
    return voisin;
}

bool Deplacement_terre_sans_mont::accessible(Carte *carte, coordonnees c){
    return (c.first>=0 && carte->isCaseTerreSansMontagne(c.first,c.second) && !carte->getCase(c.first,c.second).hasPiece());
}




/*
std::vector<coordonnees> voisin;
if(!source.second%2){//si y est pair
    if(accessible(carte , coordonnees (source.first-1 , source.second+1 ))){
        std::cout << " sommet " << source.first-1 << " " << source.second+1 << "present\n";
        voisin.push_back(coordonnees(source.first-1 , source.second+1 ));
    }else{
        std::cout << " sommet " << source.first-1 << " " << source.second+1 << "absent\n";
    }


    if(accessible(carte , coordonnees(source.first-1 , source.second   ))){
        std::cout << " sommet " << source.first-1 << " " << source.second << "present\n";
        voisin.push_back(coordonnees(source.first-1 , source.second   ));
    }else{
        std::cout << " sommet " << source.first-1 << " " << source.second << "absent\n";
    }


    if(accessible(carte , coordonnees(source.first-1 , source.second-1 ) )){
        std::cout << " sommet " << source.first-1 << " " << source.second-1 << "present\n";
        voisin.push_back(coordonnees(source.first-1 , source.second-1 ));
    }else{
        std::cout << " sommet " << source.first-1 << " " << source.second-1 << "absent\n";
    }


    if(accessible(carte , coordonnees(source.first   , source.second+1 ) )){
        std::cout << " sommet " << source.first << " " << source.second+1 << "present\n";
        voisin.push_back(coordonnees(source.first   , source.second+1 ));
    }else{
        std::cout << " sommet " << source.first << " " << source.second+1 << "absent\n";
    }


    if(accessible(carte , coordonnees(source.first   , source.second-1 ))){
        std::cout << " sommet " << source.first << " " << source.second-1 << "present\n";
        voisin.push_back(coordonnees(source.first   , source.second-1 ));
    }else{
        std::cout << " sommet " << source.first << " " << source.second-1 << "absent\n";
    }


    if(accessible(carte , coordonnees(source.first+1 , source.second   ))){
        std::cout << " sommet " << source.first+1 << " " << source.second << "present\n";
        voisin.push_back(coordonnees(source.first+1 , source.second   ));
    }else{
        std::cout << " sommet " << source.first+1 << " " << source.second << "absent\n";
    }
}else{
    if(accessible(carte , coordonnees(source.first   , source.second+1))){
        std::cout << " sommet " << source.first << " " << source.second+1 << "present\n";
        voisin.push_back(coordonnees(source.first   , source.second+1));
    }else{
        std::cout << " sommet " << source.first << " " << source.second+1 << "absent\n";
    }

    if(accessible(carte , coordonnees(source.first-1 , source.second))){
        std::cout << " sommet " << source.first-1 << " " << source.second << "present\n";
        voisin.push_back(coordonnees(source.first-1 , source.second));
    }else{
        std::cout << " sommet " << source.second << " " << source.second << "absent\n";
    }

    if(accessible(carte , coordonnees(source.first   , source.second-1))){
        std::cout << " sommet " << source.first << " " << source.second-1 << "present\n";
        voisin.push_back(coordonnees(source.first   , source.second-1));
    }else{
        std::cout << " sommet " << source.first << " " << source.second-1 << "absent\n";
    }

    if(accessible(carte , coordonnees(source.first+1 , source.second+1))){
        std::cout << " sommet " << source.first+1 << " " << source.second+1 << "present\n";
        voisin.push_back(coordonnees(source.first+1 , source.second+1));
    }else{
        std::cout << " sommet " << source.first+1 << " " << source.second+1 << "absent\n";
    }

    if(accessible(carte , coordonnees(source.first+1 , source.second))){
        std::cout << " sommet " << source.first+1 << " " << source.second << "present\n";
        voisin.push_back(coordonnees(source.first+1 , source.second));
    }else{
        std::cout << " sommet " << source.first+1 << " " << source.second << "absent\n";
    }

    if(accessible(carte , coordonnees(source.first+1 , source.second-1))){
        std::cout << " sommet " << source.first+1 << " " << source.second-1 << "present\n";
        voisin.push_back(coordonnees(source.first+1 , source.second-1));
    }else{
        std::cout << " sommet " << source.first+1 << " " << source.second-1 << "absent\n";
    }

}
return voisin;
*/

IDeplacement::~IDeplacement(){}
