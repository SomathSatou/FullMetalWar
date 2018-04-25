#ifndef MODELISATIONUNITE_H
#define MODELISATIONUNITE_H
// IMPORT C++
#include <GL/glew.h>
#include "loadobj.h"
#include "camera.h"
#include "defineclass.h"
// IMPORT QT
#include <QOpenGLWidget>
#include <QMatrix4x4>
// VBO
#define BUFFER_OFFSET(i) ((void*)(i))

class ModelisationUnite : public QOpenGLWidget {

    Q_OBJECT
public slots:
    void parametrerModelisation(QString monunite, Couleur macouleur);

public:
    ModelisationUnite(QWidget * parent = Q_NULLPTR);
    ~ModelisationUnite();
protected:
    // Méthodes d'OpenGL
    void initializeGL()         override; // Equivaut au init
    void resizeGL(int w, int h) override; // Equivaut au redimensionnement
    void paintGL()              override; // Equivaut au modelisation



private:
    TypeOBJ qstringToOBJ(const QString &laChaine);

    void creerVBO();
    void afficherVBO();
    void VM_init();
    void colorerMonMesh();

    Couleur    maCouleur;
    TypeOBJ monObjet;
    Camera camera;
    QMatrix4x4 projection;
    GLuint monIndiceVBO;
    int    maTailleVBO;
    int    tailleX;
    int    tailleZ;
};

#endif // MODELISATIONUNITE_H
