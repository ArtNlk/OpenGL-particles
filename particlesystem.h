#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <QObject>
#include <qopengl.h>

class ParticleSystem : public QObject
{
    Q_OBJECT
public:
    explicit ParticleSystem(QObject *parent = nullptr);

    const GLfloat *constData();
    int getParticleCount();

    QVector3D getParticleAt(int index);
    void setParticleAt(QVector3D particle, int index);


public slots:
    void step(float dt);
    void addParticle(QVector3D pos);
    void removeParticle(int index);
    //void purge(int count);
    //void purge(float percent);

signals:
    void particleCountChanged(int particleCount);

protected:
    QVector<GLfloat> particles; //XYZ triplets
};

#endif // PARTICLESYSTEM_H
