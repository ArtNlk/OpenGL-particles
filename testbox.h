#ifndef TESTBOX_H
#define TESTBOX_H

#include "geometryobject.h"

class TestBox : public GeometryObject
{
    Q_OBJECT
public:
    explicit TestBox(QObject *parent = nullptr);
};

#endif // TESTBOX_H
