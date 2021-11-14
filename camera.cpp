#include "camera.h"

float Camera::fov = 60.f;
float Camera::aspectRatio = 16.f/9.f;
float Camera::nearPlane = 0.01;
float Camera::farPlane = 1000.f;

Camera::Camera(QObject *parent) : QObject(parent)
{
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(fov,aspectRatio,nearPlane,farPlane);
    speed = 10;
}

QMatrix4x4 Camera::getMatrix()
{
    return projectionMatrix;
}

float Camera::getSpeed()
{
    return speed;
}

void Camera::rotate(float dh, float dv)
{
    projectionMatrix.rotate(dh,QVector3D(0,1,0));
    projectionMatrix.rotate(dh,QVector3D(1,0,0));
}

void Camera::rotate(QQuaternion rot)
{
    projectionMatrix.rotate(rot);
}

void Camera::move(float dh, float df, float dv)
{
    projectionMatrix.translate(dh,dv,df);
}

void Camera::move(QVector3D v)
{
    projectionMatrix.translate(v);
}

void Camera::stepForward()
{
    projectionMatrix.translate(0,0,-speed);
}

void Camera::stepBackward()
{
    projectionMatrix.translate(0,0,speed);
}

void Camera::strafeLeft()
{
    projectionMatrix.translate(-speed,0,0);
}

void Camera::strafeRight()
{
    projectionMatrix.translate(speed,0,0);
}

void Camera::moveUp()
{
    projectionMatrix.translate(0,speed,0);
}

void Camera::moveDown()
{
    projectionMatrix.translate(0,-speed,0);
}

void Camera::setSpeed(float _speed)
{
    speed = _speed;
}
