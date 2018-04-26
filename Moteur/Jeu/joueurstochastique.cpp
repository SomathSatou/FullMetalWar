#include "joueurstochastique.h"

std::vector<Action> joueurStochastique::joue(){
    std::vector<Action> actions;
    Action a;
    a.faire=typeAction::DEPLACER;
    a.src=24;
    a.dest=23;
    actions.push_back(a);
    a.src=23;
    a.dest=22;
    actions.push_back(a);
    a.src=22;
    a.dest=21;
    actions.push_back(a);
    a.src=21;
    a.dest=20;
    actions.push_back(a);
    a.src=20;
    a.dest=19;
    actions.push_back(a);
    return actions;
}
