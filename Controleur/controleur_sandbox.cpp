#include "controleur_sandbox.h"

Controleur_Sandbox::Controleur_Sandbox(QObject *parent) :
    QObject(parent),
    _listeJoueurs(),
    _longueurMap(5),
    _largeurMap(5),
    _minerais(false)
{
    _listeJoueurs.push_back(new Joueur("Titi",Couleur::BLEU,true));
    _listeJoueurs.push_back(new Joueur("Jack",Couleur::ROUGE,false));

}

int Controleur_Sandbox::getLongueur() const { return _longueurMap; }

int Controleur_Sandbox::getLargeur() const { return _largeurMap; }

TypeCarte Controleur_Sandbox::getType() const { return _type; }

int Controleur_Sandbox::getMinerais() const { return _minerais; }

std::vector<std::pair<typePiece, int> > Controleur_Sandbox::getListePiece() const {return _listePiece;}

const std::vector<Joueur *> &Controleur_Sandbox::getListeJoueurs() const { return _listeJoueurs; }

/**********************************SLOTS******************************************/

void Controleur_Sandbox::setCouleur(int numero, int indexCouleur){
    switch(indexCouleur){
        case 0:
            _listeJoueurs[numero]->setCouleur(Couleur::BLEU);
            break;
        case 1:
            _listeJoueurs[numero]->setCouleur(Couleur::ROUGE);
            break;
        case 2:
            _listeJoueurs[numero]->setCouleur(Couleur::VERT);
            break;
        case 3:
            _listeJoueurs[numero]->setCouleur(Couleur::JAUNE);
            break;
    }

    emit sendEnableJouer(testInformation());
}

//void Controleur_Sandbox::addJoueur() {
//    _listeJoueurs.push_back(new Joueur("",Couleur::BLEU,true));
//    emit sendEnableJouer(false);
//}

//void Controleur_Sandbox::supprJoueur() {
//    _listeJoueurs.pop_back();
//    emit sendEnableJouer(testInformation());
//}

void Controleur_Sandbox::afficheListe(){
    std::cout<< "***********************debut de l'armé ************"<<std::endl;

    for(auto p : _listePiece){
        switch(p.first){
        case typePiece::CHAR:
            std::cout<<std::endl<<"Char = " << p.second <<std::endl<<std::endl;
            break;
        case typePiece::BARGE:
            std::cout<<std::endl<<"Barge = " << p.second <<std::endl<<std::endl;
            break;
        case typePiece::BASE:
            std::cout<<std::endl<<"BASE = " << p.second <<std::endl<<std::endl;
            break;
        case typePiece::PONDEUSE:
            std::cout<<std::endl<<"PONDEUSE = " << p.second <<std::endl<<std::endl;
            break;
        case typePiece::GROS_TAS:
            std::cout<<std::endl<<"GROS_TAS = " << p.second <<std::endl<<std::endl;
            break;
        case typePiece::VEDETTE:
            std::cout<<std::endl<<"VEDETTE = " << p.second <<std::endl<<std::endl;
            break;
        case typePiece::CRABE:
            std::cout<<std::endl<<"CRABE = " << p.second <<std::endl<<std::endl;
            break;
        default:
            std::cout<<std::endl<<"piece non gérer."<<std::endl;
            break;
        }
    }
}

void Controleur_Sandbox::setNom(int numero, const QString &nom){
    _listeJoueurs[numero]->setPseudonyme(nom.toStdString());
    emit sendEnableJouer(testInformation());
}

void Controleur_Sandbox::setLongueur(int longueur){
    _longueurMap = longueur;
}

void Controleur_Sandbox::setLargeur(int largeur){
    _largeurMap = largeur;
}

void Controleur_Sandbox::setType(int value){
    switch(value){
    case 1 :
        _type = TypeCarte::PLAINES;
        break;
    case 2 :
        _type = TypeCarte::MERS;
        break;
    case 3 :
        _type = TypeCarte::STOCHASTIQUE;
        break;
    default:
        _type = TypeCarte::RANDOM;
        break;
    }
}

void Controleur_Sandbox::setMinerais(int state){
    std::cout << state << std::endl;
    (state == 2)?_minerais=true:_minerais=false;
}


void Controleur_Sandbox::setPAturn(int numero, int value){
    _listeJoueurs[numero]->setNombrePADebut(value);
}


void Controleur_Sandbox::setPAmax(int numero, int value){
    _listeJoueurs[numero]->setNombrePAMax(value);
}

