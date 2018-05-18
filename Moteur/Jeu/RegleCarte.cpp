#include "RegleCarte.h"

using namespace std;

typeCase integerTotypeCase(int i) {
    switch(i) {
    case 0 : return typeCase::PLAINE;
    case 1 : return typeCase::MONTAGNE;
    case 2 : return typeCase::MER;
    case 3 : return typeCase::MARAIS;
    case 4 : return typeCase::RECIF;
    default :
//        cout << "ERREUR integerTotypeCase" << endl;
        exit(0);
    }
}

int typeCaseToInteger(typeCase c) {
    switch(c) {
    case typeCase::PLAINE : return 0;
    case typeCase::MONTAGNE : return 1;
    case typeCase::MER : return 2;
    case typeCase::MARAIS : return 3;
    case typeCase::RECIF : return 4;
    default :
//        cout << "ERREUR typeCaseToInteger" << endl;
        exit(0);
    }
}

typeCase qstringTotypeCase(QString s) {
    if(s.toUpper().compare("PLAINE") == 0)
        return typeCase::PLAINE;

    if(s.toUpper().compare("MONTAGNE") == 0)
        return typeCase::MONTAGNE;

    if(s.toUpper().compare("MER") == 0)
        return typeCase::MER;

    if(s.toUpper().compare("MARAIS") == 0)
        return typeCase::MARAIS;

    if(s.toUpper().compare("RECIF") == 0)
        return typeCase::RECIF;

    return typeCase::VIDE;
}

RegleCarte::RegleCarte(const QString& nomFichier) :
    _nomFichier(nomFichier),
    _regles(NB_typeCase*NB_typeCase + NB_typeCase*NB_typeCase*NB_typeCase)
{
    if(!read(_nomFichier)) {
//        cout << "ERREUR : lecture  des règles" << endl;
        exit(0);
    }
}

bool RegleCarte::read(const QString& nomFichier) {

    QString haut,gauche;
    int value; // Variable pour stocker la valeur des règles

    QFile fichier(nomFichier);

    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        cout << " ERREUR : le fichier n'a pas pu être ouvert" << endl;
        return false;
    } // END IF

    QTextStream flux(&fichier);

    bool running = true;

    while(running){

        flux >> gauche >> haut;

        if(gauche.compare("EOF")==0) // On test si on a atteint la fin du fichier
            running = false;
        else {

            for(int i = 0; i<NB_typeCase; i++){
                flux >> value;
                addRegle(qstringTotypeCase(gauche),qstringTotypeCase(haut),integerTotypeCase(i),value);
            }

        } // END ELSE

    } // END WHILE

    fichier.close();

    return true;
} // END

bool RegleCarte::addRegle(typeCase gauche, typeCase haut, typeCase type_case, int value) {

    if((gauche == typeCase::VIDE) && (haut == typeCase::VIDE)) {
//        cout << "ERREUR : le fichier est mal écrit" << endl;
        return false;
    } // END IF

    if(haut == typeCase::VIDE) {
        _regles[NB_typeCase*typeCaseToInteger(gauche)+typeCaseToInteger(type_case)] = value;
    } // END IF
    else {
        _regles[NB_typeCase*NB_typeCase*(typeCaseToInteger(gauche)+1)+NB_typeCase*typeCaseToInteger(haut)+typeCaseToInteger(type_case)] = value;
    } // END ELSE

    return true;
} // END

int RegleCarte::getRegle(typeCase gauche, typeCase haut, typeCase type_case) const {
    return _regles[NB_typeCase*NB_typeCase*(typeCaseToInteger(gauche)+1)+NB_typeCase*typeCaseToInteger(haut)+typeCaseToInteger(type_case)];
} // END

int RegleCarte::getRegle(typeCase case_adjacente, typeCase type_case) const {
    return _regles[NB_typeCase*typeCaseToInteger(case_adjacente)+typeCaseToInteger(type_case)];
} // END

