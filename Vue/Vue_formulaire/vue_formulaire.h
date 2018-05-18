#ifndef VUE_FORMULAIRE_H
#define VUE_FORMULAIRE_H

#include <QWidget>
#include <Controleur/controleur_formulaire.h>
#include <Vue/Vue_formulaire/ligneformjoueur.h>
#include <Vue/Vue_formulaire/formulairecarte.h>
#include <Vue/Vue_formulaire/formulairebouton.h>

class Vue_Formulaire : public QWidget
{
    Q_OBJECT
public:
    explicit Vue_Formulaire(QWidget *parent = 0);
    ~Vue_Formulaire();

    QPushButton* getBoutonRetour() const;
    QPushButton* getBoutonJouer() const;
    Controleur_Formulaire* getControleur() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    Controleur_Formulaire* _controleur;

    QVBoxLayout* _layout_principal;
    QGridLayout* _grid_layout; // Layout pour placer les ligneJoueurs
    QHBoxLayout* _layout_bas; //Partie inferieure du formulaire

    QPushButton* _ajouter_joueur; // Pour ajouter une ligneJoueur
    QPushButton* _supprimer_joueur; // Pour supprimer un ligneJoueur
    int _nombreJoueur; //Compte le nombre de joueur de la partie

    FormulaireCarte* _formCarte;
    FormulaireBouton* _formBouton;

signals:

public slots:
    void addLigneJoueur();
    void supprLigneJoueur();
};

#endif // VUE_FORMULAIRE_H
