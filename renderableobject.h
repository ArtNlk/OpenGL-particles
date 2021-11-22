#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include <QObject>
#include <qopengl.h>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class RenderableObject : public QObject
{
    Q_OBJECT
public:
    RenderableObject(QObject *parent = nullptr);
    virtual void draw() = 0;
    virtual void draw(QOpenGLShaderProgram* shaderProgram) = 0;

signals:

protected:
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    bool needsUpdate;
    virtual void glUpdate() = 0;
};

#endif // RENDERABLEOBJECT_H
