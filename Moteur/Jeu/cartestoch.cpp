#include "cartestoch.h"
#include "plateau.h"
#include "Moteur/Piece/allpieces.h"

std::vector<CaseStoch> CarteStoch::getPlateau() const {return _plateau;}

void CarteStoch::setPlateau(Plateau c){
    for(auto oldCase : c.getListe()){
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

        CaseStoch newCase;
        switch(oldCase.getType()){
        case typeCase::MONTAGNE:

            newCase.type = 3;
            break;
        case typeCase::PLAINE:
            newCase.type = 1;
            break;
        case typeCase::MER:
            newCase.type = 4;
            break;
        case typeCase::MARAIS:
            newCase.type =2;
            break;
        case typeCase::RECIF:
            newCase.type = 5;
            break;
        default:
            newCase.type = 0;
            std::cerr<<"mauvais type de case stocha"<<std::endl;
            break;
        }
        Unite temp;
        if (dynamic_cast<Char *>(oldCase.getPiece())){
            temp.mun = 1;
            if(oldCase.getPiece()->getCouleur() == Couleur::BLEU){temp.proprio =1;}
            else{temp.proprio = 2;}
            temp.pv = 2;
            temp.type = 1; // 1 pour char
        }

        else{ if (dynamic_cast<GrosTas *>(oldCase.getPiece())){
                temp.mun = 1;
                if(oldCase.getPiece()->getCouleur() == Couleur::BLEU){temp.proprio =1;}
                else{temp.proprio = 2;}
                temp.pv = 2;
                temp.type = 2; // 1 pour char
            }

            else{                 temp.mun = 1;
                temp.proprio = 0; // a modifier
                temp.pv = 2;
                temp.type = 0; // 1 pour char
            }
        }
        newCase.piece = temp;
        //rajouter des dynamic cast pour avoir plus de piece
        _plateau.push_back(newCase);
    }
}

CarteStoch::CarteStoch(const Plateau &c){setPlateau(c);}

CarteStoch::CarteStoch(const CarteStoch &c):_longueur(c.getLongueur()),
    _largeur(c.getLargeur()),
    _taille(c.getTaille()),
    _type(c.getType()){
    for(auto Case : c.getPlateau()){
        _plateau.push_back(Case);
    }
}

void CarteStoch::faire(Action a){
    switch(a.getFaire()){
    case typeAction::DEPLACER :
        deplacement(a.getSrc(),a.getDest());
        break;
    case typeAction::ATTAQUER :
        attaque(a.getSrc(),a.getDest());
        break;
    default:
        std::cerr<<"erreur action inconnue"<<std::endl;
    }
    return;
}

bool CarteStoch::deplacementPossible(int src,int dest){
    if(src>=0 && src<_taille){
        //std::cout<<"type :" <<getPlateau()[src].piece.type<< " src : "<< src << "dest : "<<dest <<std::endl;
        switch(getPlateau()[src].piece.type){
        case 0:
            //std::cerr<<"pas de piece"<<std::endl;
            return false;
            break;
        case 1: //cas d'un tank
            if (dest>=0 && dest<_taille){
                if ((getPlateau()[dest].type<4)&&(getPlateau()[dest].piece.type == 0)){
                    return true;}
                else{//std::cout<<"deplacement interdit "<<src<<" "<<dest<<std::endl;
                    return false;}
            }
            else{//std::cout<<"dest invalide"<<std::endl;
                return false;}
            break;
        default: // case piece non implémenter
            // std::cout<<"faire les different cas du switch déplacement"<<std::endl;
            break;
        }
    }
    return false;
}

bool CarteStoch::deplacement(int src,int dest){
    if(src>=0 && src<_taille){
        //std::cout<<"type :" <<getPlateau()[src].piece.type<< " src : "<< src << "dest : "<<dest <<std::endl;
        switch(getPlateau()[src].piece.type){
        case 0:
            //std::cerr<<"pas de piece"<<std::endl;
            return false;
            break;
        case 1: //cas d'un tank
            if (dest>=0 && dest<_taille){
                if ((getPlateau()[dest].type<4)&&(getPlateau()[dest].piece.type == 0)){
                    setPiece(getPlateau()[src].piece,dest);
                    setPieceType(0,src);
                    return true;}
                else{//std::cout<<"deplacement interdit "<<src<<" "<<dest<<std::endl;
                    return false;}
            }
            else{//std::cout<<"dest invalide"<<std::endl;
                return false;}
            break;
        default: // case piece non implémenter
            std::cout<<"faire les different cas du switch déplacement"<<std::endl;
            break;
        }
    }
    return false;
}

