#include "tableaudebord.h"

TableauDeBord::TableauDeBord(int longueur, int largeur, QWidget *parent) : QWidget(parent)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int height = rec.height();
    int width = rec.width();

    setFixedHeight(height/5);

    _layout = new QHBoxLayout(this);
    _layout->setMargin(0);
    _layout->setSpacing(0);

    _layout_map = new QVBoxLayout();
    _layout_map->setMargin(0);
    _layout_map->setSpacing(0);

    _finDeTour = new QPushButton("FIN DE TOUR",this);

    _minimap = new MiniMap(longueur,largeur,this);
    _minimap->setFixedWidth(width/4);

    _infoPiece = new InformationPiece(this);

    _visuel_unite = new ModelisationUnite(this);
    _visuel_unite->setStyleSheet("background-color : lightgray");
    _visuel_unite->setFixedWidth(width/8);

    // Layout vertical avec le bouton de fin de tour puis la minimap
    _layout_map->addWidget(_finDeTour);
    _layout_map->addWidget(_minimap);

    _layout->addWidget(_visuel_unite);
    _layout->addWidget(_infoPiece);
    _layout->addLayout(_layout_map);

}

const MiniMap *TableauDeBord::getMiniMap() const { return _minimap; }

const QPushButton *TableauDeBord::getFinDeTour() const { return _finDeTour; }

const InformationPiece *TableauDeBord::getInformationPiece() const { return _infoPiece; }

const ModelisationUnite *TableauDeBord::getModelisationUnite() const { return _visuel_unite; }
