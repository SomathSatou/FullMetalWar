#include "arbrestochastique.h"
#include "Moteur/Piece/allpieces.h"
#include <ctime>

std::vector<Action> actionPossiblePiece(CarteStoch c,int src, int joueur){
    UNUSED(joueur);
    std::vector<Action> retu;
    if (c.deplacementPossible(src,src+1)) {retu.push_back(Action(typeAction::DEPLACER,src,src+1));} // droite
    if (c.deplacementPossible(src,src-1)) {retu.push_back(Action(typeAction::DEPLACER,src,src-1));} // gauche
    if (c.deplacementPossible(src,src+c.getLongueur())) {retu.push_back(Action(typeAction::DEPLACER,src,src+c.getLongueur()));} // haut
    if (c.deplacementPossible(src,src-c.getLongueur())) {retu.push_back(Action(typeAction::DEPLACER,src,src-c.getLongueur()));} // bas
    if((src/c.getLongueur())%2==0){
        if (c.deplacementPossible(src,src+c.getLongueur()-1)) {retu.push_back(Action(typeAction::DEPLACER,src,src+c.getLongueur()-1));} // haut-gauche
        if (c.deplacementPossible(src,src-c.getLongueur()-1)) {retu.push_back(Action(typeAction::DEPLACER,src,src-c.getLongueur()-1));} // bas-gauche
    }
    if((src/c.getLongueur())%2==1){
        if (c.deplacementPossible(src,src+c.getLongueur()+1)) {retu.push_back(Action(typeAction::DEPLACER,src,src+c.getLongueur()+1));} // haut-droite
        if (c.deplacementPossible(src,src-c.getLongueur()+1)) {retu.push_back(Action(typeAction::DEPLACER,src,src-c.getLongueur()+1));} // bas-droite
    }
    for(auto dest : c.portee(src)){
        if(c.attaquePossible(src,dest)){c.setMun(0,src);for(int i = 6;i>0;i--){
                retu.push_back(Action(typeAction::ATTAQUER,src,dest));}

        }

    }


    //std::cout<<"nbr coup possible " << retu.size() <<std::endl;
    return retu;}

std::vector<Action> randomAction(CarteStoch const & c,int joueur){
    std::srand(std::time(0));
    std::vector<Action> actionsPossible;
    std::vector<Action> tmp;

    CarteStoch copie(c);
    int tour = 0;
    while(tour<5){
        for(unsigned int i = 0;i<copie.getPlateau().size();i++){
            if(copie.getPlateau()[i].piece.proprio == joueur+1 ){
                for(auto a : actionPossiblePiece(copie,i,joueur+1)){
                    tmp.push_back(a);}
            }
        }

        int indiceRandom = std::rand()%tmp.size() ;
        Action ret = tmp[indiceRandom];
        actionsPossible.push_back(ret);
        copie.faire(ret);
        tour++;
        tmp.clear();
    }
    return actionsPossible;}

Noeud::Noeud(const Plateau & c) : _carte(c),_nbr_recherche(0),_nbr_valeur(0),_fils(0),_Actions(0),_pere(nullptr),_prof(0){
    load();
}

Noeud::Noeud(std::vector<Action> Actions, Noeud *pere)
    : _carte(pere->getCarte()),_nbr_recherche(0),_nbr_valeur(0),_Actions(Actions),_pere(pere),_prof(pere->getProf()+1) {
    for (auto A : _Actions) {
        switch(A.getFaire()){
        case typeAction::DEPLACER:
            _carte.deplacement(A.getSrc(),A.getDest());
            break;
        case typeAction::ATTAQUER:
            _carte.attaque(A.getSrc(),A.getDest());
            break;
        default:
            std::cerr<<"mauvais type d'action"<<std::endl;
            break;
        }
    }
    if (_carte.fini()==false){
        update(_carte.gagnant());
    }
    else {
        update(roll_out());
    }
    pere->addFils(this);
}

int Noeud::roll_out(){
    CarteStoch simulation( _carte);
    int i = _prof;
    while((simulation.fini()==false)&&(i<20)){
        std::vector<Action> Actions = randomAction(simulation,_prof%2);
        for(auto act : Actions){
            simulation.faire(act);
        }
        i++;
    }
    return simulation.gagnant();
}

void Noeud::update(int val){
    _nbr_recherche++;
    _nbr_valeur+=val;
    if(getPere() != nullptr){
        getPere()->update(val);
    }
}

std::vector<Action> Noeud::jouer(){
    float max = -1;
    float min = 1;
    Noeud * best = nullptr;
    if(_prof%2 == 0){
        for (auto f : _fils){
            if((float)f->getNbrV()/(float)f->getNbrR() > max){
                max = (float)f->getNbrV()/(float)f->getNbrR();
                best = f;
            }
        }

        if (max < 0.25)
        {
            if(_prof%2 == 1 ){_carte.finTour();}
            std::vector<Action> act;
            int r =0;
            do{
                r++;
                act = randomAction(_carte,_prof%2);
            }while((estFils(act))&&(r<500));
            if(r!=500){best = new Noeud(act,this);}
        }
    }
    else
    {
        for (auto f : _fils){
            if((float)f->getNbrV()/(float)f->getNbrR() < min){
                min = (float)f->getNbrV()/(float)f->getNbrR();
                best = f;
            }
        }

        if (min > -0.25)
        {
            if(_prof%2 == 1 ){_carte.finTour();}
            std::vector<Action> act;
            int r =0;
            do{
                r++;
                act = randomAction(_carte,_prof%2);
            }while((estFils(act))&&(r<500));
            if(r!=500){best = new Noeud(act,this);}
        }
    }
    return best->_Actions;
}