bool CarteStoch::attaque(int src, int dest){
    if((dest<0)||(dest>=getTaille())||(getPlateau()[src].piece.mun<1)){return false;}
    if((getPlateau()[src].piece.proprio!=getPlateau()[dest].piece.proprio)&&(getPlateau()[dest].piece.proprio!=0)){
        degat(dest);
        setMun(0,src);
        if (getPlateau()[dest].piece.pv == 0){
            setPieceType(0,dest);
        }
        return true;
    }
    return false;
}

bool CarteStoch::attaquePossible(int src, int dest){
    if((dest<0)||(dest>=getTaille())||(getPlateau()[src].piece.mun<1)){return false;}
    if((getPlateau()[src].piece.proprio!=getPlateau()[dest].piece.proprio)&&(getPlateau()[dest].piece.proprio!=0)){
        setMun(0,src);
        return true;
    }
    return false;
}

std::set<int> CarteStoch::portee(int src){
    std::set<int> ret;
    int d = 2;
    if (getPlateau()[src].piece.type==2){
        d = 3;}
    ret.insert(src);
    while(d>0){
        for(auto src : ret){
            if(deplacementPossible(src,src+1)){ret.insert(src+1);}
            if(deplacementPossible(src,src+1)){ret.insert(src-1);}
            if((src/getLongueur())%2==0){
                if (deplacementPossible(src,src+getLongueur()-1)) {ret.insert(src+getLongueur()-1);} // haut-gauche
                if (deplacementPossible(src,src-getLongueur()-1)) {ret.insert(src-getLongueur()-1);} // bas-gauche
            }
            if((src/getLongueur())%2==1){
                if (deplacementPossible(src,src+getLongueur()+1)) {ret.insert(src+getLongueur()+1);} // haut-droite
                if (deplacementPossible(src,src-getLongueur()+1)) {ret.insert(src-getLongueur()+1);} // bas-droite
            }
        }
        d--;
    }
    ret.erase(src);
    return ret;

}

bool CarteStoch::fini(){
    bool J1 = true;
    bool J2 = true;
    for(auto Case : getPlateau()){
        if(Case.piece.proprio == 1)
        {J1 = false;}
        if(Case.piece.proprio == 2)
        {J2 = false;}
    }
    if(J1 || J2){
        return true;
    }
    return false;
}

int CarteStoch::gagnant(){
    bool J1 = true;
    bool J2 = true;
    for(auto Case : getPlateau()){
        if(Case.piece.proprio == 1)
        {J1 = false;}
        if(Case.piece.proprio == 2)
        {J2 = false;}
    }
    if (J1){return 0;}
    if(J2){return 1;}
    return 0;
}

void CarteStoch::finTour(){for(int i = 0;i<_taille;i++){
        _plateau[i].piece.mun = 1;}
                          }

int CarteStoch::getLongueur() const{return _longueur;}

int CarteStoch::getLargeur() const{return _largeur;}

int CarteStoch::getTaille() const{return _taille;}

CaseStoch CarteStoch::getCase(int x) const{return _plateau[x];}

void CarteStoch::setLongueur(int longueur){_longueur=longueur;}

void CarteStoch::setLargeur(int largeur){_largeur=largeur;}

void CarteStoch::setTaille(int taille){_taille=taille;}

void CarteStoch::setPiece(Unite P, int dest){_plateau[dest].piece=P;}

void CarteStoch::setPieceType(int type, int cible){_plateau[cible].piece.type = type;
                                                   _plateau[cible].piece.proprio = type;
                                                                                                  _plateau[cible].piece.pv = type;
                                                                                                                                                 _plateau[cible].piece.mun = type;}

void CarteStoch::setMun(int val, int src){_plateau[src].piece.mun = val;}

void CarteStoch::degat(int dest){_plateau[dest].piece.pv--;}

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
                    if(_plateau[_longueur*j+i].piece.proprio == 1){std::cout<<"\033[1;31mC\033[0m|";}

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
                    if(_plateau[_longueur*j+i].piece.proprio == 1){std::cout<<"\033[1;31mC\033[0m|";}

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
