#ifndef PLANE_H
#define PLANE_H

#include "geometryobject.h"

class Plane : public GeometryObject
{
    Q_OBJECT
public:
    explicit Plane(float size = 10, QObject *parent = nullptr);
};

#endif // PLANE_H
