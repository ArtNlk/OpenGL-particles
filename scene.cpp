#include "scene.h"

Scene::Scene(QObject *parent) : QObject(parent)
{

}

QMatrix4x4 Scene::cameraMatrix()
{
    return sceneCamera.getMatrix();
}

const GLfloat *Scene::particlePositions()
{
    return particleSystem.constData();
}

int Scene::particleCount()
{
    return particleSystem.getParticleCount();
}

void Scene::moveForward()
{
    sceneCamera.stepForward();
}

void Scene::moveBackward()
{
    sceneCamera.stepBackward();
}

void Scene::moveLeft()
{
    sceneCamera.strafeLeft();
}

void Scene::moveRight()
{
    sceneCamera.strafeRight();
}

void Scene::moveUp()
{
    sceneCamera.moveUp();
}

void Scene::moveDown()
{
    sceneCamera.moveDown();
}

void Scene::setCameraSpeed(float speed)
{
    sceneCamera.setSpeed(speed);
}

void Scene::addParticle(QVector3D pos)
{
    particleSystem.addParticle(pos);
}

void Scene::removeParticle(int index)
{
    particleSystem.removeParticle(index);
}

void Scene::step(float dt)
{
    particleSystem.step(dt);
}
