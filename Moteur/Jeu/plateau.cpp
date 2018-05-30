#include "plateau.h"



Case::Case(const typeCase type)
    : _type(type),
      _piece(nullptr)
{}

Case::Case(const Case &c)
    : _type(c._type),
      _piece(c._piece==nullptr? nullptr : c._piece->clone())
{}

bool Case::hasPiece(){
    return _piece != nullptr;
}

Piece *Case::getPiece(){
    return _piece;
}

typeCase Case::getType() const {
    return _type;
}

void Case::setPiece(Piece *p){
    _piece=p;
}

void Case::setType(typeCase t){
    _type=t;
}

std::string Case::toString() const{
    std::ostringstream oss;
    std::string type;
    oss << "Case de type ";
    switch (_type) {
    case typeCase::MER:       type = "MER";       break;
    case typeCase::PLAINE:    type = "PLAINE";    break;
    case typeCase::MONTAGNE:  type = "MONTAGNE";  break;
    case typeCase::RECIF:     type = "RECIF";     break;
    case typeCase::MARAIS:    type = "MARAIS";    break;
    default:        type = "VIDE";   break;
    }
    oss << type;
    //        if(m_piece != 0){
    //            oss << " avec une pièce " << m_piece->toString();
    //        }
    return oss.str();
}

int randNombre100() {
    return rand()%100+1;
}

int nb_mer; //??? faut pas me demander pourquoi...

Case randCase(int p_plaine, int p_montagne, int p_mer, int p_marais, int p_recif) {

    int tmp = randNombre100(); // On génère un nombre aléatoire en 1 et 100

    if(p_plaine+p_montagne+p_mer+p_marais+p_recif == 100) {
        if( (tmp > 0) && (tmp <= p_plaine) ){
            return Case(typeCase::PLAINE);
        }

        if( (tmp > p_plaine) && (tmp <= p_plaine+p_montagne) ){
            return Case(typeCase::MONTAGNE);
        }

        if( (tmp > p_plaine+p_montagne) && (tmp <= p_plaine+p_montagne+p_mer) ){
            nb_mer++;
            return Case(typeCase::MER);
        }

        if( (tmp > p_plaine+p_montagne+p_mer) && (tmp <= p_plaine+p_montagne+p_mer+p_marais) ){
            return Case(typeCase::MARAIS);
        }

        if( (tmp > p_plaine+p_montagne+p_mer+p_marais) && (tmp <= p_plaine+p_montagne+p_mer+p_marais+p_recif) ){
            return Case(typeCase::RECIF);
        }
    }

    return Case(typeCase::VIDE); // Cas où les probabilités entrées pour les types de cases sont fausses ( càd : != 100% )
}

Plateau::Plateau(int xPlateau, int yPlateau, TypeCarte typePlateau, int repartitionRessources, Couleur cj1, Couleur cj2)
    : _x(xPlateau),
      _y(yPlateau),
      _type(typePlateau),
      _couleurj1(cj1),
      _couleurj2(cj2),
      _joueurCourant(true)
{
    UNUSED(repartitionRessources);

    int nb_test = 0; // Compteur d'appel à generationProcedurale()

    float percent_mer = 0; // Pourcentage de mer sur la map
    bool running = true;

    nb_mer = 0;

    while(running){

        _cases.clear();
        switch(typePlateau) {
        case TypeCarte::RANDOM:
            generationProcedurale();
            nb_test++;

            percent_mer = (nb_mer*100)/(_x*_y);

            if((percent_mer>=30) && (percent_mer<=40))
                running = false;
            else {
                nb_mer = 0;
                percent_mer = 0;
            }
            break;

        case TypeCarte::PLAINES:
            generationPlaine();
            running = false;
            break;
        case TypeCarte::MERS:
            generationMer();
            running =false;
            break;

        case TypeCarte::STOCHASTIQUE:
            generationStochastique(_y,_x);
            running = false;
            nb_test++;
            break;
        default:
            exit(1);
            break;


        } // END switch

    } // END WHILE

    std::cout << "\nNombre de générations de la carte : " << nb_test << std::endl;

}

