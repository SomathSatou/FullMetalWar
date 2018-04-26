#include "Jeu.h"

Jeu::Jeu(std::vector<Joueur * > joueurs, std::vector<std::pair<typePiece, int> >& liste_pieces, int longueur, int largeur, int nombreToursMax, int repartitionRessource) :
    m_joueurs(joueurs),
    m_tourMax(nombreToursMax),
    m_carte(longueur, largeur),
    m_joueurCourant(0),
    m_tourCourrant(1)
{

    for(auto & j : m_joueurs){
        j->creationArmee(liste_pieces , &m_carte);
    }

    repartitionRessource = repartitionRessource +1;
    liste_pieces.clear();


    m_joueurs[0]->getArmee()[0]->setCoordonnee(coordonnees(1,1));
    m_joueurs[1]->getArmee()[0]->setCoordonnee(coordonnees(2,2));


    /*
        int x=2;
        int y=largeur/2-4;
        int s = 0;
        for(auto & j : m_joueurs ){
            s=1-s;
            int i = 0;
            for(auto & p : j->getArmee() ){
                p->setCoordonnee(coordonnees((s? x : largeur-x),y+i));
            }
        }
        */
}


Jeu::Jeu(std::vector<Joueur *> joueurs, std::vector<std::pair<typePiece,int>> &pieces,TypeCarte type,bool minerais, int &longueur, int &largeur, int nombreToursMax, int repartitionRessource):
    m_joueurs(joueurs),
    m_tourMax(nombreToursMax),
    m_carte(longueur, largeur,type),
    m_joueurCourant(0),
    m_tourCourrant(1)
{


    for(auto & j : m_joueurs){
        j->creationArmee(pieces , &m_carte);
    }

    //1
    Joueur * neutre = new Joueur("NEUTRE",Couleur::NEUTRE);
    m_joueurs.push_back(neutre);
    int indicePiece	 = 0;
    if(minerais){
        for(int i = 0; i < longueur; i++){
            for(int j = 0; j < largeur; j++){
                if( (i% repartitionRessource) == 0 ){
                    if( (j%repartitionRessource) == 0){
                        if((m_carte.getCase(i,j).getType() != TYPECASE::MER) && (m_carte.getCase(i,j).getType() != TYPECASE::MONTAGNE)){
                            Minerai * m = new Minerai(coordonnees(i,j),neutre->getCouleur(),neutre);
                            neutre->ajouterPiece(m);
                            m_carte.getCase(i,j).nouvellePiece(neutre->getArmee().at(indicePiece));
                            indicePiece++;
                        } // END IF
                    } // END IF
                } // END IF
            } // END IF
        } // END
    } // end if minerais
    //        std::cout<<"fin 1"<<std::endl;

    //        std::cout<< "**********************coucouc*******************"<<std::endl;

    std::cout << std::flush;
    for(unsigned int i = 0; i<m_joueurs.size()-1; i++){
        switch(i){
        case 0 :
            m_joueurs[0]->getArmee()[0]->setCoordonnee(coordonnees(0,0));
            m_carte.getCase(0,0).nouvellePiece(m_joueurs[i]->getArmee()[0]);
            break;
        case 1 :
            m_joueurs[1]->getArmee()[0]->setCoordonnee(coordonnees(longueur-1,largeur-1));
            m_carte.getCase(longueur-1,largeur-1).nouvellePiece(m_joueurs[i]->getArmee()[0]);
            break;
        case 2 :
            m_carte.getCase(longueur-1,0).nouvellePiece(m_joueurs[i]->getArmee()[0]);
            break;
        case 3 :
            m_carte.getCase(0,largeur-1).nouvellePiece(m_joueurs[i]->getArmee()[0]);
            break;
        }
    }

    //   //2
    //       for(std::vector<Joueur>::iterator i = m_joueurs.begin(); i != m_joueurs.end(); i++){
    //         if((*i).getCouleur() != NEUTRE){
    //             for(std::vector<std::pair<typePiece,int>>::const_iterator j = pieces.begin(); j != pieces.end(); j++){
    //               for(int k = 0; k < (*j).second; k++){
    //                 Piece * pointeur;
    //                 switch((*j).first){
    //                   case typePiece::PONTON:		pointeur = new Ponton(   &(*i) ); 	break;
    //                   case typePiece::CHAR: 		pointeur = new Char(     &(*i) );	break;
    //                   case typePiece::GROS_TAS: 	pointeur = new GrosTas(  &(*i) ); 	break;
    //                   case typePiece::BASE:       pointeur = new Astronef( &(*i) );	break;
    //                   case typePiece::VEDETTE:	pointeur = new Vedette(  &(*i) );	break;
    //                   case typePiece::CRABE:		pointeur = new Crabe(    &(*i) );	break;
    //                   case typePiece::PONDEUSE:	pointeur = new Pondeuse( &(*i) );	break;
    //                   case typePiece::BARGE:		pointeur = new Barge(    &(*i) );	break;
    //                   default: break;
    //                 }
    //                 (*i).ajouterPiece(pointeur);
    //               } // END FOR
    //             } // END FOR
    //         } // END IF
}

bool Jeu::ordre(const coordonnees &source, const coordonnees &objectif){

    Piece * p1 = m_joueurs[m_joueurCourant]->appartient(source);
    Piece * p2 = m_carte.getCase(objectif.first,objectif.second).getPiece();

    if(p1!=nullptr){

        if(p1->getJoueur() == m_joueurs[m_joueurCourant]){

            if(p2==nullptr){

                //std::cout << "\nordre de deplacement\n";
                int cout (p1->deplacement(objectif));

                if(cout!=-1){

                    if(m_joueurs[m_joueurCourant]->retirePA(cout)){
                        p1->setCoordonnee(objectif);
                        return true;
                    }
                }else
                    return false;

            }else{//si p2 est une piece
                if(p2->getCouleur()!=p1->getCouleur()){
                    if(m_joueurs[m_joueurCourant]->retirePA(1))
                        if(p1->attaque(objectif))
                    std::cout << "coucoul'attaque'";
                }
            }
        }
    }
    return false;
}

Jeu::~Jeu(){ m_joueurs.clear();}

Carte &Jeu::getCarte() { return m_carte; }

int Jeu::getJoueurCourrant() const { return m_joueurCourant; }

int Jeu::getTourCourrant() const{
    if(m_tourCourrant < m_tourMax)
        return m_tourCourrant;
    else return -1;
}

std::vector<Joueur *> Jeu::getListeJoueurs(){ return m_joueurs; }

Joueur *Jeu::getJoueur(int i){
    return m_joueurs[i];
}

std::string Jeu::toString() const{
    std::ostringstream oss;
    oss << "Jeu Pointeur :" << this << std::endl << "Les Joueurs" << std::endl;
    for(const auto & j : m_joueurs)
        oss<< j->toString();
    //oss << m_carte.toString() << std::endl;
    return oss.str();
}

void Jeu::finDeTourJoueur() {
    //m_joueurs[m_joueurCourrant].finDeTour();
    if((unsigned)m_joueurCourant == m_joueurs.size()-2){ // -2 car il y a le joueur NEUTRE dans la liste et qu'il ne compte pas
        m_joueurCourant = 0;
        m_tourCourrant++;
    }
    else
        m_joueurCourant ++;

    for(auto & j : m_joueurs){
        j->maj_nouveau_tour();
    }
}
