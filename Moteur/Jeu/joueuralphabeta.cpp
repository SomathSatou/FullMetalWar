#include "joueuralphabeta.h"



JoueurAlphaBeta::JoueurAlphaBeta(std::string nom, Couleur couleur, bool joueur)
    : Joueur(nom,couleur,joueur),
      _profondeur(PROFONDEUR)
{}

coups JoueurAlphaBeta::jouer(Plateau p){
    //    return alpha_beta_coup_par_coup(p);
    return alpha_beta(p);
}

coups JoueurAlphaBeta::alpha_beta(Plateau &p){

    std::vector<coups> liste;
    coups a_jouer;
    coupsAJouer(p,liste,PA_MAX);
    int max(-1000);
    int ab(0);
    int alpha(-1000);
    int beta(1000);

    std::cout << "\nDebut recherche AB\n";

    for(auto & l : liste){
        p.jouerCoups(l);
        ab=alpha_beta_U(p, alpha , beta, _profondeur, PA_MAX);
        std::cout << "\n\tResultat AB : " << ab;
        if(max<ab){
            a_jouer=l;
        }
        p.annulerCoups(PA_MAX);
    }



    std::cout<< "\nResultat : "<< max;
    int i(0);
    for(auto & c : a_jouer){
        std::cout
                << "\n\t"
                << ++i
                << " : "
                << c.src.x
                << "-"
                << c.src.y
                << " vers "
                << c.dst.x
                << "-"
                << c.dst.y;
    }

    std::cout << std::flush;
    return a_jouer;

    /*
        std::vector<coups> liste;

        coupsAJouer(p,liste,PA_MAX);
        int j(0);
        int i(0);
        for(auto l : liste){
            std::cout << "\nNiveau " << j++;
            for(auto c : l){
                std::cout
                        << "\n\t\t"
                        << ++i
                        << " : "
                        << c.src.x
                        << "-"
                        << c.src.y
                        << " vers "
                        << c.dst.x
                        << "-"
                        << c.dst.y;
            }
        }

        std::cout << std::flush;
        return p.coupsPossibles();
        */
}

int JoueurAlphaBeta::alpha_beta_E(Plateau &p, int alpha, int beta, int profondeur, int PA){
    if(profondeur == 0 || p.fin()){
        //        std::cout << "\nFin de la recherche dans existentiel profondeur : " << profondeur;
        int eval = (getJoueur()? 1 : -1 ) * p.eval();
        //        std::cout << "\n\tEvaluation du plateau : " << eval ;
        return eval;
    }
    p.checkPieces();
    p.setJoueurCourant(getJoueur());
    int v = -1000;
    std::vector<coups> liste;
    coupsAJouer(p,liste,PA);
    for(auto & l : liste){
        p.setJoueurCourant(getJoueur());
        if(p.jouerCoups(l)){

            v = maximum(v,alpha_beta_U(p, alpha, beta, profondeur-1, PA_MAX));
            p.annulerCoups(PA_MAX);
            if(v >= beta){
                return v;
            }
            alpha = maximum(v,alpha);
        }
    }
    return v;
}

int JoueurAlphaBeta::alpha_beta_U(Plateau &p, int alpha, int beta, int profondeur, int PA){
    if(profondeur == 0 || p.fin()){
        //        std::cout << "\nFin de la recherche dans universel profondeur : " << profondeur;
        int eval = (getJoueur()? 1 : -1 ) * p.eval();
        //        std::cout << "\n\tEvaluation du plateau : " << eval ;
        return eval;
    }
    p.checkPieces();
    p.setJoueurCourant(!getJoueur());
    int v = 1000;
    std::vector<coups> liste;
    coupsAJouer(p,liste,PA);
    for(auto & l : liste){
        p.setJoueurCourant(!getJoueur());
        if(p.jouerCoups(l)){

            v = minimum(v,alpha_beta_E(p, alpha, beta, profondeur-1, PA_MAX));
            p.annulerCoups(PA_MAX);
            PA++;
            if(v >= beta){
                return v;
            }
            alpha = maximum(v,alpha);
        }
    }
    return v;
}

int JoueurAlphaBeta::maximum(int a, int b){
    return (a>b? a : b);
}

int JoueurAlphaBeta::minimum(int a, int b){
    return (a<b? a : b);
}

