#include <iostream>
#include "Joueur.h"
#include "piece.h"

int main(int argc, char **argv) {
    
  
    Joueur joueurUn("Nhitro", ROUGE);
    joueurUn.setNombrePADebut(10);
    joueurUn.setNombrePAMax(20);
    
    std::vector<Piece> mesPieces;
    for(int i = 0; i < 20; i++){
      Piece p(0,0,TERRESTRE,true,5,true,3);
      mesPieces.push_back(p);
    }
    
    joueurUn.setPieces(mesPieces);
    
    std::cout << joueurUn.toStringPieces() << std::endl;
    
    
    return 0;
}
