#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

int main(){
    std::ifstream f("stocha.txt",std::ios::in);
    if(!f.is_open())
        {std::cout<<"erreur de lecture fichier"<<std::endl;
         exit(1);}
    string line;
    string l1;
    string l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15, l16, l17, l18, l19, l20,l21 ,l22, l23;
    
    for(int i = 0;i<37;i++)
    	{
    	f >> line;
    	l1 += line[0];
    	l2 += line[1];
    	l3 += line[2];
    	l4 += line[3];
    	l5 += line[4];
    	l6 += line[5];
    	l7 += line[6];
    	l8 += line[7];
    	l9 += line[8];
    	l10 += line[9];
    	l11 += line[10];
    	l12 += line[11];
    	l13 += line[12];
    	l14 += line[13];
    	l15 += line[14];
    	l16 += line[15];
    	l17 += line[16];
    	l18 += line[17];
    	l19 += line[18];
    	l20 += line[19];
    	l21 += line[20];
    	l22 += line[21];
    	l23 += line[22];
    	}
    	
     std::ofstream fo("stocha_.txt",std::ofstream::out);
     fo << l1 <<"\n"<<l2<<"\n"<<l3<<"\n"<<l4<<"\n"<<l5<<"\n"<< l6<<"\n"<<l7<<"\n"<< l8<<"\n"<< l9<<"\n"<< l10
        <<"\n"<< l11<<"\n"<< l12<<"\n"<< l13<<"\n"<< l14<<"\n"<< l15<<"\n"<< l16<<"\n"<< l17<<"\n"<< l18<<"\n"<< l19<<"\n"<<l20
        <<"\n"<<l21<<"\n"<<l22<<"\n"<<l23;
 
}
