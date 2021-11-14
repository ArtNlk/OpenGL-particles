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
    void rotate(QQuaternion rot);
    void move(float dh, float df, float dv);
    void move(QVector3D v);

    void stepForward();
    void stepBackward();
    void strafeLeft();
    void strafeRight();
    void moveUp();
    void moveDown();

    void setSpeed(float _speed);

protected:
    static float fov;
    static float aspectRatio;
    static float nearPlane;
    static float farPlane;
    float speed;
    QMatrix4x4 projectionMatrix;
};

#endif // CAMERA_H
