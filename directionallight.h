#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "light.h"

#include <QVector3D>

class DirectionalLight : public Light
{
    Q_OBJECT
public:
    explicit DirectionalLight(QVector3D dir = QVector3D(45,0,0), QColor color = QColor(255,255,255,128),QObject *parent = nullptr);

    QVector3D getDirection();

public slots:
    void setDirection(QVector3D newDirection);

protected:
    QVector3D direction;
};

#endif // DIRECTIONALLIGHT_H
