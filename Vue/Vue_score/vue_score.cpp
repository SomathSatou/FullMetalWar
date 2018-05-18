#include "vue_score.h"

using namespace std;

Vue_Score::Vue_Score(const QString &pseudo, int score, QWidget *parent) : QWidget(parent)
{
    // On récupère la taille de l'écran de l'utilisateur
    QRect rec = QApplication::desktop()->availableGeometry();
    int height = rec.height();
    int width = rec.width();

    QVBoxLayout* layout = new QVBoxLayout(this);
    ostringstream oss;
    oss << "Le gagnant est " << pseudo.toStdString() << " avec " << score << " points ! Félicitation !";
    QString resultat = oss.str().c_str();
    QLabel* label_resultat = new QLabel(resultat,this);
    QFont font("Arial",height/45);
    label_resultat->setFont(font);

     _retour = new QPushButton("Retour au menu principal",this);
    _retour->setFixedSize(QSize(width/9,height/18));

    layout->addStretch(5);
    layout->addWidget(label_resultat,0,Qt::AlignCenter);
    layout->addStretch(1);
    layout->addWidget(_retour,0,Qt::AlignCenter);
    layout->addStretch(5);

}

QPushButton *Vue_Score::getRetour() const { return _retour; }
