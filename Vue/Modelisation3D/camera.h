#ifndef CAMERA_H
#define CAMERA_H
#include <QMatrix4x4>
#include <QVector3D>
#include <math.h>
#include <iostream>

class Camera
{
public:
    Camera();
    Camera(const QVector3D& position, const QVector3D& lookPoint, const QVector3D& up);
    const QVector3D& getPosition() const;
    const QVector3D& getLookPoint() const;
    const QVector3D& getUp() const;
    const QMatrix4x4& getMatrix() const;
    const float * constData() const;
    const QVector3D getDir() const;
    void translatePosition(double x, double y, double z);
    void translateLookPoint(double x, double y, double z);
    void setPosition(const QVector3D& position);
    void setLookPoint(const QVector3D& lookPoint);
    void setUp(const QVector3D& up);
    void setPositionMax(const QVector3D& bottomLeft, const QVector3D& topLeft, const QVector3D& topRight, const QVector3D& bottomRight);

    void mettreAJourLaMatrice();


private:
    QVector3D m_position;
    QVector3D m_lookPoint;
    QVector3D m_up;
    QMatrix4x4 m_matrix; 
    QVector3D m_positionsMax[4];

};

#endif // CAMERA_H
