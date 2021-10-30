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


public slots:
    void step(float dt);
    void addParticle(QVector3D pos);
    void removeParticle(int index);
    void purge(int count);
    void purge(float percent);

signals:

protected:
    QVector<GLfloat> particles;
    int particleCount;
};

#endif // PARTICLESYSTEM_H
