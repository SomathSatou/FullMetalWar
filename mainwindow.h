#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <Vue/vue.h>
#include <Controleur/controleur_jeu.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Vue_Formulaire* _formulaire;
    Vue_Sandbox* _sand;

signals:
    void sendKeyPressed(int key);

public slots:
    void setMenuPrincipal();
    void setFormulaire();
    void setSand();
    void setA();
    void setS();
    void setJeu();
    void setJeu_();
    void setScore(const QString& pseudo, int score);
};

#endif // MAINWINDOW_H
