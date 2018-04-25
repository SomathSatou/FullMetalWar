#include "informationpiece.h"

InformationPiece::InformationPiece(QWidget *parent) : QWidget(parent)
{

}

void InformationPiece::putInformationTransporteur(QString nom, int pdv, int pdvMax, QString proprio, int stockage, int stockage_max) {

    removeLayout();

    QGridLayout* layout_principal = new QGridLayout(this);

    nom = "Nom : "+nom;
    proprio = "Propriétaire : "+proprio;

    std::ostringstream oss_pdv;
    oss_pdv << "PDV : " << pdv << "/" << pdvMax;
    QString s_pdv = oss_pdv.str().c_str();

    std::ostringstream oss_cap;
    oss_cap << "Capacité : " << stockage << "/" << stockage_max;
    QString s_capacite = oss_cap.str().c_str();

    layout_principal->addWidget(new QLabel(nom,this),0,0);
    layout_principal->addWidget(new QLabel(s_pdv,this),1,0);
    layout_principal->addWidget(new QLabel("Type : Transporteur",this),2,0);

    layout_principal->addWidget(new QLabel(proprio,this),0,1);
    layout_principal->addWidget(new QLabel(s_capacite,this),1,1);

    setLayout(layout_principal);
}

void InformationPiece::putInformationDestructeur(QString nom, int pdv, int pdvMax, QString proprio, int munition, int munition_max) {

    removeLayout();


    QGridLayout* layout_principal = new QGridLayout(this);

    nom = "Nom : "+nom;
    proprio = "Propriétaire : "+proprio;

    std::ostringstream oss_pdv;
    oss_pdv << "PDV : " << pdv << "/" << pdvMax;
    QString s_pdv = oss_pdv.str().c_str();

    std::ostringstream oss_mun;
    oss_mun << "Munitions : " << munition << "/" << munition_max;
    QString s_munition = oss_mun.str().c_str();


    layout_principal->addWidget(new QLabel(nom,this),0,0);
    layout_principal->addWidget(new QLabel(s_pdv,this),1,0);
    layout_principal->addWidget(new QLabel("Type : Destructeur",this),2,0);

    layout_principal->addWidget(new QLabel(proprio,this),0,1);
    layout_principal->addWidget(new QLabel(s_munition,this),1,1);

    setLayout(layout_principal);

    /*
        QHBoxLayout* layout_principal = new QHBoxLayout();
        QVBoxLayout* layout_colonne1 = new QVBoxLayout();
        QVBoxLayout* layout_colonne2 = new QVBoxLayout();

        layout_principal->addLayout(layout_colonne1);
        layout_principal->addLayout(layout_colonne2);

        nom = "Nom : "+nom;
        proprio = "Propriétaire : "+proprio;

        std::ostringstream oss_pdv;
        oss_pdv << "PDV : " << pdv << "/" << pdvMax;
        QString s_pdv = oss_pdv.str().c_str();

        std::ostringstream oss_mun;
        oss_mun << "Munitions : " << munition << "/" << munition_max;
        QString s_munition = oss_mun.str().c_str();

        layout_colonne1->addWidget(new QLabel(nom,this));
        layout_colonne1->addWidget(new QLabel(s_pdv,this));
        layout_colonne1->addWidget(new QLabel("Type : Destructeur",this));

        layout_colonne2->addWidget(new QLabel(proprio,this));
        layout_colonne2->addWidget(new QLabel(s_munition,this));

        setLayout(layout_principal);
        */
}

void InformationPiece::putInformationNeutre(QString nom, int pdv, int pdvMax, QString proprio){

    removeLayout();

    QVBoxLayout* layout_principal = new QVBoxLayout();

    nom = "Nom : "+nom;
    proprio = "Propriétaire : "+proprio;

    std::ostringstream oss_pdv;
    oss_pdv << "PDV : " << pdv << "/" << pdvMax;
    QString s_pdv = oss_pdv.str().c_str();

    layout_principal->addWidget(new QLabel(nom,this));
    layout_principal->addWidget(new QLabel(s_pdv,this));
    layout_principal->addWidget(new QLabel(proprio,this));

    setLayout(layout_principal);
}

void InformationPiece::putInformationVide() {
    removeLayout();
}

void InformationPiece::removeLayout()
{
    QLayout* layout = this->layout ();

    if (layout != 0) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != 0){
            QWidget* w = item->widget();
            if(w) {
                w->hide();
                delete w;
            }
        } // END WHILE

        delete layout;
    } // END IF

}
