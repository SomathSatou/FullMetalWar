#include "modelisationjeu.h"

using namespace std;

ModelisationJeu::ModelisationJeu(int longueur, int largeur, QWidget *parent, int fps):
    QOpenGLWidget(parent),
    m_longueur(longueur),
    m_largeur(largeur),
    m_taille(longueur*largeur),
    m_map(m_taille),
    m_frame(fps),
    x(0),
    y(0),
    z(0),
    cursorX(0),
    cursorY(0),
    camera(),
    m_timer(0),
    m_compteurFPS(0),
    monLecteur()
{}

ModelisationJeu::~ModelisationJeu(){ delete m_timer; }

// INITIALISATION
void    ModelisationJeu::initializeGL()
{
    // Initialisation Glew
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    //    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    //---------------------
    glClearColor(0.75f, 0.77f, 0.71f, 1.f);
    integrationFPS();           // ICI POUR DESACTIVER LE RAFRAICHISSEMENT
    mesIndicesVBO = std::vector<int>(m_taille,99);
    chargementDesMeshs();
    //std::cout << monLecteur.toString() << std::endl;
    /*
    QVector3D p1(-10,0,-10);
    QVector3D p2(m_largeur*2,0,-10);
    QVector3D p3(m_largeur*2, 0, m_longueur*-sin(60)*2);
    QVector3D p4(-10, 0, m_longueur*-sin(60)*2);
    QMatrix4x4 rot; rot.rotate(-135.0, 0, 1, 0);
    camera.setPositionMax((p1 * rot), (p2 * rot), (p3 * rot), (p4 * rot));*/

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

    //  POUR LA MODELISATION
    double angle = dToR(60);
    double longueur = 1 ;       //* tailleCase
    double cos60 = cos(angle);  //* tailleCase
    double sin60 = sin(angle);  //* tailleCase

    // DISPLAY LIST
    //CASE SELECTIONNEE
    tmpX = -1; tmpZ = -1;
    m_caseSelectionnee = glGenLists(1);
    glNewList(m_caseSelectionnee, GL_COMPILE);
    glColor3f(1,1,1);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glVertex3f(longueur,    0,      0);
    glVertex3f(cos60,       0,      sin60);
    glVertex3f(-cos60,      0,      sin60);
    glVertex3f(-longueur,   0,      0);
    glVertex3f(-cos60,      0,      -sin60);
    glVertex3f(cos60,       0,      -sin60);
    glVertex3f(longueur,    0,      0);
    glEnd();
    glEndList();

    // CAMERA
    double dist = 10 * sqrt(1 / 3.0);
    QVector3D position(dist,dist,dist);
    QVector3D pointing(0, 0, 0);
    QVector3D up(0, 1, 0);

    //QMatrix4x4 m;
    // m.rotate(135, 0.0, 1.0, 0.0);

    camera.setPosition(position);
    camera.setLookPoint(pointing);
    camera.setUp(up);
    camera.mettreAJourLaMatrice();
}

// METHODES DE CHARGEMENT DES MESHS ET DE LEUR PARAMÉTRAGE
void    ModelisationJeu::colorerMonMesh(int couleur){
    float r = 0, g = 0, b = 0;
    switch(couleur){
    case 0: r = 1; break;                           // ROUGE
    case 1: b = 1; break;                           // BLEU
    case 2: g = 1; break;                           // VERT
    case 3: r = 1; g = 1; break;                    // JAUNE
    case 4: break;                                  // NEUTRE
    case 5: r = 1; g = 1; b = 1; break;             // BLANC
    case 6: break;                                  // NOIR
    case 7: r = 1; g = 0.5f; break;                 // ORANGE
    case 8: r = 1; b = 0.5f;break;                  // MAUVE
    case 9: r = 0.5f; g = 0.5f; b = 0.5f; break;    // GRIS
    case 10: g = 1; b = 1; break;                   // CYAN
    }
    glColor3f(r,g,b);
}

