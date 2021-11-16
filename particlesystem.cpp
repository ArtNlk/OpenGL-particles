#include "particlesystem.h"

#include <QVector3D>

#include <stdexcept>

#include <QOpenGLFunctions>
#include <QDebug>
#include <QtMath>
#include <QMatrix4x4>

ParticleSystem::ParticleSystem(QObject *parent) : QObject(parent)
{
    needsUpdate = false;
    currentTime = 0;
}

const GLfloat *ParticleSystem::constData()
{
    return particles.constData();
}

int ParticleSystem::getParticleCount()
{
    return particles.length()/3;
}

QVector3D ParticleSystem::getParticleAt(int index)
{
    if (index >= particles.length()/3 || index < 0)
    {
        throw std::out_of_range("getParticleAt: index out of range");
    }
    QVector3D out;
    out.setX(particles[index*3 + 0]);
    out.setY(particles[index*3 + 1]);
    out.setZ(particles[index*3 + 2]);
    return out;
}

void ParticleSystem::setParticleAt(QVector3D particle, int index)
{
    if (index >= particles.length()/3 || index < 0)
    {
        throw std::out_of_range("setParticleAt: index out of range");
    }
    particles[index*3 + 0] = particle.x();
    particles[index*3 + 1] = particle.y();
    particles[index*3 + 2] = particle.z();
    needsUpdate = true;
}

void ParticleSystem::step(int dtMs)
{
    currentTime += dtMs;
    QVector3D temp;
    for(int i = 0; i < getParticleCount(); i++)
    {
        temp = getParticleAt(i);
        temp.setY(temp.y()*sin(static_cast<float>(currentTime)/1000.f));
        setParticleAt(temp,i);
    }
}

void ParticleSystem::addParticle(QVector3D pos)
{
    particles.append(pos.x());
    particles.append(pos.y());
    particles.append(pos.z());
    needsUpdate = true;
    emit particleCountChanged(particles.length()/3);
}

void ParticleSystem::removeParticle(int index)
{
    if (index >= particles.length()/3 || index < 0)
    {
        throw std::out_of_range("setParticleAt: index out of range");
    }
    particles.removeAt(index);
    particles.removeAt(index);
    particles.removeAt(index);
    needsUpdate = true;
    emit particleCountChanged(particles.length()/3);
}

void ParticleSystem::draw()
{
    glUpdate();
    QOpenGLVertexArrayObject::Binder vaoBinder(&VAO);
    glDrawArrays(GL_POINTS,0,this->getParticleCount());
}

void ParticleSystem::glUpdate()
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
    VBO.allocate(particles.constData(),particles.length()*sizeof(GLfloat));
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);

    VBO.release();
}
