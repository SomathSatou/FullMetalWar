#ifndef REGLECARTE_H
#define REGLECARTE_H

#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include "CaseMap.h"

#define NB_TYPECASE 5

TYPECASE integerToCASEMAP(int i);
TYPECASE qstringToCASEMAP(QString s);


class RegleCarte
{
public:
    RegleCarte(const QString& nomFichier = ":/Files/Ressources/Regles_Carte/regle_map.txt");

    int getRegle(TYPECASE gauche, TYPECASE haut, TYPECASE type_case) const;
    int getRegle(TYPECASE case_adjacente, TYPECASE type_case) const;

private:
    bool read(const QString& nomFichier);
    bool addRegle(TYPECASE gauche, TYPECASE haut, TYPECASE type_case, int value);

    QString _nomFichier;
    std::vector<int> _regles;

};

#endif // REGLECARTE_H