void    ModelisationJeu::chargementDesMeshs(){
    mesMesh[5] = new VextexBufferObject[10]; // Pour les pièces
    for(int i = PL; i <= VE; i++){
        switch (i) {
        case PL:
            mesMesh[0] = new VextexBufferObject[3];
            monLecteur.chargerNouvelObjet(PL,0);
            creationVBO(mesMesh[0][0].monIndice);
            mesMesh[0][0].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;

            monLecteur.chargerNouvelObjet(PL,1);
            creationVBO(mesMesh[0][1].monIndice);
            mesMesh[0][1].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;

            monLecteur.chargerNouvelObjet(PL,2);
            creationVBO(mesMesh[0][2].monIndice);
            mesMesh[0][2].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;

            break;
        case ME:
            mesMesh[1] = new VextexBufferObject[5];
            monLecteur.chargerNouvelObjet(ME,0);
            creationVBO(mesMesh[1][0].monIndice);
            mesMesh[1][0].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;

            monLecteur.chargerNouvelObjet(ME,1);
            creationVBO(mesMesh[1][1].monIndice);
            mesMesh[1][1].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;

            monLecteur.chargerNouvelObjet(ME,2);
            creationVBO(mesMesh[1][2].monIndice);
            mesMesh[1][2].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;

            monLecteur.chargerNouvelObjet(ME,3);
            creationVBO(mesMesh[1][3].monIndice);
            mesMesh[1][3].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;

            monLecteur.chargerNouvelObjet(ME,4);
            creationVBO(mesMesh[1][4].monIndice);
            mesMesh[1][4].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;

            break;
        case MA:
            mesMesh[2] = new VextexBufferObject[2];
            monLecteur.chargerNouvelObjet(MA,0);
            creationVBO(mesMesh[2][0].monIndice);
            mesMesh[2][0].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;


            monLecteur.chargerNouvelObjet(MA,1);
            creationVBO(mesMesh[2][1].monIndice);
            mesMesh[2][1].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;
            break;
        case MO:
            mesMesh[3] = new VextexBufferObject[3];
            monLecteur.chargerNouvelObjet(MO,0);
            creationVBO(mesMesh[3][0].monIndice);
            mesMesh[3][0].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;

            monLecteur.chargerNouvelObjet(MO,1);
            creationVBO(mesMesh[3][1].monIndice);
            mesMesh[3][1].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;

            monLecteur.chargerNouvelObjet(MO,2);
            creationVBO(mesMesh[3][2].monIndice);
            mesMesh[3][2].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;
            break;
        case RE:
            mesMesh[4] = new VextexBufferObject[2];
            monLecteur.chargerNouvelObjet(RE,0);
            creationVBO(mesMesh[4][0].monIndice);
            mesMesh[4][0].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;


            monLecteur.chargerNouvelObjet(RE,1);
            creationVBO(mesMesh[4][1].monIndice);
            mesMesh[4][1].tailleDeMonVBO = monLecteur.getMesDonnees().size()/9.0;
            break;
        case BA:
            monLecteur.chargerNouvelObjet(BA,0);
            creationVBO(mesMesh[5][0].monIndice);
            mesMesh[5][0].tailleDeMonVBO = monLecteur.getMesDonnees().size()/6.0;
            break;
        case BU:
            monLecteur.chargerNouvelObjet(BU,0);
            creationVBO(mesMesh[5][1].monIndice);
            mesMesh[5][1].tailleDeMonVBO = monLecteur.getMesDonnees().size()/6.0;
            break;
        case CH:
            monLecteur.chargerNouvelObjet(CH,0);
            creationVBO(mesMesh[5][2].monIndice);
            mesMesh[5][2].tailleDeMonVBO = monLecteur.getMesDonnees().size()/6.0;
            break;
        case CR:
            monLecteur.chargerNouvelObjet(CR,0);
            creationVBO(mesMesh[5][3].monIndice);
            mesMesh[5][3].tailleDeMonVBO = monLecteur.getMesDonnees().size()/6.0;
            break;
        case GR:
            monLecteur.chargerNouvelObjet(GR,0);
            creationVBO(mesMesh[5][4].monIndice);
            mesMesh[5][4].tailleDeMonVBO = monLecteur.getMesDonnees().size()/6.0;
            break;
        case MI:
            monLecteur.chargerNouvelObjet(MI,0);
            creationVBO(mesMesh[5][5].monIndice);
            mesMesh[5][5].tailleDeMonVBO = monLecteur.getMesDonnees().size()/6.0;
            break;
        case POD:
            monLecteur.chargerNouvelObjet(POD,0);
            creationVBO(mesMesh[5][6].monIndice);
            mesMesh[5][6].tailleDeMonVBO = monLecteur.getMesDonnees().size()/6.0;
            break;
        case POND:
            monLecteur.chargerNouvelObjet(POND,0);
            creationVBO(mesMesh[5][7].monIndice);
            mesMesh[5][7].tailleDeMonVBO = monLecteur.getMesDonnees().size()/6.0;
            break;
        case PONT:
            monLecteur.chargerNouvelObjet(PONT,0);
            creationVBO(mesMesh[5][8].monIndice);
            mesMesh[5][8].tailleDeMonVBO = monLecteur.getMesDonnees().size()/6.0;
            break;
        case VE:
            monLecteur.chargerNouvelObjet(VE,0);
            creationVBO(mesMesh[5][9].monIndice);
            mesMesh[5][9].tailleDeMonVBO = monLecteur.getMesDonnees().size()/6.0;
            break;
        }
    }
}

