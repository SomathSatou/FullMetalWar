#ifndef CONTROLEUR_SANDBOX_H
#define CONTROLEUR_SANDBOX_H

#include <QObject>
#include <Moteur/Jeu/allmotor.h>
#include <vector>

class Controleur_Sandbox : public QObject
{
    Q_OBJECT

public:
    explicit Controleur_Sandbox(QObject *parent = 0);

    //accesseur
    int getLongueur() const { return _longueurMap; }
    int getLargeur() const { return _largeurMap; }
    TypeCarte getType() const { return _type; }
    int getMinerais() const { return _minerais; }
    std::vector<std::pair<typePiece,int>> getListePiece() const {return _listePiece;}
    const std::vector<Joueur *>& getListeJoueurs() const { return _listeJoueurs; }

    void addJoueur();
    void supprJoueur();

    void afficheListe();


private:
    bool testInformation() const; // Va tester les informations entrées pour et dire si on doit ou non activer le bouton "JOUER" du formulaire

    std::vector<Joueur*> _listeJoueurs;
    int _longueurMap;
    int _largeurMap;

    TypeCarte _type;
    bool _minerais;

    std::vector<std::pair<typePiece,int>> _listePiece;

signals:
    void sendEnableJouer(bool state);

public slots:
    void setLongueur(int longueur);
    void setLargeur(int largeur);

    void setType(int);
    void setMinerais(int);

    void setChar(int);
    void setGrosTas(int);
    void setCrabe(int);
    void setPondeuse(int);
    void setBase(int);
    void setBarge(int);
    void setVedette(int);

    void setCouleur(int numero, int indexCouleur);
    void setNom(int numero, const QString& nom);
    void setPAturn(int numero, int value);
    void setPAmax(int numero, int value);
};

#endif // CONTROLEUR_SANDBOX_H
