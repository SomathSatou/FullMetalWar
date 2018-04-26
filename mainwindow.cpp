#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow() :
    QMainWindow()
{
    setMenuPrincipal();
}

void MainWindow::setMenuPrincipal() {
    Vue_MenuPrincipal* _menu_principal = new Vue_MenuPrincipal(this);
    connect(_menu_principal->getBoutonJouer(),&QPushButton::clicked,this,&MainWindow::setFormulaire);
    connect(_menu_principal->getBoutonSand(),&QPushButton::clicked,this,&MainWindow::setSand);
    connect(_menu_principal->getBoutonTestA(),&QPushButton::clicked,this,&MainWindow::setA);
    connect(_menu_principal->getBoutonTestS(),&QPushButton::clicked,this,&MainWindow::setS);
    setCentralWidget(_menu_principal);
}

void MainWindow::setFormulaire() {
    _formulaire = new Vue_Formulaire(this);
    connect(_formulaire->getBoutonJouer(),&QPushButton::clicked,this,&MainWindow::setJeu);
    connect(_formulaire->getBoutonRetour(),&QPushButton::clicked,this,&MainWindow::setMenuPrincipal);
    setCentralWidget(_formulaire);
}

void MainWindow::setSand() {
    _sand = new Vue_Sandbox(this);
    connect(_sand->getBoutonJouer(),&QPushButton::clicked,this,&MainWindow::setJeu_);
    connect(_sand->getBoutonRetour(),&QPushButton::clicked,this,&MainWindow::setMenuPrincipal);
    setCentralWidget(_sand);
}

void MainWindow::setA() {
    std::vector<Joueur *> J;
    J.push_back(new Joueur("Titi",Couleur::BLEU));
    J.push_back(new Joueur("Toto",Couleur::VERT));
    std::vector<std::pair<typePiece,int>> P;
    P.push_back(std::pair<typePiece,int>(typePiece::CHAR,1));
    Controleur_Jeu* _controleur_jeu = new Controleur_Jeu(J,5,5,TypeCarte::PLAINES,false,P,this);
    connect(this,&MainWindow::sendKeyPressed,_controleur_jeu->getVueJeu()->getModelisation(),&ModelisationJeu::getKeyPressed);
    connect(_controleur_jeu,&Controleur_Jeu::putScoreScreen,this,&MainWindow::setScore);
    setCentralWidget(_controleur_jeu->getVueJeu());
}

void MainWindow::setS() {
    std::vector<Joueur *> J;
    J.push_back(new Joueur("Titi",Couleur::BLEU));
    J.push_back(new Joueur("Toto",Couleur::ORANGE));
    std::vector<std::pair<typePiece,int>> P;
    P.push_back(std::pair<typePiece,int>(typePiece::CHAR,1));
    Controleur_Jeu* _controleur_jeu = new Controleur_Jeu(J,5,5,TypeCarte::PLAINES,false,P,this);
    connect(this,&MainWindow::sendKeyPressed,_controleur_jeu->getVueJeu()->getModelisation(),&ModelisationJeu::getKeyPressed);
    connect(_controleur_jeu,&Controleur_Jeu::putScoreScreen,this,&MainWindow::setScore);
    setCentralWidget(_controleur_jeu->getVueJeu());
}

void MainWindow::setJeu() {
    Controleur_Formulaire* _controleur_form = _formulaire->getControleur();
    Controleur_Jeu* _controleur_jeu = new Controleur_Jeu(_controleur_form->getListeJoueurs(),_controleur_form->getLongueur(),_controleur_form->getLargeur(),this);
    connect(this,&MainWindow::sendKeyPressed,_controleur_jeu->getVueJeu()->getModelisation(),&ModelisationJeu::getKeyPressed);
    connect(_controleur_jeu,&Controleur_Jeu::putScoreScreen,this,&MainWindow::setScore);
    setCentralWidget(_controleur_jeu->getVueJeu());
}

void MainWindow::setJeu_() {
    Controleur_Sandbox* _controleur_sand = _sand->getControleur();
    Controleur_Jeu* _controleur_jeu = new Controleur_Jeu(_controleur_sand->getListeJoueurs(),_controleur_sand->getLongueur(),_controleur_sand->getLargeur(),_controleur_sand->getType(),_controleur_sand->getMinerais(),_controleur_sand->getListePiece(),this);
    connect(this,&MainWindow::sendKeyPressed,_controleur_jeu->getVueJeu()->getModelisation(),&ModelisationJeu::getKeyPressed);
    connect(_controleur_jeu,&Controleur_Jeu::putScoreScreen,this,&MainWindow::setScore);
    setCentralWidget(_controleur_jeu->getVueJeu());
}

void MainWindow::setScore(const QString& pseudo, int score){

    Vue_Score* _vue_score = new Vue_Score(pseudo,score,this);
    connect(_vue_score->getRetour(),&QPushButton::clicked,this,&MainWindow::setMenuPrincipal);
    setCentralWidget(_vue_score);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    switch(event->key()){
    case Qt::Key_Left:  emit sendKeyPressed(Qt::Key_Left); break; //  z++; x--;
    case Qt::Key_Right: emit sendKeyPressed(Qt::Key_Right); break; //  z--; x++;
    case Qt::Key_Down:  emit sendKeyPressed(Qt::Key_Down); break; //  x++; z++;
    case Qt::Key_Up:    emit sendKeyPressed(Qt::Key_Up); break; //  x--; z--;
    case Qt::Key_Z :    emit sendKeyPressed(Qt::Key_Z); break;
    case Qt::Key_S :    emit sendKeyPressed(Qt::Key_S); break;
    }
}
