#include "loadobj.h"

LoadOBJ::LoadOBJ(): maLongueurXMax(0), maLongueurYMax(0), maLongueurZMax(0), mesMaterials(0), mesVecteurs(0), mesNormales(0), mesCouleurs(0), mesDonneesConcatenees(0){}

void LoadOBJ::clear(){
    mesVecteurs.clear();
    mesNormales.clear();
    mesCouleurs.clear();
    mesMaterials.clear();
    mesDonneesConcatenees.clear();
}

const Material LoadOBJ::getMaterialByName(const std::string& name) const {
    std::vector<Material>::const_iterator i;
    for(i = mesMaterials.begin(); i != mesMaterials.end(); i++)
        if((*i).getIdentifiant() == name)
            return (*i);
    return Material();
}

unsigned int LoadOBJ::getIndiceMatByName(const std::string &name) const {
    unsigned int indice = 0;
    std::vector<Material>::const_iterator i;
    for(i = mesMaterials.begin(); i != mesMaterials.end(); i++){
        if((*i).getIdentifiant() == name)
            return indice;
        indice++;
    }
    return 0;
}

std::vector<Material>& LoadOBJ::getMaterial()    { return mesMaterials; }
std::vector<GLfloat>&  LoadOBJ::getMesVecteurs() { return mesVecteurs; }
std::vector<GLfloat>&  LoadOBJ::getMesNormales() { return mesNormales; }
std::vector<GLfloat>&  LoadOBJ::getMesCouleurs() { return mesCouleurs; }
std::vector<GLfloat>&  LoadOBJ::getMesDonnees()  { return mesDonneesConcatenees; }
double LoadOBJ::getX() const { return maLongueurXMax; }
double LoadOBJ::getY() const { return maLongueurYMax; }
double LoadOBJ::getZ() const { return maLongueurZMax; }


std::string LoadOBJ::toString() const{
    std::ostringstream oss;
    oss << "Nombres de vertices :" << mesVecteurs.size() << std::endl
        << "Nombre de normales :" <<  mesNormales.size() << std::endl;
    return oss.str();
}

/* Méthode récursive */
bool LoadOBJ::recupFace(QString line, int indice, int indiceFace, unsigned int indiceMat){
    QString tampon;       // Tampon pour le stockage de la lecture de l'indice depuis le fichier
    int     indiceVector; // Indice pour les vectors
    int     indiceTextur; // Indice pour les textures coords
    int     indiceNormal; // Indice pour les normales
    UNUSED(indiceTextur);
    // Si la taille de la chaîne - 1  == indice on arrête
    if( (line.size() -1) <= indice ) return true;
    // On récupère l'indice du vertice
    while(line.at(indice) != '/'){
        tampon.append(line.at(indice));
        indice++;
    }
    indiceVector = tampon.toInt() -1; tampon.clear();  // On transforme l'indice string en int et on vide la chaîne
    indice++; // Allons sur le prochain caractère car nous sommes sur un slash
    // On récupère l'indice des textures coords
    while(line.at(indice) != '/'){
        tampon.append(line.at(indice));
        indice++;
    }
    indiceTextur = tampon.toInt() -1; tampon.clear();  // On transforme l'indice string en int et on vide la chaîne
    indice++; // Allons sur le prochain caractère car nous sommes sur un slash
    // On récupère l'indice de la normale
    while(line.at(indice) != ' '){
        tampon.append(line.at(indice));
        indice++;
        if(indice == (line.size())) break; // Gestion de l'exception de fin de ligne (car nous savons que cela se termine par une normale
    }
    indiceNormal = tampon.toInt() -1; tampon.clear(); // On transforme l'indice en int et on vide la chaîne
    indice++; // On va jusqu'au prochain indice et si on dépasse, le dépassement sera géré à la n+1 ème itération de la fonction

    /*
     * Cette méthode ne fonctionne qu'avec des triangles et n'a pas été pensé pour faire autrement
     * La raison du pourquoi que des triangles, c'est dans l'optique d'optimiser la modélisation avec des VBO
     */

    mesDonneesConcatenees.push_back(mesVecteurs.at(indiceVector *3));
    mesDonneesConcatenees.push_back(mesVecteurs.at(indiceVector *3 + 1));
    mesDonneesConcatenees.push_back(mesVecteurs.at(indiceVector *3 + 2));
    mesDonneesConcatenees.push_back(mesNormales.at(indiceNormal *3));
    mesDonneesConcatenees.push_back(mesNormales.at(indiceNormal *3 + 1));
    mesDonneesConcatenees.push_back(mesNormales.at(indiceNormal *3 + 2));
    mesDonneesConcatenees.push_back(mesCouleurs.at(indiceMat *3));
    mesDonneesConcatenees.push_back(mesCouleurs.at(indiceMat *3 + 1));
    mesDonneesConcatenees.push_back(mesCouleurs.at(indiceMat *3 + 2));
    return recupFace(line, indice, ++indiceFace, indiceMat);
}

