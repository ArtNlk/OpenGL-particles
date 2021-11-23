#ifndef geometryobject_H
#define geometryobject_H

#include "renderableobject.h"
#include <QColor>

class GeometryObject : public RenderableObject
{
    Q_OBJECT
public:
    explicit GeometryObject(QObject *parent = nullptr);

    int getVertexCount();

public slots:
    void addVert(QVector3D vert, QVector3D norm);
    void addTri(int first, int second, int third);
    void move(QVector3D movement);
    void rotate(QVector3D rotation);
    void setColor(QColor color);
    QColor getColor();
    //void rotate(float angle,QVector3D axis);
    //void transform(QMatrix4x4& transformMatrix);
    void draw() override;
    void draw(QOpenGLShaderProgram *shaderProgram) override;

signals:
    void vertCountChanged(int vertCount);

protected:
    void glUpdate() override;

    QVector<GLfloat> verts;
    QVector<GLuint> indexes;
    QVector3D position;
    QColor objectColor;
};

#endif // geometryobject_H
