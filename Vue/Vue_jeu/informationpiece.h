#ifndef INFORMATIONPIECE_H
#define INFORMATIONPIECE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <sstream>

class InformationPiece : public QWidget
{
    Q_OBJECT
public:
    explicit InformationPiece(QWidget *parent = 0);

signals:

public slots:
    void putInformationTransporteur(QString nom, int pdv,int pdvMax, QString proprio, int stockage, int stockage_max);
    void putInformationDestructeur(QString nom, int pdv,int pdvMax, QString proprio, int munition, int munition_max);
    void putInformationNeutre(QString nom, int pdv,int pdvMax, QString proprio);
    void putInformationVide();

private:
    void removeLayout();
};

#endif // INFORMATIONPIECE_H
