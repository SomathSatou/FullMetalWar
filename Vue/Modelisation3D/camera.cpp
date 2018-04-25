#include "camera.h"

Camera::Camera()
    :m_position(), m_lookPoint(), m_up(0,1,0), m_matrix()
{
    m_matrix.lookAt(m_position, m_lookPoint, m_up);
    m_positionsMax[0] = QVector3D(4568765,0,0);
}

Camera::Camera(const QVector3D &position, const QVector3D &lookPoint, const QVector3D &up)
    :m_position(position), m_lookPoint(lookPoint), m_up(up)
{
    m_matrix.lookAt(m_position, m_lookPoint, m_up);
    m_positionsMax[0] = QVector3D(4568765,0,0);
}

void Camera::translatePosition(double x, double y, double z){
    if(m_positionsMax[0].x() == 4568765){
        m_position.setX(m_position.x() + x);
        m_position.setY(m_position.y() + y);
        m_position.setZ(m_position.z() + z);

        m_matrix.setToIdentity();
        m_matrix.lookAt(m_position, m_lookPoint, m_up);
    } else {
        QVector3D tmp = m_position;
        if( ((tmp.x()+x) > m_positionsMax[0].x() && (tmp.z()+z) > m_positionsMax[0].z())
        &&  ((tmp.x()+x) < m_positionsMax[1].x() && (tmp.z()+z) > m_positionsMax[1].z())
        &&  ((tmp.x()+x) < m_positionsMax[2].x() && (tmp.z()+z) < m_positionsMax[2].z())
        &&  ((tmp.x()+x) > m_positionsMax[3].x() && (tmp.z()+z) < m_positionsMax[3].z()) ){

            m_position.setX(m_position.x() + x);
            m_position.setY(m_position.y() + y);
            m_position.setZ(m_position.z() + z);

            m_matrix.setToIdentity();
            m_matrix.lookAt(m_position, m_lookPoint, m_up);
        }
    }
}

void Camera::translateLookPoint(double x, double y, double z){
    if(m_positionsMax[0].x() == 4568765){
        m_lookPoint.setX(m_lookPoint.x() + x);
        m_lookPoint.setY(m_lookPoint.y() + y);
        m_lookPoint.setZ(m_lookPoint.z() + z);

        m_matrix.setToIdentity();
        m_matrix.lookAt(m_position, m_lookPoint, m_up);
    } else {
        QVector3D tmp = m_lookPoint;

        if( ((tmp.x()+x) > m_positionsMax[0].x() && (tmp.z()+z) > m_positionsMax[0].z())
        &&  ((tmp.x()+x) < m_positionsMax[1].x() && (tmp.z()+z) > m_positionsMax[1].z())
        &&  ((tmp.x()+x) < m_positionsMax[2].x() && (tmp.z()+z) < m_positionsMax[2].z())
        &&  ((tmp.x()+x) > m_positionsMax[3].x() && (tmp.z()+z) < m_positionsMax[3].z()) ){

            m_lookPoint.setX(m_lookPoint.x() + x);
            m_lookPoint.setY(m_lookPoint.y() + y);
            m_lookPoint.setZ(m_lookPoint.z() + z);

            m_matrix.setToIdentity();
            m_matrix.lookAt(m_position, m_lookPoint, m_up);
        }
    }
}

const QVector3D Camera::getDir() const{
    return QVector3D(fabs(m_position.x() - m_lookPoint.x()), fabs(m_position.y() - m_lookPoint.y()), fabs(m_position.z() - m_lookPoint.z()));
}

const QVector3D& Camera::getPosition() const { return m_position; }
const QVector3D& Camera::getLookPoint() const { return m_lookPoint; }
const QVector3D& Camera::getUp() const { return m_up; }
const QMatrix4x4& Camera::getMatrix() const { return m_matrix; }
const float * Camera::constData() const { return m_matrix.constData(); }
void Camera::setPosition(const QVector3D& position){ m_position = position; }
void Camera::setLookPoint(const QVector3D& lookPoint){ m_lookPoint = lookPoint; }
void Camera::setUp(const QVector3D& up){ m_up = up; }
void Camera::setPositionMax(const QVector3D& bottomLeft, const QVector3D& topLeft, const QVector3D& topRight, const QVector3D& bottomRight){
    m_positionsMax[0] = bottomLeft;
    m_positionsMax[1] = topLeft;
    m_positionsMax[2] = topRight;
    m_positionsMax[3] = bottomRight;
}
void Camera::mettreAJourLaMatrice(){
    m_matrix.setToIdentity();
    m_matrix.lookAt(m_position, m_lookPoint, m_up);
}
