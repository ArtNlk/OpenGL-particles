#ifndef GEOMERTYOBJECT_H
#define GEOMERTYOBJECT_H

#include "renderableobject.h"

class GeomertyObject : public RenderableObject
{
    Q_OBJECT
public:
    explicit GeomertyObject(QObject *parent = nullptr);

    int getVertexCount();

public slots:
    void addVert(QVector3D vert, QVector3D norm);
    void move(QVector3D movement);
    //void rotate(float angle,QVector3D axis);
    //void transform(QMatrix4x4& transformMatrix);
    void draw() override;

signals:
    void vertCountChanged(int vertCount);

protected:
    void glUpdate() override;

    QVector<GLfloat> verts;
};

#endif // GEOMERTYOBJECT_H
