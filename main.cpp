#include <mainwindow.h>
#include <QApplication>
#include "defineclass.h"

using namespace std;

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        MainWindow w;
        w.showFullScreen();
        //w.showMaximized();
        //w.showMinimized();
        return a.exec();


    //    std::vector<std::pair<typePiece,int>> P;
    //    P.push_back(std::pair<typePiece,int>(typePiece::CHAR,1));

    //    Jeu j (new JoueurAlphaBeta("Joueur 1",Couleur::JAUNE),new JoueurAlphaBeta("Joueur 2",Couleur::ROUGE),P,5,5,TypeCarte::PLAINES,0);

    //    j.getJoueurCourantPtr()->jouer(j.getPlateau());


    // test arbre

//    int la = 5;
//    int lo = 5;
//    while(1){
//   // for(int j = 1;j>0;j--){
//        joueurStochastique * j1 = new joueurStochastique("Titi",Couleur::BLEU,true);
//        joueurStochastique * j2 = new joueurStochastique("Toto",Couleur::ROUGE,false);
//        std::vector<std::pair<typePiece,int>> testP;
//        testP.push_back(std::pair<typePiece,int>(typePiece::CHAR,1));
//        Jeu Test(j1,j2,testP,lo,la,TypeCarte::PLAINES,10);
//        int i = 0;
//        std::cout<<"*****************************************"<<std::endl
//                <<"*                 tour "<<i<<"                  *"<<std::endl
//               <<"*****************************************"<<std::endl;
//        j2->getArbre()->Courant->getCarte().Afficher();
//        while((!j1->getArbre()->Courant->getCarte().fini())&&(i<20)){
//            i++;
//            std::cout<<"*****************************************"<<std::endl
//                    <<"*                 tour "<<i<<"                  *"<<std::endl
//                   <<"*****************************************"<<std::endl;
//            //tmp.getFils()[0]->getCarte().Afficher();
//            j1->jouer(Test.getPlateau());
//            // j2->getArbre()->Courant->getCarte().Afficher(); // affichage aprésj1
//            if (!j1->getArbre()->Courant->getCarte().fini()) {j2->jouer(Test.getPlateau());}
//            // j2->getArbre()->Courant->getCarte().Afficher(); // affichage aprésj2

//        }
//        j2->getArbre()->Courant->getCarte().Afficher();
//        j1->getArbre()->Racine->save();
//    }

    //     return 0;

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
