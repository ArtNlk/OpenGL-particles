#include "directionallight.h"

DirectionalLight::DirectionalLight(QVector3D dir, QColor color,QObject *parent) : Light(color)
{
    direction = dir;
}

QVector3D DirectionalLight::getDirection()
{
    return direction;
}

void DirectionalLight::setDirection(QVector3D newDirection)
{
    direction = newDirection;
}
