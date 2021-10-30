#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QMatrix4x4>

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera(QObject *parent = nullptr);
    ~Camera();

    QMatrix4x4 getMatrix();

    float getSpeed();

public slots:
    void rotate(float dh, float dv);
    void rotate(QVector3D v);
    void rotate(QQuaternion v);
    void setRotation(QQuaternion rotation);
    void setRotation(QVector3D rotation);
    void move(float dh, float df, float dv);
    void move(QVector3D v);
    void moveTo(QVector3D pos);

    void stepForward();
    void stepBackward();
    void strafeLeft();
    void strafeRight();

    void setSpeed(float speed);

protected:
    float speed;
    QMatrix4x4 projectionMatrix;
};

#endif // CAMERA_H