Plateau::Plateau(const Plateau &p)
    : _x(p._x),
      _y(p._y),
      _type(p._type),
      _cases(p._cases),
      _regles(p._regles),
      _couleurj1(p._couleurj1),
      _couleurj2(p._couleurj2),
      _joueurCourant(p._joueurCourant),
      _coups(p._coups)
{
    for(auto pi : p._cimetiere){
        _cimetiere.push_back(pi->clone());
    }
}

void Plateau::generationProcedurale(){

    srand(time(NULL));

    //Première case
    _cases.push_back(typeCase::PLAINE);

    int i,ligne,colonne;

    for(i=1; i<_x*_y; i++) {

        // On convertit pour avoir les coordonnées "matriciel"
        ligne = i / _x;
        colonne = i - ligne*_x;

        // Pour la 1ère colonne de la carte
        if(colonne==0) {

            _cases.push_back(randCase(_regles.getRegle(_cases[i-_x].getType(),typeCase::PLAINE),
                             _regles.getRegle(_cases[i-_x].getType(),typeCase::MONTAGNE),
                    _regles.getRegle(_cases[i-_x].getType(),typeCase::MER),
                    _regles.getRegle(_cases[i-_x].getType(),typeCase::MARAIS),
                    _regles.getRegle(_cases[i-_x].getType(),typeCase::RECIF)));
        }

        else {

            // Pour la 1ère ligne de la carte
            if(ligne==0) {

                _cases.push_back(randCase(_regles.getRegle(_cases[i-1].getType(),typeCase::PLAINE),
                                 _regles.getRegle(_cases[i-1].getType(),typeCase::MONTAGNE),
                        _regles.getRegle(_cases[i-1].getType(),typeCase::MER),
                        _regles.getRegle(_cases[i-1].getType(),typeCase::MARAIS),
                        _regles.getRegle(_cases[i-1].getType(),typeCase::RECIF)));

            } // END IF

            //Pour le reste des cases de la carte
            else {

                _cases.push_back(randCase(_regles.getRegle(_cases[i-1].getType(),_cases[i-_x].getType(),typeCase::PLAINE),
                        _regles.getRegle(_cases[i-1].getType(),_cases[i-_x].getType(),typeCase::MONTAGNE),
                        _regles.getRegle(_cases[i-1].getType(),_cases[i-_x].getType(),typeCase::MER),
                        _regles.getRegle(_cases[i-1].getType(),_cases[i-_x].getType(),typeCase::MARAIS),
                        _regles.getRegle(_cases[i-1].getType(),_cases[i-_x].getType(),typeCase::RECIF)));

            } // END ELSE

        } // END ELSE

    } // END FOR
}

void Plateau::generationPlaine(){

    _cases.push_back(typeCase::PLAINE);

    for(int i=1; i<_x*_y; i++) {

        // On convertit pour avoir les coordonnées "matriciel"
        int ligne = i / _x;
        int colonne = i - ligne*_y;

        // Pour la 1ère colonne de la carte
        if(colonne==0) {

            _cases.push_back(typeCase::PLAINE);

        }

        else {

            // Pour la 1ère ligne de la carte
            if(ligne==0) {

                _cases.push_back(typeCase::PLAINE);


            } // END IF

            //Pour le reste des cases de la carte
            else {

                _cases.push_back(typeCase::PLAINE);

            } // END ELSE

        } // END ELSE

    } // END FOR

}

void Plateau::generationMer(){
    _cases.push_back(typeCase::MER);

    for(int i=1; i<_x*_y; i++) {

        // On convertit pour avoir les coordonnées "matriciel"
        int ligne = i / _x;
        int colonne = i - ligne*_y;

        // Pour la 1ère colonne de la carte
        if(colonne==0) {

            _cases.push_back(typeCase::MER);

        }

        else {

            // Pour la 1ère ligne de la carte
            if(ligne==0) {

                _cases.push_back(typeCase::MER);


            } // END IF

            //Pour le reste des cases de la carte
            else {

                _cases.push_back(typeCase::MER);

            } // END ELSE

        } // END ELSE

    } // END FOR
}

