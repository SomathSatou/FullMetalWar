#ifndef REGLECARTE_H
#define REGLECARTE_H

#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>

#include "defineclass.h"

#define NB_typeCase 5

typeCase integerToCASEMAP(int i);
typeCase qstringToCASEMAP(QString s);


class RegleCarte
{
public:
    RegleCarte(const QString& nomFichier = ":/Files/Ressources/Regles_Carte/regle_map.txt");

    int getRegle(typeCase gauche, typeCase haut, typeCase type_case) const;
    int getRegle(typeCase case_adjacente, typeCase type_case) const;

private:
    bool read(const QString& nomFichier);
    bool addRegle(typeCase gauche, typeCase haut, typeCase type_case, int value);

    QString _nomFichier;
    std::vector<int> _regles;

};

#endif // REGLECARTE_H
