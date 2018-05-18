#ifndef DEFINECLASS_H
#define DEFINECLASS_H

#include <vector>

#define UNUSED(expr) do { (void)(expr); } while (0)

class Coordonnee{
public:
    int x;
    int y;
    Coordonnee(const int & x , const int & y);
    Coordonnee();
    Coordonnee(const Coordonnee & c);
    Coordonnee & operator=(Coordonnee b);
};

bool operator ==(const Coordonnee & a, const Coordonnee & b);

enum class Couleur      { ROUGE, BLEU, VERT, JAUNE, NEUTRE, BLANC, NOIR, ORANGE, MAUVE, GRIS, CYAN};

enum class TypeCarte    { RANDOM, PLAINES, MERS, STOCHASTIQUE};

enum class typeAction   { DEPLACER, ATTAQUER};

enum class typeCase     { PLAINE, MONTAGNE, MER, MARAIS, RECIF, VIDE };

enum class typePiece    { CHAR , GROS_TAS , VEDETTE , MINERAI , BARGE , CRABE , PONDEUSE , BASE };

class coup{
public:
    coup(Coordonnee src, Coordonnee dst, typeAction action);

    coup(const coup & c);
    coup & operator=(coup b);

    Coordonnee src;
    Coordonnee dst;
    typeAction action;
};


bool operator ==(const coup & a ,const coup & b);

using coups = std::vector<coup>;

struct coutDeplacement{
    int cout;
    int manhattan;
};

struct triplet{
    Coordonnee src;
    coutDeplacement cout;
    Coordonnee dst;
};

bool operator<(triplet const & a , triplet const & b);

bool operator==(const triplet &a, const triplet &b);

class Action{
public:
    Action();
    Action(typeAction type,int src,int dest);
    typeAction getFaire() const;
    void setFaire(const typeAction &value);

    int getSrc() const;
    void setSrc(int value);

    int getDest() const;
    void setDest(int value);


private:
    typeAction faire;
    int src;
    int dest;
};

using actionL = std::vector<Action>;

bool operator ==(const Action &B,const Action &A);
#endif // DEFINECLASS_H
