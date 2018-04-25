#include <iostream>
#include "Piece.h"
#include "Joueur.h"
#include "Minerai.h"
#include "ponton.h"
#include "char.h"
#include "grostas.h"
#include "tourelle.h"
#include "barge.h"
#include "vedette.h"
#include "crabe.h"
#include "pode.h"
#include "pondeuse.h"

int main(int argc, char **argv) {
  
    // à revoir l'utilité de l'Astronef
    Joueur neutre("NEUTRE", NEUTRE);

    Char        c(&neutre);
    GrosTas     g(&neutre);
    Minerai     m(0,0,&neutre,1);
    Ponton      p(&neutre);
    Tourelle    t(&neutre);
    Vedette     v(&neutre);
    Barge       b(&neutre);
    Crabe       cb(&neutre);
    Pode        po(&neutre);
    Pondeuse    pon(&neutre);


    std::cout << c.toString() << std::endl;
    std::cout << g.toString() << std::endl;
    std::cout << m.toString() << std::endl;
    std::cout << p.toString() << std::endl;
    std::cout << t.toString() << std::endl;
    std::cout << v.toString() << std::endl;
    std::cout << b.toString() << std::endl;
    std::cout << cb.toString() << std::endl;
    std::cout << po.toString() << std::endl;
    std::cout << pon.toString() << std::endl;
    
    return 0;
}
