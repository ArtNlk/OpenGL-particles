#include "renderwidget.h"

#include <QMouseEvent>
#include <QtMath>

#include "gldebug.h"

RenderWidget::RenderWidget(QWidget *parent):
    scene(nullptr),
    particleProgram(nullptr),
    phongProgram(nullptr),
    pointSize(10.f)
{
    setFocusPolicy(Qt::StrongFocus);
}

RenderWidget::~RenderWidget()
{

}

void RenderWidget::setScene(Scene *scene)
{
    this->scene = scene;
}

void RenderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.25, 0.25, 0.25, 1);
    setupParticleProgram();
    setupPhongProgram();
}

void RenderWidget::setupParticleProgram()
{
    particleProgram = new QOpenGLShaderProgram;
    particleProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,":/DefaultVShader.glsl");
    particleProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,":/DefaultFShader.glsl");
    particleProgram->bindAttributeLocation("vertex", 0);
}

void RenderWidget::setupPhongProgram()
{
    phongProgram = new QOpenGLShaderProgram;
    phongProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,":/PhongVertexShader.glsl");
    phongProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,":/PhongShader.glsl");
    phongProgram->bindAttributeLocation("vertex", 0);
    phongProgram->bindAttributeLocation("vertexNormal", 1);
}

void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

    particleProgram->bind();
    particleProgram->setUniformValue("cameraMatrix",scene->cameraMatrix());
    particleProgram->setUniformValue("camPos",scene->cameraPosition());
    particleProgram->setUniformValue("pointSize",pointSize);

    scene->drawParticles(particleProgram);
    particleProgram->release();

    phongProgram->bind();
    phongProgram->setUniformValue("cameraMatrix",scene->cameraMatrix());
    phongProgram->setUniformValue("camPos",scene->cameraPosition());
    phongProgram->setUniformValue("pointSize",pointSize);
    phongProgram->setUniformValue("ambientLight",scene->getAmbientLight());
    phongProgram->setUniformValue("sunColor",scene->getSunColor());
    phongProgram->setUniformValue("sunDir",scene->getSunDir());
    scene->drawObjects(phongProgram);
    phongProgram->release();
}

void RenderWidget::resizeGL(int width, int height)
{

}

void RenderWidget::mousePressEvent(QMouseEvent *event)
{
    lastMousePos = event->pos();
}

void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = event->x() - lastMousePos.x();
    float dy = event->y() - lastMousePos.y();
    if (event->buttons() & Qt::LeftButton)
    {
       scene->rotateCamera(dx,dy);
       update();
    }
    lastMousePos = event->pos();
}

void RenderWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_W:
        scene->moveForward();
            break;
        case Qt::Key_A:
        scene->moveLeft();
            break;
        case Qt::Key_S:
        scene->moveBackward();
            break;
        case Qt::Key_D:
        scene->moveRight();
            break;
        case Qt::Key_Space:
        scene->moveUp();
            break;
        case Qt::Key_Z:
        scene->moveDown();
            break;
    }
    update();
}

void RenderWidget::wheelEvent(QWheelEvent *event)
{
    pointSize += event->angleDelta().y()/10.f;
    pointSize = qBound(1.f,pointSize,100.f);

    update();
}
