#ifndef IATTAQUE_H
#define IATTAQUE_H


class IAttaque{
public:
//    virtual coups aPortee(Plateau * carte , Coordonnee source , Couleur color) =0;
    virtual ~IAttaque(){}
};

class Portee3 : public IAttaque{
public:
//    coups aPortee(Plateau * carte , Coordonnee source , Couleur color) override{
//        coups ennemis;
//        //    coups marque;
//        //    coups file;
//        //    coup t;


//        //    for( auto & v : carte->voisins(source)){
//        //        t.source=source;
//        //        t.destination=v;
//        //        t.cout=1;
//        //        file.push_back(t);
//        //    }
//        //    std::sort(file.begin(),file.end());

//        //    coup c;

//        //    while(!file.empty() ){
//        //        c = file.back();
//        //        file.pop_back();

//        //        if ( std::find(marque.begin(), marque.end(), c) == marque.end() ){
//        //            if(carte->getCase(c.destination.first,c.destination.second).hasPiece())
//        //                if(carte->getCase(c.destination.first,c.destination.second).getPiece()->getCouleur() != color)
//        //                    ennemis.push_back(c);
//        //            marque.push_back(c);

//        //            if(c.cout<3){
//        //                for( auto v : carte->voisins(c.destination)){
//        //                    t.source = c.destination;
//        //                    t.cout = c.cout+1;
//        //                    t.destination = v;
//        //                    auto present = std::find(file.begin(), file.end(), t);
//        //                    if ( (present != file.end()) && ((*present).cout> t.cout) ){
//        //                        file.erase(present);
//        //                    }
//        //                    file.push_back(t);
//        //                }
//        //                std::sort(file.begin(),file.end());
//        //            }
//        //        }
//        //    }


//        return ennemis;

//    }

};


class PorteeNulle : public IAttaque{
public:
//    coups aPortee(Plateau * carte , Coordonnee source , Couleur color) override{
//        UNUSED(carte);
//        UNUSED(source);
//        UNUSED(color);
//        coups nul;
//        nul.clear();
//        return nul;
//    }

};

#endif // IATTAQUE_H
