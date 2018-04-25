#ifndef MODELISATIONJEU_H
#define MODELISATIONJEU_H
#define GL_GLEXT_PROTOTYPES

// IMPORT C++
#include <iostream>
#include <math.h>
#include "camera.h"
#include "loadobj.h"
#include "material.h"

// IMPORT QT
#include <QOpenGLWidget>
#include <QTimer>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QVector3D>
#include <QVector2D>

// PI
#define PI 3.1415926535
// VBO
#define BUFFER_OFFSET(i) ((void*)(i))

typedef struct {
    TypeOBJ typecase;
    TypeOBJ piece;
    int couleur;
} CaseModelisation;

typedef struct {
    GLuint monIndice;
    int tailleDeMonVBO;
} VextexBufferObject;


class ModelisationJeu : public QOpenGLWidget {
    /*
     * Classe ModelisationJeu
     * Le rôle de la classe ModelisationJeu est justement de modéliser l'ensemble du plateau.
     * Tout ceci se passe dans un contexte OpenGL
     */

    Q_OBJECT
    public slots:
        // Méthode qui compte le nobmre de FPS
        void compterFPS();
        void getKeyPressed(int key);
        void updateCase(QString typecase, QString piece, int couleur, int i); // Permet d'update dans la carte de la modélisation la case à la position i

    signals:
        void sendPositionClick(int x, int z);
        void sendPositionDeplacement(int x, int z);

    public:
        // Construction de la modélisationJeu avec tous les paramètres nécessaires
        ModelisationJeu(int longueur, int largeur, QWidget * parent = Q_NULLPTR, int fps = 60);
        ~ModelisationJeu();

    protected:
        // Méthodes d'OpenGL
        void initializeGL()         override; // Equivaut au init
        void resizeGL(int w, int h) override; // Equivaut au redimensionnement
        void paintGL()              override; // Equivaut au modelisation

        // Mouse click
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent * event) override;
        void mouseDoubleClickEvent(QMouseEvent *event) override;
        void wheelEvent(QWheelEvent * event) override;

    private:
        // Méthode permettant la mise à jour du contexte. Slot update() connecté par un QTimer avec timeout()
        void integrationFPS();
        // Méthode transformant les degrées en radian
        double dToR(double degree);
        // Méthode qui paramètre la caméra à chaque frame
        void VM_init();
        // Méthode qui modélise le plateau
        void creerPlateau();
        // Méthode qui modélise la pièce sur la case donnée
        void modeliserCase(int x, int y);
        // Méthode qui à partir d'un point à deux coordonnées retransmet la case sélectionnée
        QVector2D transcription(const QVector2D& pos);
        // Méthode utile pour le Ray mais à voir si on ne peut pas faire ça nativement
        void crossAndAssign(QVector3D& result, const QVector3D& a, const QVector3D& b);
        // Méthode qui sert à créer des VA
        void creationVA();
        // Méthode qui affiche
        void afficherVA();
        // Méthode qui sert à créer des VBO
        void creationVBO(GLuint &monMesh);
        // Méthode qui sert à afficher des VBO
        void afficherVBO(VextexBufferObject &monObjet);
        // Méthode qui sert à afficher des VBO selon une couleur
        void afficherVBO(VextexBufferObject &monObjet, int couleur);
        // Méthode qui sert à chager les Meshs
        void chargementDesMeshs();
        // Méthode qui interpetre Couleur de Joueur en glColor
        void colorerMonMesh(int couleur);
        // Méthode qui convertie un QString en TypeOBJ
        TypeOBJ qstringToOBJ(const QString& laChaine);

        int m_longueur;
        int m_largeur;
        int m_taille;
        std::vector<CaseModelisation> m_map;

        int m_frame;
        int numberOfFPS;

        double tmpX, tmpZ;
        GLuint m_caseSelectionnee;
        VextexBufferObject * mesMesh[6];
        std::vector<int> mesIndicesVBO;

        double width;
        double height;
        double x,y,z;
        double cursorX, cursorY;

        QMatrix4x4 projection;
        Camera camera;

        QTimer * m_timer;
        QTimer * m_compteurFPS;

        LoadOBJ monLecteur;

};

#endif // MODELISATIONJEU_H
