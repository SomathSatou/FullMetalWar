#ifndef VUE_SANDBOX_H
#define VUE_SANDBOX_H

#include <QWidget>
#include <Controleur/controleur_sandbox.h>
#include <Vue/Vue_sandbox/lignesandjoueur.h>
#include <Vue/Vue_sandbox/sandcarte.h>
#include <Vue/Vue_sandbox/sandbouton.h>
#include <Vue/Vue_sandbox/sand_reglage_carte.h>
#include <Vue/Vue_sandbox/sand_reglage_unite.h>

class Vue_Sandbox : public QWidget
{
    Q_OBJECT
public:
    explicit Vue_Sandbox(QWidget *parent = 0);
    ~Vue_Sandbox();

    QPushButton* getBoutonRetour() const { return _formBouton->getBoutonRetour(); }
    QPushButton* getBoutonJouer() const { return _formBouton->getBoutonJouer(); }
    Controleur_Sandbox* getControleur() const { return _controleur; }

protected:
    void paintEvent(QPaintEvent *event);

private:
    Controleur_Sandbox* _controleur;

    QVBoxLayout* _layout_principal;
    QGridLayout* _grid_layout; // Layout pour placer les ligneJoueurs
    QHBoxLayout* _layout_bas; //Partie inferieure du formulaire
    QHBoxLayout* _layout_carte; //Partie reglage de la carte
    QHBoxLayout* _layout_unite; // reglage des unité

    QPushButton* _ajouter_joueur; // Pour ajouter une ligneJoueur
    QPushButton* _supprimer_joueur; // Pour supprimer un ligneJoueur
    int _nombreJoueur; //Compte le nombre de joueur de la partie

    SandCarte* _formCarte;
    SandBouton* _formBouton;
    Sand_reglage_carte* _sandCarte;
    Sand_reglage_unite* _sandUnite;

signals:

public slots:
    void addLigneJoueur();
    void supprLigneJoueur();
};

#endif // VUE_SANDBOX_H
