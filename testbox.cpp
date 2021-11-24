#include "testbox.h"

TestBox::TestBox(float size, QObject *parent)
{
    if(size <= 0)
    {
        qDebug() << "Attempt to create 0-size box";
    }

    configureVerts(size);
    configureTris();
}

void TestBox::configureVerts(float size)
{
    float hfSize = size/2;

    //0
    addVert(QVector3D(hfSize,hfSize,hfSize),QVector3D(1,0,0));//0
    addVert(QVector3D(hfSize,hfSize,hfSize),QVector3D(0,1,0));//1
    addVert(QVector3D(hfSize,hfSize,hfSize),QVector3D(0,0,1));//2

    //1
    addVert(QVector3D(-hfSize,hfSize,hfSize),QVector3D(-1,0,0));//3
    addVert(QVector3D(-hfSize,hfSize,hfSize),QVector3D(0,1,0));//4
    addVert(QVector3D(-hfSize,hfSize,hfSize),QVector3D(0,0,1));//5

    //2
    addVert(QVector3D(-hfSize,hfSize,-hfSize),QVector3D(-1,0,0));//6
    addVert(QVector3D(-hfSize,hfSize,-hfSize),QVector3D(0,1,0));//7
    addVert(QVector3D(-hfSize,hfSize,-hfSize),QVector3D(0,0,-1));//8

    //3
    addVert(QVector3D(hfSize,hfSize,-hfSize),QVector3D(1,0,0));//9
    addVert(QVector3D(hfSize,hfSize,-hfSize),QVector3D(0,1,0));//10
    addVert(QVector3D(hfSize,hfSize,-hfSize),QVector3D(0,0,-1));//11

    //4
    addVert(QVector3D(hfSize,-hfSize,hfSize),QVector3D(1,0,0));//0
    addVert(QVector3D(hfSize,-hfSize,hfSize),QVector3D(0,-1,0));//1
    addVert(QVector3D(hfSize,-hfSize,hfSize),QVector3D(0,0,1));//2

    //5
    addVert(QVector3D(-hfSize,-hfSize,hfSize),QVector3D(-1,0,0));//3
    addVert(QVector3D(-hfSize,-hfSize,hfSize),QVector3D(0,-1,0));//4
    addVert(QVector3D(-hfSize,-hfSize,hfSize),QVector3D(0,0,1));//5

    //6
    addVert(QVector3D(-hfSize,-hfSize,-hfSize),QVector3D(-1,0,0));//6
    addVert(QVector3D(-hfSize,-hfSize,-hfSize),QVector3D(0,-1,0));//7
    addVert(QVector3D(-hfSize,-hfSize,-hfSize),QVector3D(0,0,-1));//8

    //7
    addVert(QVector3D(hfSize,-hfSize,-hfSize),QVector3D(1,0,0));//9
    addVert(QVector3D(hfSize,-hfSize,-hfSize),QVector3D(0,-1,0));//10
    addVert(QVector3D(hfSize,-hfSize,-hfSize),QVector3D(0,0,-1));//11

}

void TestBox::configureTris()
{
    //Top
    addTri(vToI(0,YAxis),vToI(2,YAxis),vToI(1,YAxis));
    addTri(vToI(0,YAxis),vToI(3,YAxis),vToI(2,YAxis));

    //Bottom
    addTri(vToI(6,YAxis),vToI(7,YAxis),vToI(4,YAxis));
    addTri(vToI(6,YAxis),vToI(4,YAxis),vToI(5,YAxis));

    //Left
    addTri(vToI(6,XAxis),vToI(1,XAxis),vToI(2,XAxis));
    addTri(vToI(6,XAxis),vToI(5,XAxis),vToI(1,XAxis));

    //Right
    addTri(vToI(7,XAxis),vToI(3,XAxis),vToI(0,XAxis));
    addTri(vToI(7,XAxis),vToI(0,XAxis),vToI(4,XAxis));

    //Front
    addTri(vToI(6,ZAxis),vToI(2,ZAxis),vToI(3,ZAxis));
    addTri(vToI(6,ZAxis),vToI(3,ZAxis),vToI(7,ZAxis));

    //Back
    addTri(vToI(5,ZAxis),vToI(0,ZAxis),vToI(1,ZAxis));
    addTri(vToI(5,ZAxis),vToI(4,ZAxis),vToI(0,ZAxis));
}

int TestBox::vToI(int index, NormalAxis nAxis)
{
    return index*3+nAxis;
}
