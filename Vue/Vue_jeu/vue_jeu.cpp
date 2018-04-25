#include "vue_jeu.h"

int pos_onglet = 150; // Position en Y initiale du premier onglet

Vue_Jeu::Vue_Jeu(int longueur,int largeur,QWidget *parent)
    : QWidget(parent), _listeOnglet()
{
    pos_onglet = 150;

    QVBoxLayout* _layout = new QVBoxLayout(this);
    _layout->setMargin(0);
    _layout->setSpacing(0);

    _infoBarre = new InfoBarre(this);
    _tableauDeBord = new TableauDeBord(longueur,largeur,this);

    QSurfaceFormat format;
    format.setSamples(16);

    m = new ModelisationJeu(longueur,largeur,this);
    m->setFormat(format);

    _layout->addWidget(_infoBarre);
    _layout->addWidget(m);
    _layout->addWidget(_tableauDeBord);
}

void Vue_Jeu::createOnglet(QString pseudo, int pa, int pa_max,Couleur couleur) {

    OngletJoueur* oj = new OngletJoueur(pseudo,couleur,pa,pa_max,this);

    _listeOnglet.push_back(oj);

    oj->move(QPoint(0,pos_onglet));
    oj->show();

    pos_onglet += 100;
}

void Vue_Jeu::setPAOnglet(int pa, int pa_max, int num_onglet) {
    _listeOnglet[num_onglet]->setPA(pa,pa_max);
}
