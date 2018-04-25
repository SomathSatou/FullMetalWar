#ifndef FACE_H
#define FACE_H
#include <string>

class Face
{
public:
    int indexVerUn; int indexVerDe; int indexVerTr;
    int indexNorUn; int indexNorDe; int indexNorTr;
    int indexTexUn; int indexTexDe; int indexTexTr;
    std::string indexMaterial;
};

#endif // FACE_H
