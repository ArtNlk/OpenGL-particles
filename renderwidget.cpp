#include "renderwidget.h"

#include <QMouseEvent>

#include <QtMath>

RenderWidget::RenderWidget(QWidget *parent):
    scene(nullptr),
    shaderProgram(nullptr),
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

    shaderProgram = new QOpenGLShaderProgram;
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,":/DefaultVShader.glsl");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,":/DefaultFShader.glsl");
    shaderProgram->bindAttributeLocation("vertex", 0);
    shaderProgram->link();

    shaderProgram->bind();
    projectionMatrixLoc = shaderProgram->uniformLocation("cameraMatrix");
    camPosLoc = shaderProgram->uniformLocation("camPos");
    pointSizeLoc = shaderProgram->uniformLocation("pointSize");

    //Test buffer
//    sceneVao.create();
//    QOpenGLVertexArrayObject::Binder vaoBinder(&sceneVao);

//    sceneVbo.create();
//    sceneVbo.bind();
//    sceneVbo.allocate(scene->particlePositions(), scene->particleCount()*3 * sizeof (GLfloat));

//    qDebug() << "Particles: " << scene->particleCount();
//    for(int i = 0; i < scene->particleCount(); i++)
//    {
//        qDebug() << "P" << i
//                 << "\tX:" << scene->particlePositions()[i*3+0]
//                 << "Y:" << scene->particlePositions()[i*3+1]
//                 << "Z:" << scene->particlePositions()[i*3+2];
//    }

//    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
//    f->glEnableVertexAttribArray(0);
//    f->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);

//    sceneVbo.release();



    shaderProgram->release();
}

void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_PROGRAM_POINT_SIZE);

    QOpenGLVertexArrayObject::Binder vaoBinder(&sceneVao);
    shaderProgram->bind();
    shaderProgram->setUniformValue(projectionMatrixLoc,scene->cameraMatrix());
    shaderProgram->setUniformValue(camPosLoc,scene->cameraPosition());
    shaderProgram->setUniformValue(pointSizeLoc,pointSize);

    scene->draw();

    //glDrawArrays(GL_POINTS,0,scene->particleCount());

    shaderProgram->release();
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
