#include "defineclass.h"

Coordonnee::Coordonnee(const int &x, const int &y)
    : x(x), y(y)
{}

Coordonnee::Coordonnee()
    : x(0), y(0)
{}

Coordonnee::Coordonnee(const Coordonnee &c)
    : x(c.x), y(c.y)
{}

Coordonnee &Coordonnee::operator=(Coordonnee b){
    x=b.x;
    y=b.y;
    return *this;
}

bool operator ==(const Coordonnee &a, const Coordonnee &b){
    return a.x==b.x && a.y==b.y;
}

bool operator<(const triplet &a, const triplet &b){
    return b.cout.manhattan < a.cout.manhattan;
}

bool operator==(const triplet &a, const triplet &b){
    return a.dst==b.dst;
}

bool operator ==(const coup &a, const coup &b){
    return a.src==b.src && a.dst == b.dst;
}

coup::coup(Coordonnee src, Coordonnee dst, typeAction action)
    : src(src), dst(dst), action(action)
{}

coup::coup(const coup &c)
    : src(c.src), dst(c.dst),action(c.action)
{}

coup &coup::operator=(coup b){
    src=b.src;
    dst=b.dst;
    action=b.action;
    return *this;
}

bool operator ==(const Action &B, const Action &A){
    if(A.getSrc()==B.getSrc()){
        if(A.getDest()==B.getDest()){
            if(A.getFaire()==B.getFaire()){
                return true;
            }
        }
    }
    return false;
}

Action::Action():faire(typeAction::DEPLACER),src(0),dest(0){}

Action::Action(typeAction type, int src, int dest):faire(type),src(src),dest(dest){}

typeAction Action::getFaire() const{return faire;}

void Action::setFaire(const typeAction &value){faire = value;}

int Action::getSrc() const{return src;}

void Action::setSrc(int value){src = value;}

int Action::getDest() const{return dest;}

void Action::setDest(int value){dest = value;}
