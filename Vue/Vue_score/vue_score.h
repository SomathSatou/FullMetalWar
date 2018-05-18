#ifndef VUE_SCORE_H
#define VUE_SCORE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <sstream>
#include <QRect>
#include <QDesktopWidget>
#include <QApplication>
#include <QPushButton>

class Vue_Score : public QWidget
{
    Q_OBJECT
public:
    explicit Vue_Score(const QString& pseudo, int score, QWidget *parent = 0);
    QPushButton* getRetour() const;

private:
    QPushButton* _retour;

signals:

public slots:
};

#endif // VUE_SCORE_H
