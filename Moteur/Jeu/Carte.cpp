#include "Carte.h"

using namespace std;

int nb_mer;

/*
 * Génère un nombre entre 1 et 100 et le renvoie
 */
int randNombre100() {
    return rand()%100+1;
}

/*
 *	Génère un CASEMAP en fonction des probabilités en pourcentage passées en paramètre,
 *	par défaut VIDE est renvoyé.
 */
CaseMap randCaseMap(int p_plaine, int p_montagne, int p_mer, int p_marais, int p_recif) {

    int tmp = randNombre100(); // On génère un nombre aléatoire en 1 et 100

    if(p_plaine+p_montagne+p_mer+p_marais+p_recif == 100) {
        if( (tmp > 0) && (tmp <= p_plaine) ){
            return CaseMap(TYPECASE::PLAINE);
        }

        if( (tmp > p_plaine) && (tmp <= p_plaine+p_montagne) ){
            return CaseMap(TYPECASE::MONTAGNE);
        }

        if( (tmp > p_plaine+p_montagne) && (tmp <= p_plaine+p_montagne+p_mer) ){
            nb_mer++;
            return CaseMap(TYPECASE::MER);
        }

        if( (tmp > p_plaine+p_montagne+p_mer) && (tmp <= p_plaine+p_montagne+p_mer+p_marais) ){
            return CaseMap(TYPECASE::MARAIS);
        }

        if( (tmp > p_plaine+p_montagne+p_mer+p_marais) && (tmp <= p_plaine+p_montagne+p_mer+p_marais+p_recif) ){
            return CaseMap(TYPECASE::RECIF);
        }
    }

    return CaseMap(TYPECASE::VIDE); // Cas où les probabilités entrées pour les types de cases sont fausses ( càd : != 100% )
}

/*
 * Constructeur de la Carte, il génère une carte et vérifie qu'elle correspond bien aux contraintes imposées,
 * sinon en regénère une nouvelle map et ce, jusqu'à ce que les contraintes soient respectées et enfin dessine
 * le résultat.
 */
Carte::Carte(int longueur, int largeur):
    m_longueur(longueur),
    m_largeur(largeur),
    m_taille(longueur*largeur),
    m_cases()
{
    int nb_test = 0; // Compteur d'appel à generationProcedurale()

    float percent_mer = 0; // Pourcentage de mer sur la map
    bool running = true;

    nb_mer = 0;



    while(running){

        m_cases.clear();
        generationProcedurale();
        nb_test++;

        percent_mer = (nb_mer*100)/m_taille;

        if((percent_mer>=30) && (percent_mer<=40))
            running = false;
        else {
            nb_mer = 0;
            percent_mer = 0;
        } // END ELSE

    } // END WHILE

    cout << "Nombre de générations de la carte : " << nb_test << endl;

}

Carte::Carte(int & longueur, int & largeur, TypeCarte type):
    m_longueur(longueur),
    m_largeur(largeur),
    m_taille(longueur*largeur),
    m_cases(),
    _type(type)
{
    int nb_test = 0; // Compteur d'appel à generationProcedurale()

    float percent_mer = 0; // Pourcentage de mer sur la map
    bool running = true;

    nb_mer = 0;



    while(running){

        m_cases.clear();
        switch(type) {
            case TypeCarte::RANDOM:
                generationProcedurale();
                nb_test++;

                percent_mer = (nb_mer*100)/m_taille;

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
                generationStochastique(largeur,longueur);
                m_largeur = largeur;
                m_longueur = longueur;
                m_taille = largeur*longueur;
                std::cout<<m_taille<< " " <<m_largeur << " " << m_longueur<<std::endl;
                running = false;
                nb_test++;
                break;
            default:
                exit(1);
            break;


        } // END switch

    } // END WHILE

    cout << "Nombre de générations de la carte : " << nb_test << endl;

}



Carte::~Carte(){ }

CaseMap& Carte::getCase(int x, int y){
    return m_cases.at(m_longueur * y+ x); } // problème de sigarbt pour le passage au second joueur, sur un call en parametre 5*5+4 il vas chercher la valeur hors du tableau
CaseMap& Carte::getCase(int i){ return m_cases[i]; }

//const CaseMap &Carte::getCase(int i) const { return m_cases[i]; }

//const CaseMap &Carte::getCase(int x, int y) const { return m_cases.at(m_longueur * y + x); }

//const CaseMap &Carte::getCase(const std::pair<int, int> &c) const { return m_cases.at(m_longueur * c.second + c.first); }

