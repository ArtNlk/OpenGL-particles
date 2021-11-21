#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QMatrix4x4>

#include "camera.h"
#include "particlesystem.h"
#include "geomertyobject.h"

class Scene : public QObject
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    QMatrix4x4 cameraMatrix();

    const GLfloat* particlePositions();
    int particleCount();
    QVector3D cameraPosition();

public slots:
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void rotateCamera(float dh, float dv);
    void moveCamera(QVector3D mov);

    void drawParticles();
    void drawObjects();

    void setCameraSpeed(float speed);

    void addParticle(QVector3D pos);
    void removeParticle(int index);
    //void purgeParticles(int count);
    //void purgeParticles(float percent);

    void step(int dtMs);

signals:

protected:
  Camera sceneCamera;
  ParticleSystem particleSystem;
  QVector<RenderableObject*> objects;
};

#endif // SCENE_H