coups JoueurAlphaBeta::alpha_beta_coup_par_coup(Plateau &p){
    coups a_jouer;
    int max(-1000);
    int ab(0);
    int alpha(-1000);
    int beta(1000);

    std::cout << "\nDebut recherche AB\n";

    for(auto & c : p.coupsPossibles()){
        _listeEnCours.clear();
        if(p.jouerCoup(c)){
            _listeEnCours.push_back(c);
            ab=alpha_beta_E_coup_par_coup(p, alpha , beta, _profondeur, PA_MAX-1);
            if(max<ab){
                a_jouer=_listeEnCours;
            }
            p.annulerCoup();
        }
    }

    std::cout<< "\nResultat : " << max;
    int i(0);
    for(auto & c : a_jouer){
        std::cout
                << "\n\t"
                << ++i
                << " : "
                << c.src.x
                << "-"
                << c.src.y
                << " vers "
                << c.dst.x
                << "-"
                << c.dst.y
                << (c.action==typeAction::ATTAQUER? " ATTAQUER" : " DEPLACER" );
    }

    std::cout << std::flush;
    return a_jouer;
}

int JoueurAlphaBeta::alpha_beta_E_coup_par_coup(Plateau &p, int alpha, int beta, int profondeur, int PA){
    if(profondeur == 0 || p.fin()){
        //        std::cout << "\nFin de la recherche dans existentiel profondeur : " << profondeur;
        int eval = (getJoueur()? 1 : -1 ) * p.eval();
        //        std::cout << "\n\tEvaluation du plateau : " << eval ;
        return eval;
    }
    int v = -1000;
    for(auto & c : p.coupsPossibles()){
        if(p.jouerCoup(c)){

            //            std::cout << "\nProfondeur "
            //                      << profondeur
            //                      << " existentiel"
            //                      << "\n\tcoup : "
            //                      << c.src.x
            //                      << "-"
            //                      << c.src.y
            //                      << " vers "
            //                      << c.dst.x
            //                      << "-"
            //                      << c.dst.y
            //                      << " PA restant : "
            //                      << PA;

            //            std::cout<< std::flush;
            PA--;
            if(PA == 0){
                if(_profondeur==profondeur)
                    _listeEnCours=p.getnDerniersCoups(PA_MAX);
                p.finDeTourJoueur();
                v = maximum(v,alpha_beta_U_coup_par_coup(p, alpha, beta, profondeur-1, PA_MAX));
                p.inverseJoueur();
            }else{
                v = alpha_beta_E_coup_par_coup(p , alpha, beta, profondeur, PA);
            }

            p.annulerCoup();
            PA++;
            if(v >= beta){
                return v;
            }
            alpha = maximum(v,alpha);

        }else{
            std::cout << "erreur coup";
        }
    }
    return v;
}

int JoueurAlphaBeta::alpha_beta_U_coup_par_coup(Plateau &p, int alpha, int beta, int profondeur, int PA){
    if(profondeur == 0 || p.fin()){
        //        std::cout << "\nFin de la recherche dans universel profondeur : " << profondeur;
        int eval = (getJoueur()? 1 : -1 ) * p.eval();
        //        std::cout << "\n\tEvaluation du plateau : " << eval ;
        return eval;
    }
    int v = 1000;
    for(auto & c : p.coupsPossibles()){

        if(p.jouerCoup(c)){

            //            std::cout << "\nProfondeur "
            //                      << profondeur
            //                      << " universel"
            //                      << "\n\tcoup : "
            //                      << c.src.x
            //                      << "-"
            //                      << c.src.y
            //                      << " vers "
            //                      << c.dst.x
            //                      << "-"
            //                      << c.dst.y
            //                      << " PA restant : "
            //                      << PA;
            PA--;
            if(PA == 0){
                p.finDeTourJoueur();
                v = minimum(v,alpha_beta_E_coup_par_coup(p, alpha, beta, profondeur-1, PA_MAX));
                p.inverseJoueur();
            }else{
                v = alpha_beta_U_coup_par_coup(p , alpha, beta, profondeur, PA);
            }

            p.annulerCoup();
            PA++;
            if(v <= alpha){
                return v;
            }
            beta = minimum(v,beta);

        }
    }
    return v;
}

void JoueurAlphaBeta::coupsAJouer(Plateau &p, std::vector<coups> &liste, int PA){
    for(auto & c : p.coupsPossibles()){
        if(p.jouerCoup(c)){
            PA--;

            if(PA == 0){
                liste.push_back(p.getnDerniersCoups(PA_MAX));
            }else{
                coupsAJouer(p, liste, PA);
            }

            PA++;
            p.annulerCoup();
        }
    }
}
