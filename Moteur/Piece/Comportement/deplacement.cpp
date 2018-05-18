#include"deplacement.h"

IDeplacement::~IDeplacement(){}

bool Deplacement_terre::accessible(typeCase tc){
    return (tc == typeCase::MONTAGNE) || (tc == typeCase::PLAINE) || (tc == typeCase::MARAIS);
}

bool Deplacement_terre_sans_mont::accessible(typeCase tc){
    return (tc == typeCase::PLAINE) || (tc == typeCase::MARAIS);
}

bool Deplacement_eau::accessible(typeCase tc){
    return (tc == typeCase::MER) || (tc == typeCase::RECIF);
}

bool Deplacement_nul::accessible(typeCase tc){
    UNUSED(tc);
    return false;
}