void Plateau::generationStochastique(int &largeur, int &longueur){
    std::ifstream f("../FullMetalWar/Moteur/Jeu/stocha.dat",std::ios::in);
    std::cout<<__FILE__<<std::endl;
    if(!f.is_open()){
        std::cout<<"erreur de lecture fichier"<<std::endl;
        exit(1);
    }
    std::string line;
    f >> longueur >> largeur;
    //    std::cout<<longueur<<std::endl;
    f >> line;
    //    std::cout<<line<<std::endl;
    //    std::cout<<"test"<<std::endl;
    int ligne = 0;
    do
    {
        //        std::cout<<line<<std::endl;
        for(int i=0;i<longueur;i++){
            switch(line[i]){
            case '0' :
                _cases.push_back(typeCase::PLAINE);
                break;
            case '1' :
                _cases.push_back(typeCase::MONTAGNE);
                break;
            case '2' :
                _cases.push_back(typeCase::MARAIS);
                break;
            case '3' :
                _cases.push_back(typeCase::MER);
                break;
            case '4' :
                _cases.push_back(typeCase::RECIF);
                break;
            default:
                //                std::cout<<"erreur"<<std::endl;
                break;
            }

        }
        f >> line;
        ligne++;
    }while(ligne<=largeur);
}

Case &Plateau::getCase(int i){
    return _cases[i];
}

Case &Plateau::getCase(int x, int y){
    return _cases[_x*y +x];
}

Case &Plateau::getCase(Coordonnee c){
    return _cases[_x*c.y+c.x];
}

int Plateau::getTaille(){
    return _x*_y;
}

int Plateau::getLongueur(){
    return _x;
}

int Plateau::getLargeur(){
    return _y;
}

int Plateau::getX(){
    return _x;
}

int Plateau::getY(){
    return _y;
}

void Plateau::finDeTourJoueur(){
    _joueurCourant = ! _joueurCourant;
    checkPieces();
}

void Plateau::checkPieces(){
    for(auto & c : _cases){
        if(c.getPiece()!=nullptr)
            c.getPiece()->maj();
    }
}

void Plateau::inverseJoueur(){
    _joueurCourant=!_joueurCourant;
}

bool Plateau::creationPiece(Coordonnee c, typePiece p, Couleur couleur){
    if(getCase(c).hasPiece()){
        return false;
    }
    Piece * piece;
    switch (p) {
    case typePiece::CHAR:
        piece = new Char(couleur);
        break;
    case typePiece::GROS_TAS:
        piece = new GrosTas(couleur);
        break;
    case typePiece::VEDETTE:
        piece = new Vedette(couleur);
        break;
    case typePiece::MINERAI:
        piece = new Minerai(couleur);
        break;
    case typePiece::BARGE:
        piece = new Barge(couleur);
        break;
    case typePiece::BASE:
        piece = new Base(couleur);
        break;
    case typePiece::CRABE:
        piece = new Crabe(couleur);
        break;
    case typePiece::PONDEUSE:
        piece = new Pondeuse(couleur);
        break;
    default:
        break;
    }
    getCase(c).setPiece(piece);
    return true;
}

bool Plateau::isCaseExistante(Coordonnee c) const{
    return ((c.x>=0 && c.y>=0) && (c.x<_x && c.y<_y));
}