void    ModelisationJeu::creationVA(){
    monLecteur.chargerNouvelObjet(MO, 0);
}

void    ModelisationJeu::afficherVA(){
    glColor3f(1,1,1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 9, &monLecteur.getMesDonnees()[0]);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT,  sizeof(GLfloat) * 9,   &monLecteur.getMesDonnees()[3]);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, sizeof(GLfloat) * 9,  &monLecteur.getMesDonnees()[6]);

    glDrawArrays(GL_TRIANGLES, 0, monLecteur.getMesDonnees().size()/9);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void    ModelisationJeu::creationVBO(GLuint &monMesh){
    glGenBuffers(1, &monMesh);
    // BUFFER DE VERTICES, NORMALES et COULEURS
    glBindBuffer(GL_ARRAY_BUFFER, monMesh);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * monLecteur.getMesDonnees().size(), &monLecteur.getMesDonnees().front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void    ModelisationJeu::afficherVBO(VextexBufferObject &monMesh){
    glColor3f(1,1,1);
    // VERTICES
    glBindBuffer(GL_ARRAY_BUFFER, monMesh.monIndice);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 9,    BUFFER_OFFSET(0));
    // NORMALES
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT,    sizeof(GLfloat) * 9,    BUFFER_OFFSET(12));
    // COULEURS
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT,  sizeof(GLfloat) * 9,    BUFFER_OFFSET(24));
    // MODELISATION
    glDrawArrays(GL_TRIANGLES, 0,  monMesh.tailleDeMonVBO);
    // FERMETURE
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    // VIDE BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void    ModelisationJeu::afficherVBO(VextexBufferObject &monMesh, int couleur){
    colorerMonMesh(couleur);
    // VERTICES
    glBindBuffer(GL_ARRAY_BUFFER, monMesh.monIndice);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 9,    BUFFER_OFFSET(0));
    // NORMALES
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT,    sizeof(GLfloat) * 9,    BUFFER_OFFSET(12));
    // MODELISATION
    glDrawArrays(GL_TRIANGLES, 0,  monMesh.tailleDeMonVBO);
    // FERMETURE
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    // VIDE BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// REDIMENSIONNEMENT
void    ModelisationJeu::resizeGL(int w, int h)
{
    width = w; height = h;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(-1,-1, w, h);
    glMatrixMode(GL_PROJECTION);
    projection.setToIdentity();
    projection.perspective(70.f, ((GLfloat)w/(GLfloat)h), 0.1f, 1000);
    glLoadMatrixf(projection.constData());
    glMatrixMode(GL_MODELVIEW);
}

