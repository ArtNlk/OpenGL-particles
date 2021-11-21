#include "scene.h"

Scene::Scene(QObject *parent) : QObject(parent)
{
    GeomertyObject* obj = new GeomertyObject();
    objects.append(obj);

    obj->addVert(QVector3D(0,0,0),QVector3D(0,1,0));
    obj->addVert(QVector3D(0,0,-1),QVector3D(0,1,0));
    obj->addVert(QVector3D(-1,0,0),QVector3D(0,1,0));
    obj->addVert(QVector3D(-1,0,-1),QVector3D(0,1,0));

    obj->addTri(0,1,2);
    obj->addTri(1,3,2);
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

QVector3D Scene::cameraPosition()
{
    return sceneCamera.getPosition();
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

void Scene::rotateCamera(float dh, float dv)
{
    sceneCamera.rotate(dh,dv);
}

void Scene::moveCamera(QVector3D mov)
{
    sceneCamera.move(mov);
}

void Scene::drawParticles()
{
    particleSystem.draw();
}

void Scene::drawObjects()
{
    for(int i = 0; i < objects.length(); i++)
    {
        objects[i]->draw();
    }
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

void Scene::step(int dtMs)
{
    particleSystem.step(dtMs);
}
