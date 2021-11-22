#include "light.h"

Light::Light(int r, int g, int b, int intensity, QObject *parent) : QObject(parent),
    RGBColor(r,g,b,intensity)
{

}

Light::Light(QColor color, QObject *parent) : QObject(parent),
    RGBColor(color)
{

}

void Light::setIntensity(float intensity)
{
    RGBColor.setAlphaF(qBound(0.f,intensity,1.f));
}

float Light::getIntensity()
{
    return RGBColor.alphaF();
}

void Light::setColor(QColor color)
{
    RGBColor = color;
}

QColor Light::getColor()
{
    QColor out;
    out.setRedF(RGBColor.redF()*RGBColor.alphaF());
    out.setGreenF(RGBColor.greenF()*RGBColor.alphaF());
    out.setBlueF(RGBColor.blueF()*RGBColor.alphaF());
    return out;
}
