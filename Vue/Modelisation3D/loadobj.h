#ifndef LOADOBJ_H
#define LOADOBJ_H
//C++
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#define UNUSED(expr) do { (void)(expr); } while (0)

//QT
#include <QString>
#include <QTextStream>
#include <QVector3D>
#include <QVector2D>
#include <QFile>

//OpenGL
#include <GL/glew.h>


//Projet
#include "material.h"
#include "face.h"

// TypeEnum servant à déterminer quel fichier à charger selon l'objet demandé
typedef enum { PL, ME, MA, MO, RE, BA, BU, CH, CR, GR, MI, POD, POND, PONT, VE, NEANT} TypeOBJ;

class LoadOBJ {

public :
    LoadOBJ();
    bool chargerNouvelObjet(const TypeOBJ objet, int numero);
    void clear();


    // Méthodes traitement de requêtes
    const Material getMaterialByName(const std::string& name) const;
    unsigned int getIndiceMatByName(const std::string& name) const;

    // Méthodes d'accès
    std::vector<Material>&  getMaterial()  ;
    std::vector<GLfloat>& getMesVecteurs() ;
    std::vector<GLfloat>& getMesNormales() ;
    std::vector<GLfloat>& getMesCouleurs() ;
    std::vector<GLfloat>& getMesDonnees()  ;
    double getX() const;
    double getY() const;
    double getZ() const;
    std::string toString() const;

private:
    bool recupFace(QString line, int indice, int indiceFace, unsigned int indiceMat);
    void chargerMLT(QString& path);

    double maLongueurXMax;
    double maLongueurYMax;
    double maLongueurZMax;

    std::vector<Material> mesMaterials;
    std::vector<GLfloat>  mesVecteurs;
    std::vector<GLfloat>  mesNormales;
    std::vector<GLfloat>  mesCouleurs;
    std::vector<GLfloat>  mesDonneesConcatenees;
};

#endif // LOADOBJ_H
