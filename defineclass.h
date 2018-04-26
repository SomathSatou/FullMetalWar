#pragma once
#ifndef DEFINECLASS_H
#define DEFINECLASS_H
enum class Couleur { ROUGE, BLEU, VERT, JAUNE, NEUTRE, BLANC, NOIR, ORANGE, MAUVE, GRIS, CYAN};


enum TypeCarte {RANDOM, PLAINES, MERS, STOCHASTIQUE};


enum class typeAction {DEPLACER, ATTAQUER};

struct Action{
    typeAction faire;
    int src;
    int dest;
    };


#endif // DEFINECLASS_H

