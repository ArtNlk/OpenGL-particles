#include "scene.h"

Scene::Scene(QObject *parent) : QObject(parent)
{
    GeomertyObject* obj = new GeomertyObject();
    objects.append(obj);

    obj->addVert(QVector3D(1,0,1),QVector3D(0,1,0));
    obj->addVert(QVector3D(1,0,-1),QVector3D(0,1,0));
    obj->addVert(QVector3D(-1,0,1),QVector3D(0,1,0));
    obj->addVert(QVector3D(-1,0,-1),QVector3D(0,1,0));

    obj->addVert(QVector3D(1,-1,1),QVector3D(1,0,1));
    obj->addVert(QVector3D(1,-1,-1),QVector3D(1,0,0));
    obj->addVert(QVector3D(-1,-1,1),QVector3D(0,0,1));

    obj->addTri(0,1,2);
    obj->addTri(1,3,2);
    obj->addTri(4,1,0);
    obj->addTri(4,5,1);
    obj->addTri(0,2,6);
    obj->addTri(6,4,0);

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

void Scene::setAmbientLight(QColor lightColor)
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
}
