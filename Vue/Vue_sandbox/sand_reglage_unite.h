#ifndef SAND_REGLAGE_UNITE_H
#define SAND_REGLAGE_UNITE_H

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

class Sand_reglage_unite : public QWidget
{
    Q_OBJECT
public:
    explicit Sand_reglage_unite(QWidget *parent = 0);
    QSpinBox* getChar() const;
    QSpinBox* getGrosTas() const;
    QSpinBox* getCrabe() const;
    QSpinBox* getPondeuse() const;
    QSpinBox* getBase() const;
    QSpinBox* getBarge() const;
    QSpinBox* getVedette() const;

protected:
    void paintEvent(QPaintEvent *);

private:
    QSpinBox* _char;
    QSpinBox* _grosTas;
    QSpinBox* _crabe;
    QSpinBox* _pondeuse;
    QSpinBox* _base;
    QSpinBox* _barge;
    QSpinBox* _vedette;

signals:
    void sendChar(int);
    void sendGrosTas(int);
    void sendCrabe(int);
    void sendPondeuse(int);
    void sendBase(int);
    void sendBarge(int);
    void sendVedette(int);

public slots:

    void charChanged(int value);
    void grosTasChanged(int value);
    void crabeChanged(int value);
    void pondeuseChanged(int value);
    void baseChanged(int value);
    void bargeChanged(int value);
    void vedetteChanged(int value);



};
#endif // SAND_REGLAGE_UNITE_H