// MODELISATION
void    ModelisationJeu::paintGL()
{
    VM_init();
    creerPlateau();
}

// VM
void    ModelisationJeu::VM_init()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(90,0,1,0); // Pour se positionner en main droite
    glLoadIdentity();
    glLoadMatrixf(camera.constData());
}

// ACTIVER LES FPS
void    ModelisationJeu::integrationFPS(){
    numberOfFPS = 0;
    if(m_timer != 0) delete m_timer;
    if(m_compteurFPS != 0) delete m_compteurFPS;
    m_timer = new QTimer(this);
    m_compteurFPS = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(m_compteurFPS, SIGNAL(timeout()), this, SLOT(compterFPS()));
    int duration = (1/(double)m_frame) * 1000;
    m_timer->start(duration);
    m_compteurFPS->start(1000);
}

// AFFICHER LES FPS
void    ModelisationJeu::compterFPS(){
    //std::cout << "FPS : " << numberOfFPS << std::endl;
    numberOfFPS = 0;
}

// MODELISATION DU PLATEAU
void    ModelisationJeu::creerPlateau(){
    // Compteur FPS
    numberOfFPS++;
    // Compteur FPS
    double angle = dToR(60);
    int   longueur = m_longueur;
    int    largeur = m_largeur;
    double sin60 = sin(angle);  //* tailleCase
    double longueurReelle = 1;  //* tailleCase

    glPushMatrix();
    glRotatef(135,0,1,0);
    glTranslatef(longueurReelle, 0, sin60);
    for(int i = 0; i < longueur; i++){
        glPushMatrix();
        for(int j = 0; j < largeur; j++){
            if(tmpX == i && tmpZ == j){
                glPushMatrix();
                glTranslatef(0,0.05f,0);
                glCallList(m_caseSelectionnee);
                glPopMatrix();
            }
            modeliserCase(i,j);
            if(j%2 == 0)
                glTranslatef(longueurReelle * 1.5f, 0, sin60);
            else
                glTranslatef(longueurReelle * 1.5f, 0, -sin60);
        }
        glPopMatrix();
        glTranslatef(0,0,sin60 * 2);
    }
    glPopMatrix();
    glPushMatrix();
    glRotatef(135.0,0,1,0);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3d(1.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);

    glColor3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);

    glColor3d(0.0, 0.0, 1.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 1.0);
    glEnd();
    glPopMatrix();
}

void    ModelisationJeu::modeliserCase(int i, int j){
    const CaseModelisation c   = m_map[m_longueur*j+i];

    int randomValue = -1;
    int monTypeDeCase =         c.typecase;
    int monIndiceDansLesVBO =   m_longueur*j + i;
    int monIndice =             mesIndicesVBO.at(monIndiceDansLesVBO);

    if(monIndice == 99) {
        switch (c.typecase) {
        case PL: randomValue = rand()%3; break;
        case MA: randomValue = rand()%2; break;
        case MO: randomValue = rand()%3; break;
        case RE: randomValue = rand()%2; break;
        case ME: randomValue = rand()%5; break;
        default: break;
        }
        mesIndicesVBO.at(monIndiceDansLesVBO) = randomValue;
        monIndice = randomValue;
    }
    afficherVBO(mesMesh[monTypeDeCase][monIndice]);
    glPushMatrix();
    glTranslatef(0,0.1,0);

    if(c.piece != NEANT){
        if(c.piece == MI || c.piece == PONT)
            afficherVBO(mesMesh[5][c.piece-5]);
        else afficherVBO(mesMesh[5][c.piece-5],c.couleur);
    }

    glPopMatrix();
}

