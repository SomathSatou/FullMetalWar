#include "RegleCarte.h"

using namespace std;

TYPECASE integerToTYPECASE(int i) {
    switch(i) {
    case 0 : return TYPECASE::PLAINE;
    case 1 : return TYPECASE::MONTAGNE;
    case 2 : return TYPECASE::MER;
    case 3 : return TYPECASE::MARAIS;
    case 4 : return TYPECASE::RECIF;
    default :
        cout << "ERREUR integerToTYPECASE" << endl;
        exit(0);
    }
}

int TYPECASEToInteger(TYPECASE c) {
    switch(c) {
    case TYPECASE::PLAINE : return 0;
    case TYPECASE::MONTAGNE : return 1;
    case TYPECASE::MER : return 2;
    case TYPECASE::MARAIS : return 3;
    case TYPECASE::RECIF : return 4;
    default :
        cout << "ERREUR TYPECASEToInteger" << endl;
        exit(0);
    }
}

TYPECASE qstringToTYPECASE(QString s) {
    if(s.toUpper().compare("PLAINE") == 0)
        return TYPECASE::PLAINE;

    if(s.toUpper().compare("MONTAGNE") == 0)
        return TYPECASE::MONTAGNE;

    if(s.toUpper().compare("MER") == 0)
        return TYPECASE::MER;

    if(s.toUpper().compare("MARAIS") == 0)
        return TYPECASE::MARAIS;

    if(s.toUpper().compare("RECIF") == 0)
        return TYPECASE::RECIF;

    return TYPECASE::VIDE;
}

RegleCarte::RegleCarte(const QString& nomFichier) :
    _nomFichier(nomFichier),
    _regles(NB_TYPECASE*NB_TYPECASE + NB_TYPECASE*NB_TYPECASE*NB_TYPECASE)
{
    if(!read(_nomFichier)) {
        cout << "ERREUR : lecture  des règles" << endl;
        exit(0);
    }
}

bool RegleCarte::read(const QString& nomFichier) {

    QString haut,gauche;
    int value; // Variable pour stocker la valeur des règles

    QFile fichier(nomFichier);

    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << " ERREUR : le fichier n'a pas pu être ouvert" << endl;
        return false;
    } // END IF

    QTextStream flux(&fichier);

    bool running = true;

    while(running){

        flux >> gauche >> haut;

        if(gauche.compare("EOF")==0) // On test si on a atteint la fin du fichier
            running = false;
        else {

            for(int i = 0; i<NB_TYPECASE; i++){
                flux >> value;
                addRegle(qstringToTYPECASE(gauche),qstringToTYPECASE(haut),integerToTYPECASE(i),value);
            }

        } // END ELSE

    } // END WHILE

    fichier.close();

    return true;
} // END

bool RegleCarte::addRegle(TYPECASE gauche, TYPECASE haut, TYPECASE type_case, int value) {

    if((gauche == TYPECASE::VIDE) && (haut == TYPECASE::VIDE)) {
        cout << "ERREUR : le fichier est mal écrit" << endl;
        return false;
    } // END IF

    if(haut == TYPECASE::VIDE) {
        _regles[NB_TYPECASE*TYPECASEToInteger(gauche)+TYPECASEToInteger(type_case)] = value;
    } // END IF
    else {
        _regles[NB_TYPECASE*NB_TYPECASE*(TYPECASEToInteger(gauche)+1)+NB_TYPECASE*TYPECASEToInteger(haut)+TYPECASEToInteger(type_case)] = value;
    } // END ELSE

    return true;
} // END

int RegleCarte::getRegle(TYPECASE gauche, TYPECASE haut, TYPECASE type_case) const {
    return _regles[NB_TYPECASE*NB_TYPECASE*(TYPECASEToInteger(gauche)+1)+NB_TYPECASE*TYPECASEToInteger(haut)+TYPECASEToInteger(type_case)];
} // END

int RegleCarte::getRegle(TYPECASE case_adjacente, TYPECASE type_case) const {
    return _regles[NB_TYPECASE*TYPECASEToInteger(case_adjacente)+TYPECASEToInteger(type_case)];
} // END

