#include "arbrestochastique.h"
#include "Moteur/Piece/allpieces.h"

std::vector<Action> randomAction(CarteStoch & c){std::vector<Action> a; return a;}

Noeud::Noeud(const Carte & c) : _carte(c),_nbr_recherche(0),_nbr_valeur(0),_fils(0),_Actions(0),_pere(nullptr),_prof(0){
    load();
}

Noeud::Noeud(std::vector<Action> Actions, Noeud *pere) : _carte(pere->getCarte()),_nbr_recherche(0),_nbr_valeur(0),_fils(NULL),_Actions(Actions),_pere(pere) {
    for (auto A : _Actions) {
            switch(A.faire){
                case typeAction::DEPLACER:
                    _carte.deplacement(A.src,A.dest);
                    break;
                case typeAction::ATTAQUER:
                    _carte.attaque(A.src,A.dest);
                default:
                    std::cerr<<"mauvais type d'action"<<std::endl;
                    break;
                }
    }
    if (_carte.fini()!=-1){
        update(_carte.fini(),this);
    }
    else {
        update(roll_out(),this);
    }
    pere->_fils.push_back(this);
}

int Noeud::roll_out(){
    CarteStoch simulation( _carte);
    while(simulation.fini()==-1){
        std::vector<Action> act = randomAction(_carte);
        for (auto A : _Actions) {
            switch(A.faire){
                case typeAction::DEPLACER:

                    simulation.deplacement(A.src,A.dest);
                    break;
                case typeAction::ATTAQUER:
                    //simulation.getCase(A.src).getPiece()->attaque(dest)
                    break;
                default:
                    std::cerr<<"mauvais type d'action"<<std::endl;
                    break;
                }
            }
        }
        return simulation.fini();
}

void Noeud::update(int val, Noeud * n){
    _nbr_recherche++;
    _nbr_valeur+=val;
    if(n->_pere != nullptr){
        update(val,n->_pere);
    }
}

std::vector<Action> Noeud::jouer(){
    int max = -1;
    Noeud * best = nullptr;
    for (auto f : _fils){
        if(f->getNbrR()/f->getNbrV() > max){
            max = f->getNbrR()/f->getNbrV();
            best = f;
        }
    }
    if (max < 0.5)
    {
        std::vector<Action> act = randomAction(_carte);
        best = new Noeud(act,this);
    }
    return best->_Actions;
}

int Noeud::getNbrR() { return _nbr_recherche;}

int Noeud::getNbrV() { return _nbr_valeur;}

CarteStoch Noeud::getCarte() {return _carte;}

void Noeud::setNbrV(int v) {_nbr_valeur = v;}

void Noeud::setNbrR(int r) {_nbr_recherche = r;}

void Noeud::setCarte(Carte c) {_carte = c;}

void Noeud::save(){;}

void Noeud::load(){
    std::string cheminBase = "../../ProjetL3/FullMetalWar";
    std::string chemin = cheminBase+"/Ressources/Stochastique/Carte";
    switch(_carte.getType()){
        case 1:
            chemin += "P_";
            break;
        case 2:
            chemin += "M_";
            break;
        case 3:
            chemin += "S_";
            break;
        default:
            chemin += "_";
            break;

        ;}
    int largeur = _carte.getLargeur();
    int longueur = _carte.getLongueur();
    std::string temp = std::to_string(longueur)+"_"+std::to_string(largeur)+".text";
    chemin += temp;
    std::cout<<chemin<<std::endl;
    std::ifstream f(chemin,std::ios::in);
    if(f.bad()){
        std::cout << "fichier non trouvé" << std::endl;
        std::cout << __FILE__ << std::endl;
        std::ofstream ft(chemin.c_str(), std::ios::out);
        if ( !ft ){

            std::cerr << "Erreur de creation du fichier" << std::endl;

            exit(1);

        }
        ft << "0 0" <<std::endl
           << "0 0" <<std::endl;
        ft.close();
        std::ifstream f(chemin,std::ios::in);
    }
    int nbrFils = 0;
    int prof = 0;

    f  >> prof>> nbrFils;
    f >> _nbr_valeur >> _nbr_recherche;
    for(int i =0;i<nbrFils;i++){
        AjouterFils(f);
        std::cout<<"fin"<<std::endl;
    }


}

void Noeud::AjouterFils(std::ifstream &f){
    int nbrFils = 0;
    int prof = 0;
    int nbr_valeur,nbr_recherche;
    std::string ligneAction;
    f >> prof >> nbrFils;
    f >> nbr_valeur >> nbr_recherche;
    std::vector<Action> ListeC = trad(f);
    Noeud nouv(ListeC,this);
    for(int i = 0;i<nbrFils;i++){
        nouv.AjouterFils(f);
    }

}

void Noeud::toLatek(){}

std::vector<Action> Noeud::trad(std::ifstream &f){
    std::vector<Action> tmp;
    int nbrA =0;
    char faire;
    int src,dest;
    f >> nbrA;
    for(int i = 0;i<nbrA;i++){
        f >> faire >> src >> dest;
        Action tmpA;
        switch (faire) {
        case 'd':
            tmpA.faire = typeAction::DEPLACER;
            break;
        case 'a':
            tmpA.faire = typeAction::ATTAQUER;
            break;
        default:
            std::cerr<<"erreur : mauvais caractère : "<<faire<<std::endl;
        }
        tmpA.dest = dest;
        tmpA.src = src;
        tmp.push_back(tmpA);
    }
    return tmp;
}