std::vector<std::pair<int, int> > Carte::voisins(std::pair<int, int> source) const{
    std::vector<std::pair<int,int>> voisin;
    if(!(source.second%2)){
//        std::cout << "\npair\n";
        if(isCaseExistante(std::pair<int,int>(source.first-1 , source.second+1 ))){
            voisin.push_back(std::pair<int,int>(source.first-1 , source.second+1 ));
        }
        if(isCaseExistante(std::pair<int,int>(source.first-1 , source.second ))){
            voisin.push_back(std::pair<int,int>(source.first-1 , source.second   ));
        }
        if(isCaseExistante(std::pair<int,int>(source.first-1 , source.second-1 ))){
            voisin.push_back(std::pair<int,int>(source.first-1 , source.second-1 ));
        }
        if(isCaseExistante(std::pair<int,int>(source.first , source.second+1 ))){
            voisin.push_back(std::pair<int,int>(source.first   , source.second+1 ));
        }
        if(isCaseExistante(std::pair<int,int>(source.first , source.second-1 ))){
            voisin.push_back(std::pair<int,int>(source.first   , source.second-1 ));
        }
        if(isCaseExistante(std::pair<int,int>(source.first+1 , source.second ))){
            voisin.push_back(std::pair<int,int>(source.first+1 , source.second   ));
        }
    }else{
//        std::cout << "\nimpair\n";
        if(isCaseExistante(std::pair<int,int>(source.first , source.second+1 ))){
            voisin.push_back(std::pair<int,int>(source.first   , source.second+1));
        }
        if(isCaseExistante(std::pair<int,int>(source.first-1 , source.second ))){
            voisin.push_back(std::pair<int,int>(source.first-1 , source.second));
        }
        if(isCaseExistante(std::pair<int,int>(source.first , source.second-1 ))){
            voisin.push_back(std::pair<int,int>(source.first   , source.second-1));
        }
        if(isCaseExistante(std::pair<int,int>(source.first+1 , source.second+1 ))){
            voisin.push_back(std::pair<int,int>(source.first+1 , source.second+1));
        }
        if(isCaseExistante(std::pair<int,int>(source.first+1 , source.second ))){
            voisin.push_back(std::pair<int,int>(source.first+1 , source.second));
        }
        if(isCaseExistante(std::pair<int,int>(source.first+1 , source.second-1 ))){
            voisin.push_back(std::pair<int,int>(source.first+1 , source.second-1));
        }
    }
    return voisin;
}

bool Carte::isCaseExistante(int x, int y) const{return (x>=0 && y>=0) && (x<m_longueur && y< m_largeur);}

bool Carte::isCaseExistante(std::pair<int, int> c) const{
    return (c.first>=0 && c.second>=0) && (c.first<m_longueur && c.second< m_largeur);
}

bool Carte::isCaseTerreEtMontagne(int x, int y) const {return isCaseExistante(x,y)?(( m_cases[m_longueur * y + x].getType() == TYPECASE::PLAINE || m_cases.at(m_longueur * y + x).getType() == TYPECASE::MARAIS || m_cases.at(m_longueur * y + x).getType() == TYPECASE::MONTAGNE )):false;}

bool Carte::isCaseTerreSansMontagne(int x, int y) const { return isCaseExistante(x,y)?(( m_cases.at(m_longueur * y + x).getType() == TYPECASE::PLAINE || m_cases.at(m_longueur * y + x).getType() == TYPECASE::MARAIS )) : false;}

bool Carte::isCaseEau(int x, int y) const { return isCaseExistante(x,y)?(( m_cases.at(m_longueur * y + x).getType() == TYPECASE::MER || m_cases.at(m_longueur * y + x).getType() == TYPECASE::RECIF )):false;}

int Carte::getLongueur() const { return m_longueur; }

int Carte::getLargeur() const  { return m_largeur; }

int Carte::getTaille() const { return m_taille; }

std::string Carte::toString() const {
    std::ostringstream oss;
    oss << "Carte Pointeur: " << this << std::endl;
    for(std::vector<CaseMap>::const_iterator i = m_cases.cbegin(); i != m_cases.cend(); i++)
        oss << (*i).toString() << std::endl;
    return oss.str();
}

std::vector<CaseMap> Carte::getListe() const { return m_cases; }

/*
 * Permet de génèrer le plateau de jeu en fonction des régles créées.
 * Les règles sont lues dans un fichier texte et stockées dans une classe prévue
 * à cet effet.
 */
