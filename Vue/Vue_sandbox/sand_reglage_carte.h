#ifndef SAND_REGLAGE_CARTE_H
#define SAND_REGLAGE_CARTE_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>

class Sand_reglage_carte : public QWidget
{
    Q_OBJECT
public:
    explicit Sand_reglage_carte(QWidget *parent = 0);

    QComboBox* getType() const {return _typeCarte;}
    QCheckBox* getMinerai() const {return _minerais;}

protected:
    void paintEvent(QPaintEvent *);

private:
    QCheckBox* _minerais;
    QComboBox* _typeCarte;

signals:
    void sendType(int);
    void sendMinerais(int);

public slots:
    void typeChanged(int);
    void mineraisChanged(int);
};

#endif // SAND_REGLAGE_CARTE_H
