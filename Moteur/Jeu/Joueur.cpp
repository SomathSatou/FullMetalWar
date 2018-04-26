#include "Joueur.h"

Joueur::Joueur(const std::string &pseudonyme, Couleur couleur)
    : m_pseudonyme(pseudonyme), m_couleur(couleur), m_score(0),m_PACourant(10),m_PAMax(25){}

Joueur::~Joueur() { m_pieces.clear(); }

void Joueur::setPseudonyme(const std::string &pseudo){ m_pseudonyme = pseudo; }

void Joueur::setCouleur(const Couleur couleur){ m_couleur = couleur; }

void Joueur::creationArmee(const std::vector<std::pair<typePiece, int> > &liste_pieces, Carte * carte){
    m_carte = carte;
    for(const auto & tp : liste_pieces){
        for(int i = 0 ; i < tp.second ; i++){
            switch (tp.first) {
            case typePiece::CHAR:
                m_pieces.push_back(new Char(std::pair<int,int>(-1,-1) , m_couleur , this));
                break;
            case typePiece::BARGE:
                m_pieces.push_back(new Barge(std::pair<int,int>(-1,-1) , m_couleur , this));
                break;
            case typePiece::BASE:
                m_pieces.push_back(new Base(std::pair<int,int>(-1,-1) , m_couleur , this));
                break;
            case typePiece::VEDETTE:
                m_pieces.push_back(new Vedette(std::pair<int,int>(-1,-1) , m_couleur , this));
                break;
            case typePiece::CRABE:
                m_pieces.push_back(new Crabe(std::pair<int,int>(-1,-1) , m_couleur , this));
                break;
            case typePiece::GROS_TAS:
                m_pieces.push_back(new GrosTas(std::pair<int,int>(-1,-1) , m_couleur , this));
                break;
            case typePiece::MINERAI:
                m_pieces.push_back(new Minerai(std::pair<int,int>(-1,-1) , m_couleur , this));
                break;
            case typePiece::PONDEUSE:
                m_pieces.push_back(new Pondeuse(std::pair<int,int>(-1,-1) , m_couleur , this));
                break;
            default:
                std::cout << "\ntu n'a pas codé l'ajout des autres pieces... (creationArmee dans Joueur)\n";
                break;
            }
        }
    }
}

void Joueur::setScore(const int score){ m_score = score; }

void Joueur::setNombrePADebut(int deb) {m_PACourant = deb ;}

void Joueur::setNombrePAMax(int max){m_PAMax = max;}

void Joueur::ramasserMinerai(){ m_score+=1;}

void Joueur::ajouterPiece(Piece *p){m_pieces.push_back(p);}

int Joueur::getPA() const{return m_PACourant;}

bool Joueur::retirePA(int PA){
    if(PA>m_PACourant){
        return false;
    }else{
        m_PACourant-=PA;
        return true;
    }
}

int Joueur::getScore() const{ return m_score; }

Couleur Joueur::getCouleur() const{ return m_couleur; }

const std::string &Joueur::getPseudonyme() const { return m_pseudonyme; }

std::vector<Piece *> Joueur::getArmee(){
    return m_pieces;
}

Piece *Joueur::appartient(coordonnees c){
//    std::cout << "appartient\n";
    for(auto & p : m_pieces){
        if(p->getCoordonnees()==c){
            //std::cout << "trouvé\n" << std::flush;
            return p;
        }
    }
//    std::cout << "non trouvé\n" << std::flush;
    return nullptr;
}

coups Joueur::actionPossibles(){
    coups actions;
    coups c;
    for(auto p : m_pieces){
        c= p->actionsPossibles();
        actions.insert(actions.end(),c.begin(),c.end());
    }
    return actions;
}

std::vector<Action> Joueur::joue(){
    std::vector<Action> a;
    return a;
}

int Joueur::getNombrePACourant() const{return m_PACourant;}

int Joueur::getNombrePAMax()const {return m_PAMax;}

Carte *Joueur::getCarte() const{
    return m_carte;
}

std::string Joueur::toString() const{
    std::ostringstream oss;
    oss
            << m_pseudonyme
            << std::endl
            << "Armee : "
            << toStringPieces()
            << std::endl;
    return oss.str(); }

std::string Joueur::toStringPieces() const
{
    std::ostringstream oss;
    for(const auto & p : m_pieces){
        oss <<"\n\t"<< p->toString();
    }
    //for(std::vector<Piece *>::const_iterator i = m_pieces.begin(); i != m_pieces.end(); i++)
    //oss << "\tPiece " << ++j <<  "   " << (*i)->toString() << std::endl;
    return oss.str();
}
