#ifndef VUE_JEU_H
#define VUE_JEU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <Vue/Vue_jeu/ongletjoueur.h>
#include <Vue/Vue_jeu/infobarre.h>
#include <Vue/Vue_jeu/tableaudebord.h>
#include <Vue/Modelisation3D/modelisationjeu.h>

class Vue_Jeu : public QWidget
{
    Q_OBJECT
public:
    Vue_Jeu(int longueur, int largeur, QWidget *parent = 0);

    const MiniMap* getMiniMap() const { return _tableauDeBord->getMiniMap(); }
    const ModelisationJeu* getModelisation() const { return m; }
    const QPushButton* getFinDeTour() const { return _tableauDeBord->getFinDeTour(); }
    const InfoBarre* getInfoBarre() const { return _infoBarre; }
    const InformationPiece* getInformationPiece() const { return _tableauDeBord->getInformationPiece(); }
    const ModelisationUnite* getModelisationUnite() const { return _tableauDeBord->getModelisationUnite(); }

private:
    std::vector<OngletJoueur*> _listeOnglet;
    ModelisationJeu* m;
    TableauDeBord* _tableauDeBord;
    InfoBarre* _infoBarre;

signals:

public slots :
    void createOnglet(QString pseudo, int pa, int pa_max,Couleur coul);
    void setPAOnglet(int pa, int pa_max, int num_onglet);


};

#endif // VUE_JEU_H
