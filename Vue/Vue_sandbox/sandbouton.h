#ifndef SANDBOUTON_H
#define SANDBOUTON_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QPushButton>
#include <QHBoxLayout>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>

class SandBouton : public QWidget
{
    Q_OBJECT
public:
    explicit SandBouton(QWidget *parent = 0);
    QPushButton* getBoutonRetour() const { return _retour; }
    QPushButton* getBoutonJouer() const { return _jouer; }

protected:
    void paintEvent(QPaintEvent* e);

private:
    QPushButton* _jouer; // Bouton pour lancer la partie
    QPushButton* _retour; // Bouton pour retourner sur le menu principal

signals:

public slots:
    void enableJouer(bool state);
};

#endif // SANDBOUTON_H
