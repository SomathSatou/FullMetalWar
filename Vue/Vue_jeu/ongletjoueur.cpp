#include "ongletjoueur.h"

OngletJoueur::OngletJoueur(QString pseudo,Couleur couleur, int pa, int pa_max,QWidget *parent) :
    QWidget(parent)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int height = rec.height();
    int width = rec.width();

    setFixedHeight(height/18);

    _layout = new QVBoxLayout(this);
    _layout->setMargin(0);

    _label_pseudo = new QLabel(this);
    _label_PA = new QLabel(this);

    _label_pseudo->setContentsMargins(width/160,0,0,0);
    _label_PA->setContentsMargins(width/160,0,0,0);

    _layout->addWidget(_label_pseudo);
    _layout->addWidget(_label_PA);

    setPseudo(pseudo);
    setPA(pa,pa_max);
    setCouleur(couleur);
}

void OngletJoueur::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void OngletJoueur::setPseudo(QString pseudo) {
    _label_pseudo->setText(pseudo);
}

void OngletJoueur::setPA(int pa, int pa_max) {
    std::ostringstream oss;
    oss << "PA : " << pa << "/" << pa_max;

    std::string tmp = oss.str();

    QString text = tmp.c_str();

    _label_PA->setText(text);
}

void OngletJoueur::setCouleur(Couleur couleur) {

    switch(couleur){

        case Couleur::ROUGE :
            setStyleSheet("background-color : red");
            break;
        case Couleur::BLEU :
            setStyleSheet("background-color : blue");
            break;
        case Couleur::VERT:
            setStyleSheet("background-color : green");
            break;
        case Couleur::JAUNE:
            setStyleSheet("background-color : yellow");
            break;
        default :
            setStyleSheet("background-color : white");

    } // END SWITCH

} // END