// A COMPLETER
bool LoadOBJ::chargerNouvelObjet(const TypeOBJ objet, int numero){
    clear();
    unsigned int     indiceMaterialCurrent = 0; // 0 étant la valeur par défaut si nous n'avons pas de MTL, une couleur blanche sera ajoutée
    QString cheminBase(":/Files/Ressources/modele3D/");
    QString chemin;
    QString cheminMLT;

    // DETERMINATION DU FICHIER A CHARGER
    switch(objet){
        case PL:
            if(numero == 0) chemin = cheminBase + "plaine1.obj";
            if(numero == 1) chemin = cheminBase + "plaine2.obj";
            if(numero == 2) chemin = cheminBase + "plaine3.obj";
        break;
        case ME:
            if(numero == 0) chemin = cheminBase + "water.obj";
            if(numero == 1) chemin = cheminBase + "water1.obj";
            if(numero == 2) chemin = cheminBase + "water1.obj";
            if(numero == 3) chemin = cheminBase + "water3.obj";
            if(numero == 4) chemin = cheminBase + "water4.obj";
        break;
        case MA:
            if(numero == 0) chemin = cheminBase + "swamp1.obj";
            if(numero == 1) chemin = cheminBase + "swamp2.obj";
        break;
        case MO:
            if(numero == 0) chemin = cheminBase + "mountain1.obj";
            if(numero == 1) chemin = cheminBase + "mountain2.obj";
            if(numero == 2) chemin = cheminBase + "mountain3.obj";
        break;
        case RE:
            if(numero == 0) chemin = cheminBase + "recif1.obj";
            if(numero == 1) chemin = cheminBase + "recif2.obj";
        break;
        case BA:    chemin = cheminBase + "barge.obj";          break;
        case BU:    chemin = cheminBase + "mountain1.obj";      break;
        case CH:    chemin = cheminBase + "char.obj";           break;
        case CR:    chemin = cheminBase + "crabe.obj";          break;
        case GR:    chemin = cheminBase + "grostas.obj";        break;
        case MI:    chemin = cheminBase + "minerais.obj";       break;
        case POD:   chemin = cheminBase + "base.obj";           break;
        case POND:  chemin = cheminBase + "pondeuse.obj";       break;
        case PONT:  chemin = cheminBase + "ponton.obj";         break;
        case VE:    chemin = cheminBase + "vedette.obj";        break;
        default:    chemin = "Type OBJET non reconnu ERROR";    break;
    }
    // LECTURE DE FICHIER
//    std::cout << chemin.toStdString() << std::endl;
    QFile file(chemin);
    if(!file.open(QIODevice::ReadOnly)){
        //std::cout << "Impossible d'ouvrir le fichier *****************************************************************************************************************************" << std::endl;
        return false;
    }// else
       // std::cout << "J'ai réussi à ouvrir le fichier" << std::endl;

    // RECUPERATION DU CONTENU DU FICHIER
    QTextStream in(&file);
    while (!in.atEnd()){
        QString line = in.readLine();
        // Si la ligne commence par un m c'est que la ligne correspond au nom du FICHIER MLT
        // Nous devons alors le récupérer pour créer les materials associés
        if(line.at(0) == 'm'){
            int index = line.indexOf(' ',1) + 1; // Nous récupérons l'index du premier espace car le début de la ligne ne nous intéresse pas
            while(line.at(index) != '.'){  // Tant que nous ne sommes pas arrivés au . de l'extension, nous récupérons la chaîne de carac
                cheminMLT.append(line.at(index));
                index++;
            }
            // Une fois ceci chose faite, nous pouvons rajouter l'extension (Cela impose l'absence de . dans la nomenclature du fichier)
            cheminMLT.append(".mtl");
            cheminMLT = cheminBase + cheminMLT;
            // On contrôle le chemin obtenu
//            std::cout << "Chemin du MLT : " << cheminMLT.toStdString() << std::endl;
            // LECTURE DU FICHIER MLT POUR RÉCUPÉRER LES MATERIALS
//            std::cout << cheminMLT.toStdString() << std::endl;
            chargerMLT(cheminMLT);
        }
        // Si la ligne commence par un v, nous nous trouvons soit face à un sommet, soit à une normale, soit à des TexturesCoords
        if(line.at(0) == 'v'){
            // Si c'est une normale
            if(line.at(1) == 'n'){
                QString tampon;
                int firstSpace = line.indexOf(' ', 0) +1;
                double x,y,z;
                while(line.at(firstSpace) != ' '){
                    tampon.append(line.at(firstSpace));
                    firstSpace++;
                }
                x = tampon.toDouble();
                tampon.clear();
                firstSpace++;
                while(line.at(firstSpace) != ' '){
                    tampon.append(line.at(firstSpace));
                    firstSpace++;
                }
                y = tampon.toDouble();
                tampon.clear();
                firstSpace++;
                while(line.at(firstSpace) != ' ' && firstSpace < (line.size()-1)){
                    tampon.append(line.at(firstSpace));
                    firstSpace++;
                }
                z = tampon.toDouble();
                mesNormales.push_back(x);
                mesNormales.push_back(y);
                mesNormales.push_back(z);
            }
            // Si c'est des texturesCoords
            else if(line.at(1) == 't'){
                QString tampon;
                int firstSpace = line.indexOf(' ', 0) +1;
                double x,y;
                UNUSED(x);
                UNUSED(y);
                while(line.at(firstSpace) != ' '){
                    tampon.append(line.at(firstSpace));
                    firstSpace++;
                }
                x = tampon.toDouble();
                tampon.clear();
                firstSpace++;
                while(line.at(firstSpace) != ' '){
                    tampon.append(line.at(firstSpace));
                    firstSpace++;
                    if(firstSpace == (line.size())) break;
                }
                y = tampon.toDouble();
                tampon.clear();
                // A VOIR
            }
            // Si c'est une vertice
            else if(line.at(1) == ' '){
                QString tampon;
                int firstSpace = line.indexOf(' ', 0) +1;
                double x,y,z;
                while(line.at(firstSpace) != ' '){
                    tampon.append(line.at(firstSpace));
                    firstSpace++;
                }
                x = tampon.toDouble();
                tampon.clear();
                firstSpace++;
                while(line.at(firstSpace) != ' '){
                    tampon.append(line.at(firstSpace));
                    firstSpace++;
                }
                y = tampon.toDouble();
                tampon.clear();
                firstSpace++;
                while(line.at(firstSpace) != ' '){
                    tampon.append(line.at(firstSpace));
                    firstSpace++;
                    if(firstSpace == (line.size())) break;
                }
                z = tampon.toDouble();
                mesVecteurs.push_back(x);
                mesVecteurs.push_back(y);
                mesVecteurs.push_back(z);
                if(x > maLongueurXMax) maLongueurXMax = x;
                if(y > maLongueurYMax) maLongueurYMax = y;
                if(z > maLongueurZMax) maLongueurZMax = z;
            }
        }
        // Si c'est un material
        else if(line.at(0) == 'u'){
            QString tampon;
            int firstSpace = line.indexOf(' ', 0) +1;
            while(1){
                tampon.append(line.at(firstSpace));
                firstSpace++;
                if(firstSpace == line.size()) break;
            }
            indiceMaterialCurrent = getIndiceMatByName(tampon.toStdString());
        }
        // Si c'est une face
        else if(line.at(0) == 'f'){
            int firstSpace = line.indexOf(' ', 0) +1;
            recupFace(line, firstSpace, 0, indiceMaterialCurrent);
        }
    }
    file.close();
//    std::cout << "Taille de la liste : " << mesDonneesConcatenees.size() << std::endl;
//    std::cout << "Normalement ça doit être proche de 450000" << std::endl;

    return true;
}

