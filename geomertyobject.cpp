#include "geomertyobject.h"

#include <QOpenGLFunctions>
#include <QDebug>
#include <QtMath>
#include <QMatrix4x4>

GeomertyObject::GeomertyObject(QObject *parent) : RenderableObject(parent)
{

}

int GeomertyObject::getVertexCount()
{
    return verts.length()/6;
}

void GeomertyObject::addVert(QVector3D vert, QVector3D norm)
{
    verts.append(vert.x());
    verts.append(vert.y());
    verts.append(vert.z());

    verts.append(norm.x());
    verts.append(norm.y());
    verts.append(norm.z());
    needsUpdate = true;
    emit vertCountChanged(getVertexCount());
}

void GeomertyObject::move(QVector3D movement)
{
    for(int i = 0; i < getVertexCount(); i++)
    {
        verts[i*6 + 0] = movement.x();
        verts[i*6 + 1] = movement.y();
        verts[i*6 + 2] = movement.z();
    }
}

void GeomertyObject::draw()
{
    glUpdate();
    QOpenGLVertexArrayObject::Binder vaoBinder(&VAO);
    glDrawArrays(GL_TRIANGLES,0,this->getVertexCount());
}

void GeomertyObject::glUpdate()
{
    if(!needsUpdate)
    {
        return;
    }
    if(VAO.isCreated())
    {
        VAO.destroy();
    }

    VAO.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&VAO);

    if(VBO.isCreated())
    {
        VBO.destroy();
    }
    VBO.create();
    VBO.bind();
    VBO.allocate(verts.constData(),verts.length()*sizeof(GLfloat));
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),nullptr);

    VBO.release();
}
