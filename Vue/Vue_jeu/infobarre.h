#ifndef INFOBARRE_H
#define INFOBARRE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>
#include <sstream>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>

class InfoBarre : public QWidget
{
    Q_OBJECT
public:
    explicit InfoBarre(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

private:
    QHBoxLayout* _layout;

    QLabel* _label_tour;
    QLabel* _label_joueurCourant;

    QPushButton* _option;

signals:

public slots:
    void updateInfoBarre(int tour,std::string joueur);
};

#endif // INFOBARRE_H
