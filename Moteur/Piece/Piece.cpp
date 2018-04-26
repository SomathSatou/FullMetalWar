#include "Piece.h"
#include "Moteur/Jeu/Joueur.h"


bool operator==(const std::pair<int, int> &a, const std::pair<int, int> &b){
    return a.first== b.first && a.second == b.second;
}


bool operator<(const triplet &a, const triplet &b){
    return b.cout.second < a.cout.second;
}

bool operator==(const triplet &a, const triplet &b){
    return a.sommet.first==b.sommet.first && a.sommet.second==b.sommet.second ;
}


Piece::Piece(coordonnees coor, Couleur color, int pointDeVieMax, Joueur *proprietaire)
    : m_coordonnee(coor),
      m_color(color),
      m_pointDeVie(pointDeVieMax),
      m_pointDeVieMax(pointDeVieMax),
      m_proprietaire(proprietaire){}

Piece::Piece(const Piece &p)
    : m_coordonnee(p.m_coordonnee),
      m_color(p.m_color),
      m_pointDeVie(p.m_pointDeVie),
      m_pointDeVieMax(p.m_pointDeVieMax),
      m_proprietaire(p.m_proprietaire){}

Piece::~Piece(){
    m_proprietaire->getCarte()->getCase(m_coordonnee.first,m_coordonnee.second).detruitPiece();
    delete(_attaque);
    delete(_deplacement);
}

int Piece::getPositionX() const { return m_coordonnee.first; }

int Piece::getPositionY() const { return m_coordonnee.second; }

coordonnees Piece::getCoordonnees() const { return m_coordonnee; }

int Piece::getPointDeVie() const { return m_pointDeVie; }

int Piece::getPointDeVieMax() const { return m_pointDeVieMax; }

Couleur Piece::getCouleur() const { return m_color; }

int Piece::getPoids() const{ return 1;}

std::vector<triplet> Piece::cases_a_portee(int portee){
    std::vector<triplet> path;
    std::vector<triplet> file;
    triplet t;

    for( auto & v : m_proprietaire->getCarte()->voisins(m_coordonnee) )
    {
        t.provenance = m_coordonnee;
        t.cout = std::pair<int,int>(1,1);
        t.sommet = v;
        file.push_back(t);
    }
    std::sort(file.begin(),file.end());

    triplet c;

    while(portee>0){
        c = file.back();
        file.pop_back();

        if ( std::find(path.begin(), path.end(), c) == path.end() ){
            path.push_back(c);

            for( auto v : m_proprietaire->getCarte()->voisins(c.sommet))
            {
                t.provenance = c.sommet;
                t.cout = std::pair<int,int>(c.cout.first+1,c.cout.second+1);
                t.sommet = v;

                auto present = std::find(file.begin(), file.end(), t);
                if ( (present == file.end()) || ((*present).cout> t.cout) ){
                    file.erase(present);
                    file.push_back(t);
                }
            }
            std::sort(file.begin(),file.end());
        }
    }
    file.clear();
    return path;
}

void Piece::setCoordonnee(const coordonnees &c) {
    if(m_coordonnee!= coordonnees(-1,-1))
        m_proprietaire->getCarte()->getCase(m_coordonnee.first,m_coordonnee.second).detruitPiece();

    if(c!=coordonnees(-1,-1)){
        m_coordonnee.first = c.first;
        m_coordonnee.second = c.second;
        m_proprietaire->getCarte()->getCase(m_coordonnee.first,m_coordonnee.second).nouvellePiece(this);
    }
}

void Piece::setPointDeVie(const int pointDeVie){ m_pointDeVie = pointDeVie; }

std::string Piece::toString() const{
    std::ostringstream oss;
    oss << infoPiece()
        << this
        << "\n\tPosition : "
        << m_coordonnee.first
        << " "
        << m_coordonnee.second
        << "\n\tetat : "
        << getPointDeVie()
        << "/"
        << getPointDeVieMax()
        << "\n\tenergie";
    return oss.str();
}

void Piece::setTypeDeplacement(IDeplacement *typeDepla){
    _deplacement=typeDepla;
}

void Piece::setTypeAttaque(IAttaque * typeAtk){
    _attaque=typeAtk;
}

Joueur *Piece::getJoueur() const { return m_proprietaire;}

int Piece::deplacement(const coordonnees &destination) const{
    std::vector<triplet> path(pathfinding_dijkstra_manhattan(m_coordonnee, destination));
    triplet t;
    t.provenance=destination;
    t.cout=std::pair<int,int>(0,0);
    t.sommet=destination;
    auto result (std::find(path.begin(), path.end(), t));
    if(result == path.end()){
        std::cout << "\n\tcase inaccessible";
        return -1;
    }
    else
        return (*result).cout.first;
}

bool Piece::attaque(const coordonnees &ennemi){UNUSED(ennemi); return false;}



