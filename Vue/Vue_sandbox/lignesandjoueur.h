#ifndef LIGNESANDJOUEUR_H
#define LIGNESANDJOUEUR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPainter>
#include <QLabel>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>

class LigneSandJoueur : public QWidget
{
    Q_OBJECT
public:
    explicit LigneSandJoueur( int numeroJoueur,QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

private:
    QHBoxLayout* _layout;

    QLineEdit* _nomJoueur;
    QComboBox* _listeCouleur;
    QSpinBox* _PA_turn;
    QSpinBox* _PA_max;

    int _numeroJoueur;

signals:
    void sendNom(int numero, const QString& nom);
    void sendCouleur(int numero, int indexCouleur);
    void sendPAturn(int numero, int value);
    void sendPAmax(int numero, int value);

public slots:
    void nomChanged(const QString& nom);
    void couleurChanged(int indexCouleur);
    void PA_turnChanged(int value);
    void PA_maxChanged(int value);
};


#endif // LIGNESANDJOUEUR_H
