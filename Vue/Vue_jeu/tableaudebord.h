#ifndef TABLEAUDEBORD_H
#define TABLEAUDEBORD_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <Vue/Vue_jeu/minimap.h>
#include <Vue/Vue_jeu/informationpiece.h>
#include <Vue/Modelisation3D/modelisationunite.h>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>

class TableauDeBord : public QWidget
{
    Q_OBJECT
public:
    explicit TableauDeBord(int longueur, int largeur, QWidget *parent = 0);

    const MiniMap* getMiniMap() const { return _minimap; }
    const QPushButton* getFinDeTour() const { return _finDeTour; }
    const InformationPiece* getInformationPiece() const { return _infoPiece; }
    const ModelisationUnite* getModelisationUnite() const { return _visuel_unite; }

private:
    QHBoxLayout* _layout;
    QVBoxLayout* _layout_map;

    MiniMap* _minimap;

    QPushButton* _finDeTour;

    InformationPiece* _infoPiece;

    ModelisationUnite* _visuel_unite;

signals:

public slots:
};

#endif // TABLEAUDEBORD_H