// EVENTS DE LA SOURIS
void    ModelisationJeu::mouseDoubleClickEvent(QMouseEvent *event){
    double x = event->x();
    double y = event->y();
    QVector3D view = (camera.getLookPoint() - camera.getPosition());
    view.normalize();
    QVector3D h; crossAndAssign(h, view, (camera.getUp()));
    h.normalize();
    QVector3D v; crossAndAssign(v, view, h);
    v.normalize();
    double rad = 70.0 * PI / 180.0;                 // 70.0 = fovy
    double vLength = tan( rad / 2.0 ) * 0.1f;       // 0.1f = nearClamping
    double hLength = vLength * (width / height);
    v *= (float)vLength;
    h *= (float)hLength;
    x -= width  / 2.0;
    y -= height / 2.0;
    x /= (width  / 2.0);
    y /= (height / 2.0);
    QVector3D pos;
    pos = camera.getPosition() + view*0.1f + h*x + v*y;
    QVector3D dir;
    dir = pos - camera.getPosition();
    while(pos.y() > 0){
        pos.setX((float)(pos.x() - fabs(dir.x())));
        pos.setY((float)(pos.y() - fabs(dir.y()))); if(pos.y() < 0) pos.setY(0);
        pos.setZ((float)(pos.z() - fabs(dir.z())));
    }
    QVector3D newPos(pos.x(),pos.y(),pos.z());
    QMatrix4x4 m;
    m.rotate(135.0,0,1,0);
    newPos = newPos * m;
    QVector2D pos2D(newPos.x(), newPos.z());
    transcription(pos2D);

    /*
    QVector3D nouvellePosCam = camera.getDir();
    nouvellePosCam.setX(newPos.x() + nouvellePosCam.x()/2.0);
    nouvellePosCam.setY(newPos.y() + nouvellePosCam.y()/2.0);
    nouvellePosCam.setZ(newPos.z() + nouvellePosCam.z()/2.0);
    std::cout << "Nouvelle Pos Cam : " << nouvellePosCam.x() << " " << nouvellePosCam.y() << " " << nouvellePosCam.z() << std::endl;
    camera.setPosition(nouvellePosCam);
    camera.setLookPoint(newPos);
    camera.mettreAJourLaMatrice();*/
}

void    ModelisationJeu::mousePressEvent(QMouseEvent *event){
    x = event->x();
    y = event->y();
    QVector2D position_carte;
    QVector3D view = (camera.getLookPoint() - camera.getPosition());
    view.normalize();
    QVector3D h; crossAndAssign(h, view, (camera.getUp()));
    h.normalize();
    QVector3D v; crossAndAssign(v, view, h);
    v.normalize();
    double rad = 70.0 * PI / 180.0; // 70.0 = fovy
    double vLength = tan( rad / 2.0 ) * 0.1f; // 0.1f = nearClamping
    double hLength = vLength * (width / height);
    v *= (float)vLength;
    h *= (float)hLength;
    x -= width  / 2.0;
    y -= height / 2.0;
    x /= (width  / 2.0);
    y /= (height / 2.0);
    QVector3D pos;
    pos = camera.getPosition() + view*0.1f + h*x + v*y;
    QVector3D dir;
    dir = pos - camera.getPosition();

    x = event->x();
    y = event->y();

    while(pos.y() > 0){
        pos.setX((float)(pos.x() - fabs(dir.x())));
        pos.setY((float)(pos.y() - fabs(dir.y()))); if(pos.y() < 0) pos.setY(0);
        pos.setZ((float)(pos.z() - fabs(dir.z())));
    }
    QVector3D newPos(pos.x(),pos.y(),pos.z());
    QMatrix4x4 m;
    m.rotate(135.0,0,1,0);
    newPos = newPos * m;
    QVector2D pos2D(newPos.x(), newPos.z());
    position_carte = transcription(pos2D);


    if(event->button() == Qt::LeftButton){
        //std::cout << "debug click ***************************************************************"<<std::endl
        //          << position_carte.x()<< " - " << position_carte.y() <<std::endl;
        emit sendPositionClick((int)position_carte.x(),(int)position_carte.y());
    }

    if(event->button() == Qt::RightButton){
//        std::cout << "debug click ***************************************************************"<<std::endl
//                  << position_carte.x()<< " - " << position_carte.y() <<std::endl;
        int x((int)position_carte.x());
        int y((int)position_carte.y());
        if(y==m_longueur){
            y=m_longueur-1;
//            std::cout << "\n\n\tcorrection y(modelisationjeu.cpp ligne 560)\n";
        }
        emit sendPositionDeplacement(x,y);
    }

}

