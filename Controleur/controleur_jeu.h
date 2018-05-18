#ifndef CONTROLEUR_JEU_H
#define CONTROLEUR_JEU_H

#include <unistd.h>
#include <QObject>
#include <Moteur/Jeu/allmotor.h>
#include <Vue/Vue_jeu/vue_jeu.h>
#include <Moteur/Piece/piece.h>

#include "defineclass.h"

QString TYPECASEToQString(typeCase t); // Transforme un élément de l'enumération TYPECASE en QString
QString PieceToQString(const Piece * p); // Transforme une piece en QString
int COULEURToInt(Couleur c);

class Controleur_Jeu : public QObject
{
    Q_OBJECT
public:
    explicit Controleur_Jeu(const std::vector<Joueur*> listeJoueurs,int longueur, int largeur, QObject *parent = 0);
    explicit Controleur_Jeu(const std::vector<Joueur*> listeJoueurs,int longueur, int largeur,TypeCarte type,bool min,std::vector<std::pair<typePiece,int>> listepiece, QObject *parent = 0);
    ~Controleur_Jeu();

    Vue_Jeu* getVueJeu() const;
    void initialisation();
    void getCase(int i); // Récupère la case voulue dans le moteur pour l'envoyer à la vue via les signaux sendCaseMiniMap/sendCaseModelisation
    void getNombrePACourant(int);


    Jeu *getMoteur() const;
    void setMoteur(Jeu *moteur);

private:
    QObject* _parent;
    Jeu* _moteur;
    Vue_Jeu* _vue_jeu;
    QPoint _positionCurrentCase;
    int _PACourant;
    int _PAMax;
    //
    TypeCarte _type;
    std::vector<std::pair<typePiece,int>> _listePieces;
    bool _minerais;


signals:
    /*
     * Envoie les informations de la case à dessiner :
     *  - typecase : le type de la case à dessiner (plaine, mer, ...)
     *  - piece : la pièce qui se trouve sur la case (il peut n'y avoir aucune pièce sur la case)
     *  - couleur : la couleur du joueur qui possède la pièce
     *  - i : la position de la case à dessiner en position linéaire (mais peut éventuellement se changer en coordonnée basique)
     */
    void sendCaseMiniMap(QString typecase, bool piece, int Couleur, int i);
    void sendCaseModelisation(QString typecase, QString piece, int Couleur, int i);
    void sendModelisationUnite(QString monunite, Couleur coul);

    void sendCreateOnglet(QString pseudo, int pa, int pa_max, Couleur coul);
    void sendPAOnglet(int pa, int pa_max,int num_onglet);

    void sendValuesInfoBarre(int tour,std::string joueur);

    void sendInformationDestructeur(QString nom, int pdv,int pdvMax, QString proprio, int munition, int munition_max);
    void sendInformationTransporteur(QString nom, int pdv,int pdvMax, QString proprio, int munition, int munition_max);
    void sendInformationNeutre(QString nom, int pdv,int pdvMax, QString proprio);
    void sendInformationVide();

    void putScoreScreen(const QString& pseudo, int score);



public slots:
    void getClickFinDeTour(); // Récupère le signal du clique de fin de tour
    void getClickModelisation(int x, int y); // Récupère les coordonnées de la case sélectionnée dans la modelisation
    void getPositionDeplacement(int x, int y);

};

#endif // CONTROLEUR_JEU_H