std::vector<Coordonnee> Plateau::voisins(Coordonnee source) const{
    std::vector<Coordonnee> voisin;
    if(!(source.y%2)){
        if(isCaseExistante(Coordonnee(source.x-1 , source.y+1 ))){
            voisin.push_back(Coordonnee(source.x-1 , source.y+1 ));
        }
        if(isCaseExistante(Coordonnee(source.x-1 , source.y ))){
            voisin.push_back(Coordonnee(source.x-1 , source.y   ));
        }
        if(isCaseExistante(Coordonnee(source.x-1 , source.y-1 ))){
            voisin.push_back(Coordonnee(source.x-1 , source.y-1 ));
        }
        if(isCaseExistante(Coordonnee(source.x , source.y+1 ))){
            voisin.push_back(Coordonnee(source.x   , source.y+1 ));
        }
        if(isCaseExistante(Coordonnee(source.x , source.y-1 ))){
            voisin.push_back(Coordonnee(source.x   , source.y-1 ));
        }
        if(isCaseExistante(Coordonnee(source.x+1 , source.y ))){
            voisin.push_back(Coordonnee(source.x+1 , source.y   ));
        }
    }else{
        if(isCaseExistante(Coordonnee(source.x , source.y+1 ))){
            voisin.push_back(Coordonnee(source.x   , source.y+1));
        }
        if(isCaseExistante(Coordonnee(source.x-1 , source.y ))){
            voisin.push_back(Coordonnee(source.x-1 , source.y));
        }
        if(isCaseExistante(Coordonnee(source.x , source.y-1 ))){
            voisin.push_back(Coordonnee(source.x   , source.y-1));
        }
        if(isCaseExistante(Coordonnee(source.x+1 , source.y+1 ))){
            voisin.push_back(Coordonnee(source.x+1 , source.y+1));
        }
        if(isCaseExistante(Coordonnee(source.x+1 , source.y ))){
            voisin.push_back(Coordonnee(source.x+1 , source.y));
        }
        if(isCaseExistante(Coordonnee(source.x+1 , source.y-1 ))){
            voisin.push_back(Coordonnee(source.x+1 , source.y-1));
        }
    }
    return voisin;
}

coups Plateau::coupsPossibles(){
    coups actions;
    for(int x=0 ; x<_x ; x++){
        for(int y = 0 ; y<_y ; y++){
            Piece * p = getCase(x,y).getPiece();
            if(p!= nullptr){
                if(p->getCouleur() == (_joueurCourant? _couleurj1 : _couleurj2)){
                    if(dynamic_cast<Destructeur *>(p)){
                        if(dynamic_cast<Destructeur *>(p)->pretATirer()){
                            coups proches(aPortee(Coordonnee(x,y)));
                            actions.insert(actions.end(),proches.begin(),proches.end());
                        }
                    }
                    for(auto v : voisins(Coordonnee(x,y))){
                        if((!getCase(v).hasPiece()) && (p->_deplacement->accessible(getCase(v).getType()))){
                            actions.push_back(coup (Coordonnee(x,y),Coordonnee(v),typeAction::DEPLACER));
                        }
                    }
                }
            }
        }
    }
    return actions;
}

bool Plateau::fin(){
    for(int i(0) ; i < _x*_y ; i++){
        if(getCase(i).getPiece()!=nullptr)
            return false;
    }
    return true;
}

int Plateau::eval(){
    //evaluation vis a vis du joueur 1
    Piece * p;
    int score(0);
    for(int i(0) ; i < _x*_y ; i++){
        p = getCase(i).getPiece();
        if(p!=nullptr){
            score+= p->getPointDeVie()*(p->getCouleur()==_couleurj1? 5 : -5 );
        }
    }
    return score;
}

void Plateau::annulerCoups(int n){
    for(int i(0); i<n ; i++)
        annulerCoup();
}

void Plateau::annulerCoup(){
    if(!_coups.empty()){
        coup c (_coups.back());
        _coups.pop_back();
        Piece * src (getCase(c.src).getPiece());
        Piece * dst (getCase(c.dst).getPiece());
        Destructeur * d(nullptr);

        if(src==nullptr&& dst==nullptr){
            std::cout << "\nerreur coup a annuler\n";
        }
        else{
            switch (c.action) {
            case typeAction::DEPLACER:
                getCase(c.src).setPiece(dst);
                getCase(c.dst).setPiece(nullptr);
                break;
            case typeAction::ATTAQUER:
                if(dst==nullptr){
                    getCase(c.dst).setPiece(_cimetiere.back());
                    _cimetiere.pop_back();
                    dst = getCase(c.dst).getPiece();
                }
                dst->soin();
                d = dynamic_cast<Destructeur *> (src);
                d->rechargement();
                break;
            default:
                std::cout<<"\nerreur annuler coup";
                break;
            }
        }
    }
}

