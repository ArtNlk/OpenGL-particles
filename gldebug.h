#ifndef GLDEBUG_H
#define GLDEBUG_H

#include <QDebug>
#include <QtOpenGL>

GLenum glCheckError_(const char *file, int line);
#define GL_CHECK_ERROR glCheckError_(__FILE__, __LINE__);

#endif // GLDEBUG_H
