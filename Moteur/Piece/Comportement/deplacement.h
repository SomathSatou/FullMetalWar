#pragma once

#include "defineclass.h"


class IDeplacement{
public:
    virtual bool accessible(typeCase tc) = 0;
    virtual ~IDeplacement();

};


class Deplacement_terre : public IDeplacement{

public:
    bool accessible(typeCase tc);
};

class Deplacement_terre_sans_mont : public IDeplacement{

public:
    bool accessible(typeCase tc);
};

class Deplacement_eau : public IDeplacement{

public:
    bool accessible(typeCase tc);
};


class Deplacement_nul : public IDeplacement{

public:
    bool accessible(typeCase tc);
};
