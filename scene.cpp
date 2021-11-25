#include "scene.h"

#include <QDebug>

Scene::Scene(QObject *parent) : QObject(parent)
{

    objects.append(new TestBox(1.5));
    objects.append(new Plane(10));
    objects[0]->move(QVector3D(0,1,0));
    objects[1]->setColor(QColor(93, 201, 111));
    ambientLight.setIntensity(0.1);
    sunLight.setIntensity(0.3);
    sunLight.setDirection(QVector3D(-45,45,0));
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

QColor Scene::getAmbientLight()
{
    return ambientLight.getColor();
}

QColor Scene::getSunColor()
{
    return sunLight.getColor();
}

QVector3D Scene::getSunDir()
{
    return sunLight.getDirection();
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

void Scene::drawParticles(QOpenGLShaderProgram *shaderProgram)
{
    particleSystem.draw();
}

void Scene::drawObjects(QOpenGLShaderProgram *shaderProgram)
{
    for(int i = 0; i < objects.length(); i++)
    {
        objects[i]->draw(shaderProgram);
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

void Scene::setAmbientLightColor(QColor lightColor)
{
    ambientLight.setColor(lightColor);
}

void Scene::setSunColor(QColor color)
{
    sunLight.setColor(color);
}

void Scene::setSunDir(QVector3D dir)
{
    sunLight.setDirection(dir);
}

void Scene::step(int dtMs)
{
    particleSystem.step(dtMs);
    objects[0]->rotate(QVector3D(0.1,0.2,0.3));
}
