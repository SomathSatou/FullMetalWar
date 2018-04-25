#include <mainwindow.h>
#include <QApplication>
#include "defineclass.h"
#include "Moteur/Jeu/arbrestochastique.h"

using namespace std;

int main(int argc, char *argv[])
{

//    QApplication a(argc, argv);

//    MainWindow w;
//    w.showFullScreen();
//    //w.showMaximized();

//    return a.exec();


    // test arbre
       int la = 5;
       int lo = 5;
       Carte Test(lo,la,TypeCarte::PLAINES);
       Noeud tmp(Test);

       return 0;


    /*
    Joueur * j1 = new Joueur("J1",Couleur::BLEU);
    Joueur * j2 = new Joueur("J2",Couleur::ROUGE);

    std::vector<Joueur *> lj;
    lj.push_back(j1);
    lj.push_back(j2);


    std::vector<std::pair<typePiece,int>> liste_pieces;
    liste_pieces.push_back(pair<typePiece,int>(typePiece::CHAR,4));


    int longueur = 20;

    int largeur = 20;

    Jeu j(lj, liste_pieces, TypeCarte::PLAINES , false , longueur, largeur );

    cout << j.toString();

    coordonnees s (1,1);
    coordonnees d (3,1);


    j.ordre(s,d);

    cout << j.toString();

    std::cout<< "\ncoucou\n";
    for(auto & v : j.getCarte().voisins(coordonnees(1,1))){
        std::cout<< "\nsommet " << v.first << " " << v.second;
    }
    std::cout<< "\ncoucou\n";
    for(auto & v : j.getCarte().voisins(coordonnees(6,6))){
        std::cout<< "\nsommet " << v.first << " " << v.second;
    }

    return 0;
*/
}
