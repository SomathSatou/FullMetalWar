#ifndef FORMULAIRECARTE_H
#define FORMULAIRECARTE_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>

class FormulaireCarte : public QWidget
{
    Q_OBJECT
public:
    explicit FormulaireCarte(QWidget *parent = 0);
    QSpinBox* getSpinBoxLongueur() const;
    QSpinBox* getSpinBoxLargeur() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    QSpinBox* _longueur_carte;
    QSpinBox* _largeur_carte;

signals:

public slots:
};

#endif // FORMULAIRECARTE_H