coups Piece::actionsPossibles(){
    coups actions(voisins());
    coups ennemis(_attaque->aPortee(m_proprietaire->getCarte(),m_coordonnee,m_color));
    actions.insert(actions.end(),ennemis.begin(),ennemis.end());
    //    std::cout << "\nVoici la liste de mes actions possibles : ";
    //    for(auto a : actions){
    //        std::cout << "\n\tma position : "
    //                  << a.source.first
    //                  << "-"
    //                  << a.source.second
    //                  << "\tmon objectif : "
    //                  << a.destination.first
    //                  << "-"
    //                  << a.destination.second
    //                  << "\tle cout : "
    //                  << a.cout;

    //        std::cout << std::flush;
    //    }
    return actions;

}

bool Piece::prendreDegats(int d){
    m_pointDeVie-=d;
    return m_pointDeVie<=0;
}

bool Piece::maj_nouveau_tour(){
    if(m_pointDeVie<=0)
        return false;
    return true;
}

std::vector<triplet> Piece::pathfinding_dijkstra_manhattan(const coordonnees &source, const coordonnees &destination) const{
    std::vector<triplet> path;
    std::vector<triplet> file;
    triplet t;
    t.provenance = source;
    t.cout = std::pair<int,int>(0,manhattan(source,destination));
    t.sommet = source;
    path.push_back(t);

    //std::cout << "\nsommet initial : " << t.sommet.first << t.sommet.second ;
    //std::cout << "\nsommet objectif : " << destination.first << destination.second << "\n";

    for( auto & v : _deplacement->voisin(m_proprietaire->getCarte(), source) )
    {
        t.provenance = source;
        t.cout = std::pair<int,int>(1, manhattan(v,destination));
        t.sommet = v;
        //std::cout << "\n\tsommet voisin : " << t.sommet.first << t.sommet.second;
        file.push_back(t);
    }
    std::sort(file.begin(),file.end());

    bool not_objectif = true;
    triplet c;

    while(not_objectif && !file.empty() ){
        c = file.back();
        file.pop_back();
        //        std::cout << "\nsommet courant : " << c.sommet.first << c.sommet.second << "\n" ;

        if(c.sommet==destination){
            not_objectif=false;
            //            std::cout << "\nobjectif atteint!\n";
        }
        if ( std::find(path.begin(), path.end(), c) == path.end() ){
            path.push_back(c);

            for( auto v : _deplacement->voisin(m_proprietaire->getCarte(), c.sommet))
            {
                t.provenance = c.sommet;
                t.cout = std::pair<int,int>(c.cout.first+1,manhattan(v, destination));
                t.sommet = v;
                //                std::cout << "\n\tsommet voisin : " << t.sommet.first << t.sommet.second << "\n";
                auto present = std::find(file.begin(), file.end(), t);
                if ( (present != file.end()) && ((*present).cout> t.cout) ){
                    file.erase(present);
                }
                file.push_back(t);
            }
            std::sort(file.begin(),file.end());
        }
        //        else
        //            std::cout << " sommet deja present dans path";
    }
    file.clear();
    return path;
}

int Piece::manhattan(const coordonnees &source, const coordonnees &destination) const {
    if(source.second%2) //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////a modifier
        return abs(source.first-destination.first)+abs(source.second-destination.second);
    else
        return abs(source.first-destination.first)+abs(source.second-destination.second);
}

coups Piece::voisins(){

    coups path;
    coup t;

    for( auto & v : _deplacement->voisin(m_proprietaire->getCarte(), m_coordonnee) ){
        t.source=m_coordonnee;
        t.destination=v;
        t.cout=1;
        path.push_back(t);
    }
    return path;

    /*
    if(cout_max>0){

        coups file;
        coup t;

        std::pair<std::pair<coordonnees,coordonnees>,int> position;

        for( auto & v : _deplacement->voisin(m_proprietaire->getCarte(), m_coordonnee) ){
            t.source=m_coordonnee;
            t.destination=v;
            t.cout=1;
            file.push_back(t);
        }
        std::sort(file.begin(),file.end());

        coup c;

        while(!file.empty() ){
            c = file.back();
            file.pop_back();

            if ( std::find(path.begin(), path.end(), c) == path.end() ){
                path.push_back(c);

                if(c.cout!=cout_max){
                    for( auto v : _deplacement->voisin(m_proprietaire->getCarte(), c.source)){
                        t.source = m_coordonnee;
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
            else
                std::cout << " sommet deja present dans path";
        }
        file.clear();
    }
    return path;
    */
}

void Piece::setJoueur(Joueur *proprietaire)
{
    m_proprietaire = proprietaire;
}

bool operator<(const coup &a, const coup &b){
    return b.cout < a.cout;
}

bool operator==(const coup &a, const coup &b){
    return a.destination.first==b.destination.first && a.destination.second==b.destination.second;
}
