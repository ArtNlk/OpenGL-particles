#ifndef GEOMERTYOBJECT_H
#define GEOMERTYOBJECT_H

#include <QObject>
#include "qopengl.h"

class GeomertyObject : public QObject
{
    Q_OBJECT
public:
    explicit GeomertyObject(QObject *parent = nullptr);

signals:

protected:


};

#endif // GEOMERTYOBJECT_H