void    ModelisationJeu::mouseMoveEvent(QMouseEvent *event){

    double translateX = 0;
    double translateZ = 0;

    double other_x = event->x();
    double other_y = event->y();

    if(other_x < x && other_y < y){ translateX = 0.5; translateZ = 0.5; }
    if(other_x < x && other_y > y){ translateX = 0.5; translateZ =  -0.5; }
    if(other_x > x && other_y < y){ translateX = -0.5;  translateZ = 0.5; }
    if(other_x > x && other_y > y){ translateX = -0.5;  translateZ = -0.5;  }
    camera.translatePosition(translateX, 0, translateZ);
    camera.translateLookPoint(translateX, 0, translateZ);

    x = event->x();
    y = event->y();
}

void    ModelisationJeu::wheelEvent(QWheelEvent *event){
    int y = 0;
    if(event->delta() > 0){
        if(camera.getPosition().y() > 1)
            y = -1;
    }
    else {
        if(camera.getPosition().y() < 25)
            y = 1;
    }
    camera.translatePosition(0,y,0);
}

// ALGORITHME DE TRANSCRIPTION POINT OPENGL HEXAGONE
QVector2D ModelisationJeu::transcription(const QVector2D &pos){
    // Paramètres de l'hexagone
    double longueur          = 2;
    double longueurParDeux   = longueur/2;
    double sin60             = sin(dToR(60));
    double cos60             = cos(dToR(60));

    // Points
    QVector2D pointUn        ;
    QVector2D pointDe        ;
    QVector2D pointTr        ;
    double    distanceXPreca = 0;
    double    distanceZPreca = 0;


    // paramètres pour X
    double tailleLigne       = 2;
    double zoneSureX         = tailleLigne/(double)2;
    double zoneIncertaineX   = tailleLigne/(double)4;
    // paramètres pour Y
    double tailleColonne     =  2 * sin(dToR(60));

    // Zone externe au plateau
    double zoneHorsX         = (m_largeur - 2) * (zoneSureX+zoneIncertaineX) + 2 * tailleLigne; // [O, 4 + (n-2 cases) * 1.5] 4 correspondant à la longeur de la première case et à la dernière case du plateau
    double zoneHorsZ         = (m_longueur * tailleColonne); // [0, longueur*tailleColonne + (si ligne pair) tailleColonne/2]
    double dernierX          = (m_largeur);  // Correspond au dernier X possible
    double dernierZ          = (m_longueur); // Correspond au dernier Y possible

    // Initialisation des variables servant de coordonnées au clic, et à l'emplacement de la case dans le plateau
    double  x                = pos.x();
    double  z                = pos.y();
    double  numeroLigne      = 0;
    double  numeroColonne    = 0;

    // Variables utiles uniquement pour l'algorithme
    int    alternance        = 1; // Quand c'est 0, on soustrait la zoneSureX, si c'est 1 on soustrait la zoneIncertaine
    int    operationFinie    = 0; // Quand il n'est plus possible de retrancher zoneSure et zoneIncertaine, on arrête
    int    valeurEnt         = 0; // Boolean qui détermine si numeroLigne est un nombre naturel ou décimal, 0 pour faux, 1 pour vrai

    /*
     * On détermine si nous sommes dans une zone certaine (rectangle de l'hexagone) ou incertaine (triangles de l'hexagone)
     * Si valeurEnt est faux, x nous permet de savoir entre quelles lignes le clic se joue
     * Sinon x nous donne la ligne directement concernée
     * Pour ce faire, on retranche la longueur d'une zone certaine puis la longueur d'une zone incertaine en alternant les deux
     * En zone incertaine, notre numéro de ligne est décimal 0.5, 1.5, 2.5 etc.
     * En zone certaine,   notre numéro de ligne est entier.
     */
    while(operationFinie == 0){
        if(alternance){
            if( x >= zoneIncertaineX ){
                x-=zoneIncertaineX;
                numeroLigne = (int)numeroLigne;
                numeroLigne++;
                alternance=0;
            } else {
                operationFinie = 1;
                valeurEnt = 0;
            }
        } else {
            if( x >= zoneSureX ){
                x-=zoneSureX;
                numeroLigne+=0.5;
                alternance=1;
            } else {
                operationFinie = 1;
                valeurEnt = 1;
            }
        }
    }
    if(pos.x() <= zoneIncertaineX){ numeroLigne = 1;        valeurEnt = 1; } // EXCEPTION si le clic est en zone négative      (à l'extérieur du plateau)
    if(pos.x() >= zoneHorsX){       numeroLigne = dernierX; valeurEnt = 1; } // EXCEPTION si le clic est en hors zone positive (à l'extérieur du plateau)

    /*
     * Selon si la valeur est entière ou non, le déroulement va être différent
     * Si la valeur est entière, il nous suffit juste de retrancher le Z avec la largeur d'une case jusqu'à obtenir la bonne colonne
     * Cependant, le traitement est différent si le numéro de la ligne est pair ou impair
     * Dans le cas d'une ligne paire, on doit retrancher la moitié d'une largeur de case (Choix arbitraire)
     * Si la valeur est décimale, il nous faut comparer
     */
    if(valeurEnt){
        operationFinie = 0;
        if( (((int)numeroLigne)%2) == 0 ){
            z-= tailleColonne/2.0;          // Retranchement de la moitié de largeur de case
            zoneHorsZ+= tailleColonne/2.0;  // Ajout de la moitié d'une taille de colonne à la zoneHorsZ
        }
        while(operationFinie == 0){
            if(z < tailleColonne )
                operationFinie = 1;
            z-=tailleColonne;
            numeroColonne++;
        }
        if(pos.y() <= tailleColonne) numeroColonne = 1;        // EXCEPTION le clic est en zone négative      (à l'extérieur du plateau)
        if(pos.y() > zoneHorsZ)      numeroColonne = dernierZ; // EXCEPTION le clic est en hors zone positive (à l'extérieur du plateau)
    }
    else {
        operationFinie = 0;
        while(operationFinie == 0){
            if(z < tailleColonne )
                operationFinie = 1;
            z-=tailleColonne;
            numeroColonne++; // Nous récupérons le numéro de la colonne pour savoir entre quelles cases le clic se joue
        }
        valeurEnt = numeroLigne; // Nous récupérons le numéro de la ligne du dessous
        distanceXPreca = (valeurEnt) * (cos60 + longueurParDeux);
        distanceZPreca = sin60 * (2 * (numeroColonne-1));

        /*
         * Nous retrouvons les points correspondants au haut de l'hexagone  de la ligne du dessous
         *                        pointDeux    x
         *  /\ /\                             / \
         * |  |  |                           /   \
         *  \/ \/                   pointUn x     x pointTrois
         *  |Ici|
         *   \ /
         */
        pointUn.setX(  distanceXPreca );
        pointDe.setX(  distanceXPreca + cos60 );
        pointTr.setX(  distanceXPreca );

        if(((int)numeroLigne)%2 == 0){
            pointUn.setY(  distanceZPreca + sin60);
            pointDe.setY(  distanceZPreca + sin60 + sin60);
            pointTr.setY(  distanceZPreca + sin60 * 2 + sin60);
        } else {
            pointUn.setY(  distanceZPreca );
            pointDe.setY(  distanceZPreca + sin60 );
            pointTr.setY(  distanceZPreca + sin60 * 2);
        }
        /* Nous allons avoir deux cas de figures
         * Soit le clic est avant le pointDeux (donc il ne concerne que la première partie de l'hexagone)
         * Soit le clic est après le pointDeux (donc il ne concerne que la deuxième partie de l'hexagone)
         * On va chercher dans les deux cas à faire la projection du point cliqué sur la droite définie
         * par les points de l'hexagone
         */
        if(pos.y() < pointDe.y()){
            // On va récupérer l'équation de la droite affine
            double coeffDirect = (pointDe.x() - pointUn.x()) / (pointDe.y() - pointUn.y());
            double ordonneeOri = pointUn.x() - (coeffDirect * pointUn.y());
            // On récupère le projeté du point sur la droite
            double imageDeZ    = (coeffDirect * pos.y()) + ordonneeOri;
            // On compare les X
            if(pos.x() > imageDeZ){
                if(((int)numeroLigne)%2 == 0){
                    numeroLigne = (int)numeroLigne +1;
                }
                else {
                    numeroColonne--;
                    numeroLigne = (int)numeroLigne +1;
                }
            } else if(pos.x() < imageDeZ){
                if(((int)numeroLigne)%2 == 0){ numeroLigne = (int)numeroLigne; }
                else numeroLigne = (int)numeroLigne;
            }
        } else if (pos.y() >= pointDe.y()){
            // On va récupérer l'équation de la droite affine
            double coeffDirect = (pointTr.x() - pointDe.x()) / (pointTr.y() - pointDe.y());
            double ordonneeOri = pointDe.x() - (coeffDirect * pointDe.y());
            // On récupère le projeté du point sur la droite
            double imageDeZ    = (coeffDirect * pos.y()) + ordonneeOri;
            // On compare les X
            if(pos.x() > imageDeZ){
                if(((int)numeroLigne)%2 == 0){
                    numeroLigne = (int)numeroLigne +1;
                    numeroColonne++;
                }
                else numeroLigne = (int)numeroLigne +1;
            } else if(pos.x() < imageDeZ){
                if(((int)numeroLigne)%2 == 0){ numeroLigne = (int)numeroLigne; }
                else numeroLigne = (int)numeroLigne;
            }
        }
    }


    tmpZ = numeroLigne -1;
    tmpX = numeroColonne -1;

    return QVector2D(tmpX, tmpZ); // Je ne suis plus sûr de l'ordre WARNING
}