void Carte::generationProcedurale(){

    srand(time(NULL));

    //Première case
    m_cases.push_back(TYPECASE::PLAINE);

    int i,ligne,colonne;

    for(i=1; i<m_taille; i++) {

        // On convertit pour avoir les coordonnées "matriciel"
        ligne = i / m_longueur;
        colonne = i - ligne*m_longueur;

        // Pour la 1ère colonne de la carte
        if(colonne==0) {

            m_cases.push_back(randCaseMap(m_regles.getRegle(m_cases[i-m_longueur].getType(),TYPECASE::PLAINE),
                                          m_regles.getRegle(m_cases[i-m_longueur].getType(),TYPECASE::MONTAGNE),
                                          m_regles.getRegle(m_cases[i-m_longueur].getType(),TYPECASE::MER),
                                          m_regles.getRegle(m_cases[i-m_longueur].getType(),TYPECASE::MARAIS),
                                          m_regles.getRegle(m_cases[i-m_longueur].getType(),TYPECASE::RECIF)));
        }

        else {

            // Pour la 1ère ligne de la carte
            if(ligne==0) {

                m_cases.push_back(randCaseMap(m_regles.getRegle(m_cases[i-1].getType(),TYPECASE::PLAINE),
                                              m_regles.getRegle(m_cases[i-1].getType(),TYPECASE::MONTAGNE),
                                              m_regles.getRegle(m_cases[i-1].getType(),TYPECASE::MER),
                                              m_regles.getRegle(m_cases[i-1].getType(),TYPECASE::MARAIS),
                                              m_regles.getRegle(m_cases[i-1].getType(),TYPECASE::RECIF)));

            } // END IF

            //Pour le reste des cases de la carte
            else {

                m_cases.push_back(randCaseMap(m_regles.getRegle(m_cases[i-1].getType(),m_cases[i-m_longueur].getType(),TYPECASE::PLAINE),
                                              m_regles.getRegle(m_cases[i-1].getType(),m_cases[i-m_longueur].getType(),TYPECASE::MONTAGNE),
                                              m_regles.getRegle(m_cases[i-1].getType(),m_cases[i-m_longueur].getType(),TYPECASE::MER),
                                              m_regles.getRegle(m_cases[i-1].getType(),m_cases[i-m_longueur].getType(),TYPECASE::MARAIS),
                                              m_regles.getRegle(m_cases[i-1].getType(),m_cases[i-m_longueur].getType(),TYPECASE::RECIF)));

            } // END ELSE

        } // END ELSE

    } // END FOR
}

void Carte::generationPlaine(){

    m_cases.push_back(TYPECASE::PLAINE);

    for(int i=1; i<m_taille; i++) {

        // On convertit pour avoir les coordonnées "matriciel"
        int ligne = i / m_longueur;
        int colonne = i - ligne*m_largeur;

        // Pour la 1ère colonne de la carte
        if(colonne==0) {

            m_cases.push_back(TYPECASE::PLAINE);

        }

        else {

            // Pour la 1ère ligne de la carte
            if(ligne==0) {

                m_cases.push_back(TYPECASE::PLAINE);


            } // END IF

            //Pour le reste des cases de la carte
            else {

                m_cases.push_back(TYPECASE::PLAINE);

            } // END ELSE

        } // END ELSE

    } // END FOR

}

void Carte::generationMer(){
    m_cases.push_back(TYPECASE::MER);

    for(int i=1; i<m_taille; i++) {

        // On convertit pour avoir les coordonnées "matriciel"
        int ligne = i / m_longueur;
        int colonne = i - ligne*m_largeur;

        // Pour la 1ère colonne de la carte
        if(colonne==0) {

            m_cases.push_back(TYPECASE::MER);

        }

        else {

            // Pour la 1ère ligne de la carte
            if(ligne==0) {

                m_cases.push_back(TYPECASE::MER);


            } // END IF

            //Pour le reste des cases de la carte
            else {

                m_cases.push_back(TYPECASE::MER);

            } // END ELSE

        } // END ELSE

    } // END FOR
}

void Carte::generationStochastique(int &largeur, int &longueur){
    std::ifstream f("stocha.dat",std::ios::in);
    if(!f.is_open())
        {std::cout<<"erreur de lecture fichier"<<std::endl;
         exit(1);}
    string line;
    f >> longueur >> largeur;
    std::cout<<longueur<<std::endl;
    f >> line;
    std::cout<<line<<std::endl;
    std::cout<<"test"<<std::endl;
    int ligne = 0;
    do
        {
            std::cout<<line<<std::endl;
            for(int i=0;i<longueur;i++){
                switch(line[i]){
                    case '0' :
                        m_cases.push_back(TYPECASE::PLAINE);
                        break;
                    case '1' :
                        m_cases.push_back(TYPECASE::MONTAGNE);
                        break;
                    case '2' :
                        m_cases.push_back(TYPECASE::MARAIS);
                        break;
                    case '3' :
                        m_cases.push_back(TYPECASE::MER);
                        break;
                    case '4' :
                        m_cases.push_back(TYPECASE::RECIF);
                        break;
                    default:
                        std::cout<<"erreur"<<std::endl;
                        break;


                    }

                }
            f >> line;
            ligne++;
    }while(ligne<=largeur);
}
