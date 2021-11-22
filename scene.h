#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QMatrix4x4>
#include <QColor>

#include "camera.h"
#include "particlesystem.h"
#include "geomertyobject.h"
#include "light.h"
#include "directionallight.h"

class Scene : public QObject
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    QMatrix4x4 cameraMatrix();

    const GLfloat* particlePositions();
    int particleCount();
    QVector3D cameraPosition();

    QColor getAmbientLight();

    QColor getSunColor();
    QVector3D getSunDir();

public slots:
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void rotateCamera(float dh, float dv);
    void moveCamera(QVector3D mov);

    void drawParticles(QOpenGLShaderProgram* shaderProgram);
    void drawObjects(QOpenGLShaderProgram* shaderProgram);

    void setCameraSpeed(float speed);

    void addParticle(QVector3D pos);
    void removeParticle(int index);

    void setAmbientLight(QColor lightColor);

    void setSunColor(QColor color);
    void setSunDir(QVector3D dir);

    void step(int dtMs);

signals:

protected:
  Camera sceneCamera;
  ParticleSystem particleSystem;
  QVector<RenderableObject*> objects;
  Light ambientLight;
  DirectionalLight sunLight;
};

#endif // SCENE_H
