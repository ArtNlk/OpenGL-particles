#include "geometryobject.h"

#include <QOpenGLFunctions>
#include <QDebug>
#include <QtMath>
#include <QMatrix4x4>

GeometryObject::GeometryObject(QObject *parent) : RenderableObject(parent)
{
    objectColor = QColor(255,128,128);
}

int GeometryObject::getVertexCount()
{
    return verts.length()/6;
}

void GeometryObject::addVert(QVector3D vert, QVector3D norm)
{
    verts.append(vert.x());
    verts.append(vert.y());
    verts.append(vert.z());

    verts.append(norm.x());
    verts.append(norm.y());
    verts.append(norm.z());
    emit vertCountChanged(getVertexCount());
}

void GeometryObject::addTri(int first, int second, int third)
{
    indexes.append(first);
    indexes.append(second);
    indexes.append(third);
    needsUpdate = true;
}

void GeometryObject::move(QVector3D movement)
{
    for(int i = 0; i < getVertexCount(); i++)
    {
        verts[i*6 + 0] += movement.x();
        verts[i*6 + 1] += movement.y();
        verts[i*6 + 2] += movement.z();
    }
    position += movement;
}

void GeometryObject::rotate(QVector3D rotation)
{
    QVector3D v;
    QVector3D n;
    QMatrix4x4 m;
    m.setToIdentity();
    m.rotate(rotation.x(),1,0,0);
    m.rotate(rotation.y(),0,1,0);
    m.rotate(rotation.z(),0,0,1);
    for(int i = 0; i < getVertexCount(); i++)
    {
        v = QVector3D(verts[i*6 + 0],verts[i*6 + 1],verts[i*6 + 2]);
        n = QVector3D(verts[i*6 + 3],verts[i*6 + 4],verts[i*6 + 5]) - v - position;
        v -= position;
        v = m*v;
        n = m*n;
        v += position;
        n += position + v;
        verts[i*6 + 0] = v.x();
        verts[i*6 + 1] = v.y();
        verts[i*6 + 2] = v.z();
        verts[i*6 + 3] = n.x();
        verts[i*6 + 4] = n.y();
        verts[i*6 + 5] = n.z();
    }
}

void GeometryObject::setColor(QColor color)
{
    objectColor = color;
}

QColor GeometryObject::getColor()
{
    return objectColor;
}

void GeometryObject::draw()
{
    glUpdate();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    QOpenGLVertexArrayObject::Binder vaoBinder(&VAO);
    //glDrawArrays(GL_TRIANGLES,0,this->getVertexCount());
    glDrawElements(GL_TRIANGLES,indexes.length(),GL_UNSIGNED_INT,indexes.constData());
}

void GeometryObject::draw(QOpenGLShaderProgram *shaderProgram)
{
    shaderProgram->setUniformValue("objectColor",objectColor);
    draw();
}

void GeometryObject::glUpdate()
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
