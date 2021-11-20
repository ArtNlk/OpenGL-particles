#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "renderableobject.h"

class ParticleSystem : public RenderableObject
{
    Q_OBJECT
public:
    explicit ParticleSystem(QObject *parent = nullptr);

    const GLfloat *constData();
    int getParticleCount();

    QVector3D getParticleAt(int index);
    void setParticleAt(QVector3D particle, int index);


public slots:
    void step(int dtMs);
    void addParticle(QVector3D pos);
    void removeParticle(int index);
    void draw() override;
    //void purge(int count);
    //void purge(float percent);

signals:
    void particleCountChanged(int particleCount);

protected:
    QVector<GLfloat> particles; //XYZ triplets

    int currentTime;
    void glUpdate() override;
};

#endif // PARTICLESYSTEM_H
