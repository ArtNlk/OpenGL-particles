#ifndef LIGHT_H
#define LIGHT_H

#include <QObject>
#include <QColor>

class Light : public QObject
{
    Q_OBJECT
public:
    Light(int r = 255, int g=255, int b=255, int a = 255,QObject *parent = nullptr);
    Light(QColor color,QObject *parent = nullptr);

public slots:
    void setIntensity(float intensity);
    float getIntensity();

    void setColor(QColor color);
    QColor getColor();

signals:

protected:
    QColor RGBColor;
};

#endif // LIGHT_H