coups Plateau::aPortee(const Coordonnee &c){
    coups proches;
    Destructeur * d = dynamic_cast<Destructeur *>( getCase(c).getPiece());
    std::vector<triplet> dejaVu;
    std::vector<triplet> pile;
    triplet t;
    Piece * p = nullptr;
    coup a(c,c,typeAction::ATTAQUER);

    t.src=c;
    t.cout.cout=1;
    t.cout.manhattan=0;
    for(auto & v : voisins(c)){
        t.dst=v;
        pile.push_back(t);
    }

    triplet temp;
    while(!pile.empty()){
        temp= pile.back();
        pile.pop_back();
        if(std::find(dejaVu.begin(),dejaVu.end(),temp) == dejaVu.end()){
            dejaVu.push_back(temp);
            p=getCase(temp.dst).getPiece();
            if(p!=nullptr){
                if(p->getCouleur() != (_joueurCourant? _couleurj1 : _couleurj2) ){
                    a.dst=temp.dst;
                    proches.push_back(a);
                }
            }
            if(temp.cout.cout<d->distance()){
                t.cout.cout=temp.cout.cout+1;
                for(auto & v : voisins(temp.dst)){
                    t.dst=v;
                    pile.push_back(t);
                }
            }
        }
    }
    return proches;
}

bool Plateau::ordre(coup c){
    coups actions(coupsPossibles());
    if(std::find(std::begin(actions),std::end(actions), c) == std::end(actions)){
        return false;
    }
    jouerCoup(c);
    return true;
}

void Plateau::ordre(coups c){
    for(auto co : c)
        ordre(co);
}

bool Plateau::jouerCoups(coups l){
    for(auto c : l)
        if(!jouerCoup(c))
            return false;
    return true;
}

bool Plateau::jouerCoup(coup c){
    if(isCaseExistante(c.src) && isCaseExistante(c.dst) && ((c.action==typeAction::ATTAQUER) || (c.action==typeAction::DEPLACER))){

        Piece * src = getCase(c.src).getPiece();
        Piece * dst = getCase(c.dst).getPiece();
        Destructeur * d(nullptr);
        if(src!=nullptr){
            switch (c.action) {
            case typeAction::DEPLACER:
                if(dst==nullptr && src!=nullptr){
                    getCase(c.src).setPiece(nullptr);
                    getCase(c.dst).setPiece(src);
                    _coups.push_back(c);
                    return true;
                }else{
                    std::cout << "\nerreur sur le coup a jouer déplacement";
                    return false;
                }
                break;
            case typeAction::ATTAQUER:
                d = dynamic_cast<Destructeur *> (src);
                if(d != nullptr && dst!=nullptr){
                    if(d->pretATirer()){
                        d->tire();
                        dst->prendDesDegats();
                        _coups.push_back(c);
                        if(dst->getPointDeVie()<=0){
                            getCase(c.dst).setPiece(nullptr);
                            _cimetiere.push_back(dst);
//                            std::cout<<"\nune piece est KO\n";
                        }
                        return true;
                    }else{
                        std::cout << "\nerreur sur le coup a jouer pas de munition";
                        return false;
                    }
                }else{
                    std::cout << "\nerreur sur le coup a jouer attaque";
                    return false;
                }
                break;
            default:
                return false;
                break;
            }
        }else{
            std::cout << "\nerreur sur le coup a jouer src==nullptr";
            return false;
        }
    }else{
        std::cout << "\nerreur sur le coup a jouer case inexistante";
        return false;
    }

}



bool Plateau::getJoueurCourant() const
{
    return _joueurCourant;
}

void Plateau::setJoueurCourant(bool joueurCourant)
{
    _joueurCourant = joueurCourant;
}

coups Plateau::getnDerniersCoups(int n){
    coups l(_coups.end()-n, _coups.end());
    return l;
}

std::vector<Case> Plateau::getListe(){return _cases;}

TypeCarte Plateau::getType(){return _type;}
