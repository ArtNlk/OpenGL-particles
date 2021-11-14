#include "renderwidget.h"

RenderWidget::RenderWidget(QWidget *parent):
    scene(nullptr),
    shaderProgram(nullptr)
{

}

void RenderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.5, 0.5, 0.5, 1);

    shaderProgram = new QOpenGLShaderProgram;
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,":/DefaultVShader.glsl");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,":/DefaultFShader.glsl");
    shaderProgram->bindAttributeLocation("vertex", 0);
    shaderProgram->link();

    shaderProgram->bind();
    projectionMatrixLoc = shaderProgram->uniformLocation("cameraMatrix");

    //Test buffer
    sceneVao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&sceneVao);

    sceneVbo.create();
    sceneVbo.bind();
    sceneVbo.allocate(scene->particlePositions(), scene->particleCount() * sizeof (GLfloat));

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat),nullptr);
    sceneVbo.release();

    shaderProgram->release();
}
