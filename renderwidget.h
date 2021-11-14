#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include "scene.h"

class RenderWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    RenderWidget(QWidget *parent = nullptr);
    ~RenderWidget();

    void setScene(Scene* scene);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Scene* scene;
    QOpenGLShaderProgram* shaderProgram;
    int projectionMatrixLoc;
    QOpenGLVertexArrayObject sceneVao;
    QOpenGLBuffer sceneVbo;
};

#endif // RENDERWIDGET_H