bool Noeud::estFils(std::vector<Action> act){
    for(auto f : _fils){
        if(f->getActions() == act){return true;}
    }
    return false;
}

int Noeud::getNbrR() { return _nbr_recherche;}

int Noeud::getNbrV() { return _nbr_valeur;}

CarteStoch Noeud::getCarte() const {return _carte;}

std::vector<Noeud *> Noeud::getFils() {return _fils;}

void Noeud::setNbrV(int v) {_nbr_valeur = v;}

void Noeud::setNbrR(int r) {_nbr_recherche = r;}

void Noeud::setCarte(Plateau c) {_carte = c;}

void Noeud::addFils(Noeud *n){_fils.push_back(n);}

void Noeud::save(){
    std::string cheminBase = "../FullMetalWar";
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
    std::cout<<"carte sauvé : "<<chemin<<std::endl;
    std::ofstream f(chemin.c_str(),std::ios::out |std::ios::trunc);
    if (!f.is_open())
    {
        std::cerr<<"fichier non lue lors de la sauvegarde.";
        exit(1);
    }
    f<< getProf() << " " << getFils().size() << std::endl
     << getNbrV() << " " << getNbrR() << std::endl<<"0"<<std::endl;
    for(auto fi : getFils()){
        fi->saveFils(f);
    }
}

void Noeud::saveFils(std::ofstream &f){
    f<< getProf() << " " << getFils().size() << std::endl
     << getNbrV() << " " << getNbrR() << std::endl
     << getActions().size() << " ";
    for(auto ac : getActions()){
        switch(ac.getFaire()){
        case typeAction::ATTAQUER :
            f<<"a ";
            break;
        case typeAction::DEPLACER :
            f<<"d ";
            break;
        default:
            f <<"X ";
            std::cerr<<"deplacement non reconnu remplacement par X dans l'arbre"<<std::endl;
            break;
        }
        f<< ac.getSrc()<<" "<<ac.getDest() <<" ";
    }
    f<<std::endl;
    for(auto fi : getFils()){
        fi->saveFils(f);
    }
}

Noeud *Noeud::getPere() const
{
    return _pere;
}

void Noeud::setPere(Noeud *pere)
{
    _pere = pere;
}

void Noeud::load(){
    std::string cheminBase = "../FullMetalWar";
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
    std::cout<<"carte chargé : "<<chemin<<std::endl;
    std::ifstream f(chemin,std::ios::in);
    if(!f.is_open()){
        std::cout << "fichier non trouvé" << std::endl;
        std::cout << __FILE__ << std::endl;
        std::ofstream ft(chemin.c_str(), std::ios::out | std::ios::trunc );
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
    int nbrA;
    f  >> _prof>> nbrFils;
    f >> _nbr_valeur >> _nbr_recherche;
    f >> nbrA;
    for(int i =0;i<nbrFils;i++){
        AjouterFils(f);

    }


}

void Noeud::AjouterFils(std::ifstream &f){
    int nbrFils = 0;
    int prof = 0;
    int nbr_valeur,nbr_recherche;
    std::string ligneAction;
    f >> prof >> nbrFils;
    //std::cerr<<"ligne 1 : "<<prof<< "   " << nbrFils <<std::endl;
    f >> nbr_valeur >> nbr_recherche;
    //std::cerr<<"ligne 2 : "<<nbr_valeur<< "   " << nbr_recherche <<std::endl;
    std::vector<Action> ListeC = trad(f);
    auto nouv = new Noeud(ListeC,this);
    nouv->setNbrR(nbr_recherche);
    nouv->setNbrV(nbr_valeur);
    //   _fils.push_back(nouv);
    for(int i = 0;i<nbrFils;i++){
        nouv->AjouterFils(f);
    }

}

void Noeud::toLatek(){}

std::vector<Action> Noeud::trad(std::ifstream &f){
    std::vector<Action> tmp;
    int nbrA = 0;
    char faire;
    int src,dest;
    f>>nbrA;
    while (nbrA>0){
        f >> faire >> src >> dest;
        //std::cerr<<"ligne 3 : "<<faire<<" "<<src<<" "<<dest<<std::endl;
        Action tmpA;
        switch (faire) {
        case 'd':
            tmpA.setSrc(src);tmpA.setDest(dest);
            break;
        case 'a':
            tmpA.setFaire(typeAction::ATTAQUER);tmpA.setSrc(src);tmpA.setDest(dest);
            break;
        default:
            std::cerr<<"erreur : mauvais caractère : "<<faire<<std::endl;
        }
        tmp.push_back(tmpA);
        nbrA--;
    }
    return tmp;
}

int Noeud::getProf() const
{
    return _prof;
}

void Noeud::setProf(int prof)
{
    _prof = prof;
}

std::vector<Action> Noeud::getActions() const
{
    return _Actions;
}

void Noeud::setActions(const std::vector<Action> &Actions)
{
    _Actions = Actions;
}

