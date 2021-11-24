#ifndef TESTBOX_H
#define TESTBOX_H

#include "geometryobject.h"

class TestBox : public GeometryObject
{
    Q_OBJECT
public:
    explicit TestBox(float size = 5,QObject *parent = nullptr);

private:

    enum NormalAxis {XAxis = 0, YAxis, ZAxis};

    void configureVerts(float size);
    void configureTris();

    ///@brief Helper function to convert vertex index and normal axis to global vertex index
    ///@param index Vertex index
    ///@param nAxis Normal axis number: 0-X 1-Y 2-Z
    inline int vToI(int index, NormalAxis nAxis);
};

#endif // TESTBOX_H
