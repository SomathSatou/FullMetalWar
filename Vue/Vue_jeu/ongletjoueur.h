#ifndef ONGLETJOUEUR_H
#define ONGLETJOUEUR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <sstream>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>
#include "defineclass.h"

class OngletJoueur : public QWidget
{
    Q_OBJECT
public:
    explicit OngletJoueur(QString pseudo,Couleur coul , int pa = 10, int pa_max = 25 ,QWidget *parent = 0);
    explicit OngletJoueur(const OngletJoueur & copy);

    void setPseudo(QString pseudo);
    void setPA(int pa, int pa_max);
    void setCouleur(Couleur couleur);

protected:
    void paintEvent(QPaintEvent *);

private:

    QVBoxLayout *_layout;
    QLabel *_label_pseudo;
    QLabel *_label_PA;

signals:

public slots:

};

#endif // ONGLETJOUEUR_H
