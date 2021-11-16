#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <QObject>
#include <qopengl.h>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

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
    void step(int dtMs);
    void addParticle(QVector3D pos);
    void removeParticle(int index);
    void draw();
    //void purge(int count);
    //void purge(float percent);

signals:
    void particleCountChanged(int particleCount);

protected:
    QVector<GLfloat> particles; //XYZ triplets

    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    bool needsUpdate;
    int currentTime;
    void glUpdate();
};

#endif // PARTICLESYSTEM_H
