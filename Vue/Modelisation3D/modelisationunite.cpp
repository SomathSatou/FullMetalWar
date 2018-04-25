#include "modelisationunite.h"
#include "Moteur/Piece/Piece.h"

ModelisationUnite::ModelisationUnite(QWidget * parent): QOpenGLWidget(parent), camera(), tailleX(0), tailleZ(0) {}
ModelisationUnite::~ModelisationUnite(){ glDeleteBuffers(1, &monIndiceVBO); }

void ModelisationUnite::initializeGL(){
    glClearColor(0.937f, 0.925f, 0.905f, 1.f);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      // Problem: glewInit failed, something is seriously wrong.
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
//    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    // LUMIERE
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    GLfloat  lumiere[4]     =   {  10,    1,   10, 1};      // A MODIFIER AU BESOIN
    GLfloat  ambient[4]  	=	{0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat  diffuse[4] 	=	{0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat  specular[4] 	=	{ 100,  100,  100, 1.0f};
    GLfloat  percent[3]     = 	{0.2f, 0.2f, 0.2f};

    glLightfv(GL_LIGHT0, GL_POSITION, lumiere);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, percent);

    // CAMERA
    int         ratioX = (double)tailleX/0.4; if(ratioX == 0) ratioX = 1;
    QVector3D position(-0.5 * ratioX,1,-0.75 * ratioX);
    QVector3D pointing(0, 0, 0);
    QVector3D up(0, 1, 0);
    camera.setPosition(position);
    camera.setLookPoint(pointing);
    camera.setUp(up);
    camera.mettreAJourLaMatrice();
}

void    ModelisationUnite::colorerMonMesh(){
    float r = 0, g = 0, b = 0;
    switch(maCouleur){
        case Couleur::ROUGE: r = 1; break;                           // ROUGE
        case Couleur::BLEU: b = 1; break;                           // BLEU
        case Couleur::VERT: g = 1; break;                           // VERT
        case Couleur::JAUNE: r = 1; g = 1; break;                    // JAUNE
        case Couleur::NEUTRE: r=0.5f; g=0.5f; b=0.5f; break;          // NEUTRE
        case Couleur::BLANC: r = 1; g = 1; b = 1; break;             // BLANC
        case Couleur::NOIR: break;                                  // NOIR
        case Couleur::ORANGE: r = 1; g = 0.5f; break;                 // ORANGE
        case Couleur::MAUVE: r = 1; b = 0.5f;break;                  // MAUVE
        case Couleur::GRIS: r = 0.5f; g = 0.5f; b = 0.5f; break;    // GRIS
        case Couleur::CYAN: g = 1; b = 1; break;                   // CYAN
    }
    glColor3f(r,g,b);
}

void ModelisationUnite::parametrerModelisation(QString monunite, Couleur macouleur){
    monObjet = qstringToOBJ(monunite);
    std::cout << monObjet << " "  << NEANT << std::endl;
    if(monObjet != NEANT) {
        maCouleur = macouleur;
        creerVBO();
    }
    else glDeleteBuffers(1, &monIndiceVBO);
    update();
}

void ModelisationUnite::paintGL(){
    VM_init();
    afficherVBO();
}

void ModelisationUnite::VM_init()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(90,0,1,0);
    glLoadIdentity();
    glLoadMatrixf(camera.constData());
}

void ModelisationUnite::resizeGL(int w, int h){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(-1,-1, w, h);
    glMatrixMode(GL_PROJECTION);
    projection.setToIdentity();
    projection.perspective(70.f, ((GLfloat)w/(GLfloat)h), 0.1f, 1000);
    glLoadMatrixf(projection.constData());
    glMatrixMode(GL_MODELVIEW);
}

void ModelisationUnite::creerVBO(){
    LoadOBJ loader;
    loader.chargerNouvelObjet(monObjet,0);
    tailleX = loader.getX();
    tailleZ = loader.getZ();
//    std::cout << "Longueur max X : " << loader.getX() << " Y : " << loader.getY() << " Z : " << loader.getZ() << std::endl;

    glGenBuffers(1, &monIndiceVBO);
    // BUFFER DE VERTICES, NORMALES et COULEURS
    glBindBuffer(GL_ARRAY_BUFFER, monIndiceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * loader.getMesDonnees().size(), &loader.getMesDonnees().front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    maTailleVBO = loader.getMesDonnees().size()/6;
}

void ModelisationUnite::afficherVBO(){
    if(glIsBuffer(monIndiceVBO) == GL_TRUE){
        colorerMonMesh();
        // VERTICES
        glBindBuffer(GL_ARRAY_BUFFER, monIndiceVBO);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 9,    BUFFER_OFFSET(0));
        // NORMALES
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT,    sizeof(GLfloat) * 9,    BUFFER_OFFSET(12));

        // MODELISATION
        glDrawArrays(GL_TRIANGLES, 0,  maTailleVBO);
        // FERMETURE
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        // VIDE BUFFER
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

TypeOBJ ModelisationUnite::qstringToOBJ(const QString &laChaine){
    TypeOBJ toReturn;
    std::string laChaineConvertie = laChaine.toUpper().toStdString();
         if(laChaineConvertie.compare("PLAINE")==0)     toReturn = PL;
    else if(laChaineConvertie.compare("MARAIS")==0)     toReturn = MA;
    else if(laChaineConvertie.compare("MONTAGNE")==0)   toReturn = MO;
    else if(laChaineConvertie.compare("RECIF")==0)      toReturn = RE;
    else if(laChaineConvertie.compare("MER")==0)        toReturn = ME;
    else if(laChaineConvertie.compare("BARGE")==0)      toReturn = BA;
    else if(laChaineConvertie.compare("BULLE")==0)      toReturn = BU;
    else if(laChaineConvertie.compare("CHAR")==0)       toReturn = CH;
    else if(laChaineConvertie.compare("CRABE")==0)      toReturn = CR;
    else if(laChaineConvertie.compare("GROSTAS")==0)    toReturn = GR;
    else if(laChaineConvertie.compare("MINERAI")==0)    toReturn = MI;
    else if(laChaineConvertie.compare("PODE")==0)       toReturn = POD;
    else if(laChaineConvertie.compare("PONDEUSE")==0)   toReturn = POND;
    else if(laChaineConvertie.compare("PONTON")==0)     toReturn = PONT;
    else if(laChaineConvertie.compare("VEDETTE")==0)    toReturn = VE;
    else toReturn = NEANT;

    return toReturn;
}