void Controleur_Sandbox::setTypeJoueur(int numero, int value){
    Joueur* J;
    switch(value){
        case 0 :
             J = new Joueur(_listeJoueurs[numero]->getPseudonyme(),_listeJoueurs[numero]->getCouleur(),_listeJoueurs[numero]->getJoueur());
            _listeJoueurs.erase(_listeJoueurs.begin()+numero);
            if (numero == 0){_listeJoueurs.insert(_listeJoueurs.begin(),J);}
            else{_listeJoueurs.push_back(J);}
            break;
        case 1 :
            J = new joueurStochastique(_listeJoueurs[numero]->getPseudonyme(),_listeJoueurs[numero]->getCouleur(),_listeJoueurs[numero]->getJoueur());
            _listeJoueurs.erase(_listeJoueurs.begin()+numero);
            if (numero == 0){_listeJoueurs.insert(_listeJoueurs.begin(),J);}
            else{_listeJoueurs.push_back(J);}
            break;
        case 2 :
            J = new JoueurAlphaBeta(_listeJoueurs[numero]->getPseudonyme(),_listeJoueurs[numero]->getCouleur(),_listeJoueurs[numero]->getJoueur());
            _listeJoueurs.erase(_listeJoueurs.begin()+numero);
            if (numero == 0){_listeJoueurs.insert(_listeJoueurs.begin(),J);}
            else{_listeJoueurs.push_back(J);}
            break;
    }
}

void Controleur_Sandbox::setChar(int x){
    bool update = false;
    for(auto &l : _listePiece){
        if (l.first == typePiece::CHAR){
            l.second = x;
            update = true;
        }
    }
    if (!update) {_listePiece.push_back(std::make_pair(typePiece::CHAR,x));}
    afficheListe();
}

void Controleur_Sandbox::setGrosTas(int x){
    bool update = false;
    for(auto &l : _listePiece){
        if (l.first == typePiece::GROS_TAS){
            l.second = x;
            update = true;
        }
    }
    if (!update) {_listePiece.push_back(std::make_pair(typePiece::GROS_TAS,x));}
    afficheListe();
}

void Controleur_Sandbox::setCrabe(int x){
    bool update = false;
    for(auto &l : _listePiece){
        if (l.first == typePiece::CRABE){
            l.second = x;
            update = true;
        }
    }
    if (!update) {_listePiece.push_back(std::make_pair(typePiece::CRABE,x));}
    afficheListe();
}

void Controleur_Sandbox::setPondeuse(int x){
    bool update = false;
    for(auto &l : _listePiece){
        if (l.first == typePiece::PONDEUSE){
            l.second = x;
            update = true;
        }
    }
    if (!update) {_listePiece.push_back(std::make_pair(typePiece::PONDEUSE,x));}
    afficheListe();
}

void Controleur_Sandbox::setBase(int x){
    bool update = false;
    for(auto &l : _listePiece){
        if (l.first == typePiece::BASE){
            l.second = x;
            update = true;
        }
    }
    if (!update) {_listePiece.push_back(std::make_pair(typePiece::BASE,x));}

    afficheListe();
}

void Controleur_Sandbox::setBarge(int x){
    bool update = false;
    for(auto &l : _listePiece){
        if (l.first == typePiece::BARGE){
            l.second = x;
            update = true;
        }
    }
    if (!update) {_listePiece.push_back(std::make_pair(typePiece::BARGE,x));}
}

void Controleur_Sandbox::setVedette(int x){
    bool update = false;
    for(auto &l : _listePiece){
        if (l.first == typePiece::VEDETTE){
            l.second = x;
            update = true;
        }
    }
    if (!update) {_listePiece.push_back(std::make_pair(typePiece::VEDETTE,x));}
    std::cout<<x<<std::endl;
    afficheListe();
}

bool Controleur_Sandbox::testInformation() const {
    for(std::vector<Joueur*>::const_iterator i = _listeJoueurs.cbegin(); i != _listeJoueurs.cend(); i++) {
        for(std::vector<Joueur*>::const_iterator j = i; j != _listeJoueurs.cend(); j++) {

            if(j != i) {
                QString j1 = (*i)->getPseudonyme().c_str();
                QString j2 = (*j)->getPseudonyme().c_str();

                bool testCouleur = (*i)->getCouleur() == (*j)->getCouleur();
                bool testPseudo = j1.toUpper().compare(j2.toUpper()) == 0;

                if(j1.isEmpty() || j2.isEmpty()) testPseudo = true;

                if(testCouleur || testPseudo) return false;
            }

        } // END FOR

    } // END FOR

    return true;
}



