#ifndef MINIMAP_H
#define MINIMAP_H

#include <QWidget>
#include <QPainter>
#include <Moteur/Jeu/allmotor.h>

typedef struct {
    QString typecase;
    bool piece;
    int couleur;
} CaseCarte;

class MiniMap : public QWidget
{
    Q_OBJECT
public:
    explicit MiniMap(int longueur, int largeur, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent* e);

private:
    int _longueur;
    int _largeur;
    int _taille;
    std::vector<CaseCarte> _listeCase;

signals:

public slots:
    void updateCase(QString typecase, bool piece, int Couleur, int i);
};

#endif // MINIMAP_H
