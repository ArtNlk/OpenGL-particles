#include "plane.h"

Plane::Plane(float size, QObject *parent) : GeometryObject(parent)
{
    addVert(QVector3D(-size/2,0,-size/2),QVector3D(0,1,0));
    addVert(QVector3D(-size/2,0,size/2),QVector3D(0,1,0));
    addVert(QVector3D(size/2,0,size/2),QVector3D(0,1,0));
    addVert(QVector3D(size/2,0,-size/2),QVector3D(0,1,0));

    addTri(0,1,2);
    addTri(2,3,0);
}
