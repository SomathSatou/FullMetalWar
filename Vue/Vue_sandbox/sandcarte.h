#ifndef SANDCARTE_H
#define SANDCARTE_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>

class SandCarte : public QWidget
{
    Q_OBJECT
public:
    explicit SandCarte(QWidget *parent = 0);
    QSpinBox* getSpinBoxLongueur() const { return _longueur_carte; }
    QSpinBox* getSpinBoxLargeur() const { return _largeur_carte; }

protected:
    void paintEvent(QPaintEvent *event);

private:
    QSpinBox* _longueur_carte;
    QSpinBox* _largeur_carte;

signals:

public slots:
};

#endif // SANDCARTE_H
