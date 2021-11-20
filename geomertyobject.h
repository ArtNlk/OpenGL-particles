#ifndef GEOMERTYOBJECT_H
#define GEOMERTYOBJECT_H

#include <QObject>
#include "qopengl.h"
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

class GeomertyObject : public QObject
{
    Q_OBJECT
public:
    explicit GeomertyObject(QObject *parent = nullptr);

signals:

protected:
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    bool needsUpdate;
};

#endif // GEOMERTYOBJECT_H
