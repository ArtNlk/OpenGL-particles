#include "geomertyobject.h"

#include <QOpenGLFunctions>
#include <QDebug>
#include <QtMath>
#include <QMatrix4x4>

GeomertyObject::GeomertyObject(QObject *parent) : RenderableObject(parent)
{
    objectColor = QColor(255,128,128);
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
    emit vertCountChanged(getVertexCount());
}

void GeomertyObject::addTri(int first, int second, int third)
{
    indexes.append(first);
    indexes.append(second);
    indexes.append(third);
    needsUpdate = true;
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

void GeomertyObject::setColor(QColor color)
{
    objectColor = color;
}

QColor GeomertyObject::getColor()
{
    return objectColor;
}

void GeomertyObject::draw()
{
    glUpdate();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    QOpenGLVertexArrayObject::Binder vaoBinder(&VAO);
    //glDrawArrays(GL_TRIANGLES,0,this->getVertexCount());
    glDrawElements(GL_TRIANGLES,indexes.length(),GL_UNSIGNED_INT,indexes.constData());
}

void GeomertyObject::draw(QOpenGLShaderProgram *shaderProgram)
{
    shaderProgram->setUniformValue("objectColor",objectColor);
    draw();
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

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    if(VBO.isCreated())
    {
        VBO.destroy();
    }
    VBO.create();
    VBO.bind();
    VBO.allocate(verts.constData(),verts.length()*sizeof(GLfloat));
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),nullptr);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),reinterpret_cast<void*>(3*sizeof(GLfloat)));

    VBO.release();
}
