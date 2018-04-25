#include "minimap.h"
#include <iostream>

using namespace std;

MiniMap::MiniMap(int longueur, int largeur, QWidget *parent) :
    QWidget(parent),
    _longueur(longueur),
    _largeur(largeur),
    _taille(longueur*largeur),
    _listeCase(_taille)
{
    this->setStyleSheet("background-color : white");
}

void MiniMap::paintEvent(QPaintEvent* e) {

    UNUSED(e);
    QPainter painter(this);

    int ligne,colonne;
    float width,heigth,demi_width,demi_heigth,quart_heigth;

    // On récupère la taille du widget
    int frame_width = this->contentsRect().width();
    int frame_heigth = this->contentsRect().height();

    // Calcul de la largeur d'un hexagone
    width = (float)frame_width/(float)_longueur - ((float)frame_width/2.0f)/((float)(_longueur*_longueur));;
    demi_width = width/2;

    // Calcul de la hauteur d'un hexagone
    heigth = (float)frame_heigth/(float)_largeur;
    heigth += ((float)frame_heigth/3.0f)/(float)_largeur - ((float)frame_heigth/4.0f)/((float)(_largeur*_largeur));

    demi_heigth = heigth/2.0f;
    quart_heigth = demi_heigth/2.0f;

    for(int i=0; i<_taille; i++) {
        ligne = i / _longueur;
        colonne = i - ligne*_longueur;

        ligne = _largeur - ligne - 1; // Pour que l'origine du repère soit en bas à gauche et non en haut à gauche

        // On dessine la case
        if(_listeCase[i].typecase.compare("PLAINE") == 0)
            painter.setBrush(QBrush(QColor(232,204,111))); // JAUNE

        if(_listeCase[i].typecase.compare("MONTAGNE") == 0)
            painter.setBrush(QBrush(QColor(154,109,79))); // MARRON

        if(_listeCase[i].typecase.compare("MER") == 0)
            painter.setBrush(QBrush(QColor(117,177,217))); // BLEU

        if(_listeCase[i].typecase.compare("MARAIS") == 0)
            painter.setBrush(QBrush(QColor(131,154,117))); // VERT

        if(_listeCase[i].typecase.compare("RECIF") == 0)
            painter.setBrush(QBrush(QColor(125,125,125))); // GRIS

        if(_listeCase[i].typecase.compare("VIDE") == 0)
            painter.setBrush(QBrush(QColor(0,0,0))); // NOIR

        painter.setPen(QColor(0,0,0)); // On remet le painter en noir pour que les bordures des cases soient noires

        if(ligne%2 == 0) {

            QPointF ligne_paire[6] = {

                QPointF(colonne*width+width,ligne*3*quart_heigth),

                QPointF((colonne+1)*width+demi_width,3*quart_heigth*ligne+quart_heigth),

                QPointF((colonne+1)*width+demi_width,3*quart_heigth*ligne+3*quart_heigth),

                QPointF(colonne*width+width,ligne*3*quart_heigth+heigth),

                QPointF(colonne*width+demi_width,3*quart_heigth*ligne+3*quart_heigth),

                QPointF(colonne*width+demi_width,3*quart_heigth*ligne+quart_heigth)

            };

            painter.drawConvexPolygon(ligne_paire,6);

        } // END IF

        else {

            QPointF ligne_impaire[6] = {

                QPointF(colonne*width+demi_width,ligne*3*quart_heigth),

                QPointF((colonne+1)*width,3*quart_heigth*ligne+quart_heigth),

                QPointF((colonne+1)*width,3*quart_heigth*ligne+3*quart_heigth),

                QPointF(colonne*width+demi_width,ligne*3*quart_heigth+heigth),

                QPointF(colonne*width,3*quart_heigth*ligne+3*quart_heigth),

                QPointF(colonne*width,3*quart_heigth*ligne+quart_heigth)
            };

            painter.drawConvexPolygon(ligne_impaire,6);

        } // END ELSE

        // On dessine un point de la couleur du joueur auquel la pièce appartient (s'il y en a une)
        if(_listeCase[i].piece){

            switch(_listeCase[i].couleur) {
            case 0 :
                painter.setBrush(QColor(255,0,0)); // ROUGE
                painter.setPen(QColor(255,0,0));
                break;
            case 1:
                painter.setBrush(QColor(0,0,255)); // BLEU
                painter.setPen(QColor(0,0,255));
                break;
            case 2:
                painter.setBrush(QColor(0,255,0)); // VERT
                painter.setPen(QColor(0,255,0));
                break;
            case 3:
                painter.setBrush(QColor(255,255,0)); // JAUNE
                painter.setPen(QColor(255,255,0));
                break;
            default:
                painter.setBrush(QColor(237,112,3)); // ORANGE
                painter.setPen(QColor(237,112,3));
            } // END SWITCH

            if(ligne%2 == 0)
                painter.drawEllipse(QPointF(colonne*width+width,3*quart_heigth*ligne+demi_heigth),demi_heigth/2.0f,demi_heigth/2.0f);
            else painter.drawEllipse(QPointF(colonne*width+demi_width,3*quart_heigth*ligne+demi_heigth),demi_heigth/2.0f,demi_heigth/2.0f);

        } // END IF

    } // END FOR
}

void MiniMap::updateCase(QString typecase, bool piece, int couleur, int i) {

    _listeCase[i].typecase = typecase;
    _listeCase[i].piece = piece;
    _listeCase[i].couleur = couleur;

    update();
}