// METHODES ININTERESSANTES
void    ModelisationJeu::crossAndAssign(QVector3D& result, const QVector3D& a, const QVector3D& b) {
    float tempX = a.y() * b.z() - a.z() * b.y();
    float tempY = a.z() * b.x() - a.x() * b.z();
    float tempZ = a.x() * b.y() - a.y() * b.x();
    result.setX(tempX);
    result.setY(tempY);
    result.setZ(tempZ);
}

double    ModelisationJeu::dToR(double degree){ return (degree * PI/180); }

void ModelisationJeu::getKeyPressed(int key) {
    int x = 0, y = 0, z = 0;
    switch(key){
    case Qt::Key_Left:  x = -1; z =  1; break; //  z++; x--;
    case Qt::Key_Right: x =  1; z = -1; break; //  z--; x++;
    case Qt::Key_Down:  x =  1; z =  1; break; //  x++; z++;
    case Qt::Key_Up:    x = -1; z = -1; break; //  x--; z--;
    case Qt::Key_Z :    y =  1; break;
    case Qt::Key_S :    y = -1; break;
    }

    camera.translatePosition(x,y,z);
    camera.translateLookPoint(x,y,z);
}

void ModelisationJeu::updateCase(QString typecase, QString piece, int couleur, int i) {

    m_map[i].typecase   = qstringToOBJ(typecase);
    m_map[i].piece      = qstringToOBJ(piece);
    m_map[i].couleur    = couleur;
}

TypeOBJ ModelisationJeu::qstringToOBJ(const QString &laChaine){
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
