#include "controleur_formulaire.h"
#include "Moteur/Piece/Piece.h"

Controleur_Formulaire::Controleur_Formulaire(QObject *parent) :
    QObject(parent),
    _listeJoueurs(),
    _longueurMap(20),
    _largeurMap(20)
{
    _listeJoueurs.push_back(new Joueur("",Couleur::BLEU));
    _listeJoueurs.push_back(new Joueur("",Couleur::BLEU));

}

/**********************************SLOTS******************************************/

void Controleur_Formulaire::setCouleur(int numero, int indexCouleur){
    switch(indexCouleur){
        case 0:
            _listeJoueurs[numero]->setCouleur(Couleur::BLEU);
            break;
        case 1:
            _listeJoueurs[numero]->setCouleur(Couleur::ROUGE);
            break;
        case 2:
            _listeJoueurs[numero]->setCouleur(Couleur::VERT);
            break;
        case 3:
            _listeJoueurs[numero]->setCouleur(Couleur::JAUNE);
            break;
    }

    emit sendEnableJouer(testInformation());
}

void Controleur_Formulaire::addJoueur() {
    _listeJoueurs.push_back(new Joueur("",Couleur::BLEU));
    emit sendEnableJouer(false);
}

void Controleur_Formulaire::supprJoueur() {
    _listeJoueurs.pop_back();
    emit sendEnableJouer(testInformation());
}

void Controleur_Formulaire::setNom(int numero, const QString &nom){
    _listeJoueurs[numero]->setPseudonyme(nom.toStdString());
    emit sendEnableJouer(testInformation());
}

void Controleur_Formulaire::setLongueur(int longueur){
    _longueurMap = longueur;
}

void Controleur_Formulaire::setLargeur(int largeur){
    _largeurMap = largeur;
}

void Controleur_Formulaire::setPAturn(int numero, int value){
    _listeJoueurs[numero]->setNombrePADebut(value);
}


void Controleur_Formulaire::setPAmax(int numero, int value){
    _listeJoueurs[numero]->setNombrePAMax(value);
}

bool Controleur_Formulaire::testInformation() const {
    for(std::vector<Joueur*>::const_iterator i = _listeJoueurs.cbegin(); i != _listeJoueurs.cend(); i++) {
        for(std::vector<Joueur*>::const_iterator j = i; j != _listeJoueurs.cend(); j++) {

            if(j != i) {
                QString j1 = (*i)->getPseudonyme().c_str();
                QString j2 = (*j)->getPseudonyme().c_str();

                bool testCouleur = (*i)->getCouleur() == (*j)->getCouleur();
                bool testPseudo = j1.toUpper().compare(j2.toUpper()) == 0;

                if(j1.isEmpty() || j2.isEmpty()) testPseudo = true;

                if(testCouleur || testPseudo) return false;
            }

        } // END FOR

    } // END FOR

    return true;
}