void LoadOBJ::chargerMLT(QString &path){
    std::string      nomMaterial;
    QFile file2(path);
    if(!file2.open(QIODevice::ReadOnly)){
//        std::cout << "Impossible d'ouvrir le fichier" << std::endl;
        // Nous n'avons pas trouvé de material
        mesCouleurs.push_back(1);
        mesCouleurs.push_back(1);
        mesCouleurs.push_back(1);
    } else {
//        std::cout << "J'ai réussi à ouvrir le fichier" << std::endl;
        // RECUPERATION DU CONTENU DU FICHIER
        QTextStream in2(&file2);
        double ar,ag,ab,dr,dg,db,sr,sg,sb,s;
        bool   creationMat = 0;
        while (!in2.atEnd()){
            QString line = in2.readLine();
            // Si c'est une valeur de lumière
            if(line.size() > 0){
                if(line.at(0) == 'K'){
                    // Si c'est ambient
                    if(line.at(1) == 'a'){
                        QString tampon;
                        int firstSpace = line.indexOf(' ', 0) +1;
                        while(line.at(firstSpace) != ' '){
                            tampon.append(line.at(firstSpace));
                            firstSpace++;
                        }
                        ar = tampon.toDouble();
                        tampon.clear();
                        firstSpace++;
                        while(line.at(firstSpace) != ' '){
                            tampon.append(line.at(firstSpace));
                            firstSpace++;
                        }
                        ag = tampon.toDouble();
                        tampon.clear();
                        firstSpace++;
                        while(line.at(firstSpace) != ' '){
                            tampon.append(line.at(firstSpace));
                            firstSpace++;
                            if(firstSpace == (line.size())) break;
                        }
                        ab = tampon.toDouble();
                    }
                    // Si c'est diffuse
                    else if(line.at(1) == 'd'){
                        QString tampon;
                        int firstSpace = line.indexOf(' ', 0) +1;
                        while(line.at(firstSpace) != ' '){
                            tampon.append(line.at(firstSpace));
                            firstSpace++;
                        }
                        dr = tampon.toDouble();
                        tampon.clear();
                        firstSpace++;
                        while(line.at(firstSpace) != ' '){
                            tampon.append(line.at(firstSpace));
                            firstSpace++;
                        }
                        dg = tampon.toDouble();
                        tampon.clear();
                        firstSpace++;
                        while(line.at(firstSpace) != ' '){
                            tampon.append(line.at(firstSpace));
                            firstSpace++;
                            if(firstSpace == (line.size())) break;
                        }
                        db = tampon.toDouble();
                    }
                    // Si c'est specular
                    else if(line.at(1) == 's'){
                        QString tampon;
                        int firstSpace = line.indexOf(' ', 0) +1;
                        while(line.at(firstSpace) != ' '){
                            tampon.append(line.at(firstSpace));
                            firstSpace++;
                        }
                        sr = tampon.toDouble();
                        tampon.clear();
                        firstSpace++;
                        while(line.at(firstSpace) != ' '){
                            tampon.append(line.at(firstSpace));
                            firstSpace++;
                        }
                        sg = tampon.toDouble();
                        tampon.clear();
                        firstSpace++;
                        while(line.at(firstSpace) != ' '){
                            tampon.append(line.at(firstSpace));
                            firstSpace++;
                            if(firstSpace == (line.size())) break;
                        }
                        sb = tampon.toDouble();
                        creationMat = 1;
                    }
                }
                else if(line.at(0) == 'N' && line.at(1) == 's'){
                    QString tampon;
                    int firstSpace = line.indexOf(' ', 0) +1;
                    while(line.at(firstSpace) != ' '){
                        tampon.append(line.at(firstSpace));
                        firstSpace++;
                        if(firstSpace == (line.size())) break;
                    }
                    s = tampon.toDouble();
                    s /=100.0;
                }
                /*
                else if(line.contains("Material Count")){
                    QString tampon;
                    int lastSpace = line.size() - 1;
                    while(line.at(lastSpace) != ' '){
                        tampon = line.at(lastSpace) + tampon;
                        lastSpace--;
                    }
                    int sizeMaterials = tampon.toInt();
                    out_materials = std::vector<Material>(sizeMaterials);
                }*/
                else if(line.contains("newmtl")){
                    QString tampon;
                    int firstSpace = line.indexOf(' ', 0) +1;
                    while(1){
                        tampon.append(line.at(firstSpace));
                        firstSpace++;
                        if(firstSpace == line.size()) break;
                    }
                    nomMaterial = tampon.toStdString();
                }

                if(creationMat == 1){
                    Material m(nomMaterial,ar,ag,ab,dr,dg,db,sr,sg,sb,s);
                    mesMaterials.push_back(m);
                    mesCouleurs.push_back(dr);
                    mesCouleurs.push_back(dg);
                    mesCouleurs.push_back(db);
                    creationMat = 0;
                }
            }
        }
        file2.close();
    }
}
