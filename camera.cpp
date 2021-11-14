#include "camera.h"

#include <QTransform>
#include <cmath>

float Camera::fov = 90.f;
float Camera::aspectRatio = 16.f/9.f;
float Camera::nearPlane = 0.001;
float Camera::farPlane = 10000.f;

Camera::Camera(QObject *parent) : QObject(parent),
    speed(0.1),
    hRot(0.0),
    vRot(0.0),
    pos(0,0,0)
{

}

Camera::~Camera()
{

}

QMatrix4x4 Camera::getMatrix()
{
    QMatrix4x4 mat;
    mat.setToIdentity();
    mat.perspective(fov,aspectRatio,nearPlane,farPlane);
    mat.rotate(vRot,1,0,0);
    mat.rotate(hRot,0,1,0);
    mat.translate(-pos);
    return mat;
}

float Camera::getSpeed()
{
    return speed;
}

QVector3D Camera::getPosition()
{
    return pos;
}

void Camera::rotate(float dh, float dv)
{
    hRot += fmod(dh,360.f);
    vRot += fmod(dv,360.f);
}

void Camera::move(float dh, float df, float dv)
{
    pos += QVector3D(dh,dv,df);
}

void Camera::move(QVector3D v)
{
    pos += v;
}

void Camera::stepForward()
{
    QMatrix4x4 t;
    t.setToIdentity();
    t.rotate(-hRot,0,1,0);
    t.rotate(-vRot,1,0,0);
    qDebug() << t * QVector3D(0,0,-speed) << " " << vRot << " " << hRot;
    pos += t*QVector3D(0,0,-speed);

}

void Camera::stepBackward()
{
    QMatrix4x4 t;
    t.setToIdentity();
    t.rotate(-hRot,0,1,0);
    t.rotate(-vRot,1,0,0);
    qDebug() << t * QVector3D(0,0,speed);
    pos += t*QVector3D(0,0,speed);
}

void Camera::strafeLeft()
{
    QMatrix4x4 t;
    t.setToIdentity();
    t.rotate(-hRot,0,1,0);
    qDebug() << t * QVector3D(-speed,0,0);
    pos += t*QVector3D(-speed,0,0);
}

void Camera::strafeRight()
{
    QMatrix4x4 t;
    t.setToIdentity();
    t.rotate(-hRot,0,1,0);
    t.rotate(-vRot,1,0,0);
    qDebug() << t * QVector3D(speed,0,0);
    pos += t*QVector3D(speed,0,0);
}

void Camera::moveUp()
{
    pos.setY(pos.y() + speed);
}

void Camera::moveDown()
{
    pos.setY(pos.y() - speed);
}

void Camera::setSpeed(float _speed)
{
    speed = _speed;
}
