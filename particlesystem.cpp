#include "particlesystem.h"

#include <QVector3D>

#include <stdexcept>

ParticleSystem::ParticleSystem(QObject *parent) : QObject(parent),
{

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
    out.setX(particles[index + 0]);
    out.setX(particles[index + 1]);
    out.setX(particles[index + 2]);

    return out;
}

void ParticleSystem::setParticleAt(QVector3D particle, int index)
{
    if (index >= particles.length()/3 || index < 0)
    {
        throw std::out_of_range("setParticleAt: index out of range");
    }

    particles[index + 0] = particle.x();
    particles[index + 1] = particle.y();
    particles[index + 2] = particle.z();
}

void ParticleSystem::step(float dt)
{

}

void ParticleSystem::addParticle(QVector3D pos)
{
    particles.append(pos.x());
    particles.append(pos.y());
    particles.append(pos.z());
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
    emit particleCountChanged(particles.length()/3);
}
