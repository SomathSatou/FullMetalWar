#ifndef CONTROLEUR_FORMULAIRE_H
#define CONTROLEUR_FORMULAIRE_H

#include <QObject>
#include <Moteur/Jeu/allmotor.h>
#include <vector>

class Controleur_Formulaire : public QObject
{
    Q_OBJECT

public:
    explicit Controleur_Formulaire(QObject *parent = 0);

    int getLongueur() const { return _longueurMap; }
    int getLargeur() const { return _largeurMap; }
    void addJoueur();
    void supprJoueur();
    const std::vector<Joueur *>& getListeJoueurs() const { return _listeJoueurs; }

private:
    bool testInformation() const; // Va tester les informations entrées pour et dire si on doit ou non activer le bouton "JOUER" du formulaire

    std::vector<Joueur *> _listeJoueurs;
    int _longueurMap;
    int _largeurMap;

signals:
    void sendEnableJouer(bool state);

public slots:
    void setLongueur(int longueur);
    void setLargeur(int largeur);
    void setCouleur(int numero, int indexCouleur);
    void setNom(int numero, const QString& nom);
    void setPAturn(int numero, int value);
    void setPAmax(int numero, int value);
};

#endif // CONTROLEUR_FORMULAIRE_H
