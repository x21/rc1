#ifndef IPAINTER_H
#define IPAINTER_H

#include <QtGui>
#include "rc1.h"

class RC1;

class IPaint
{
public:
    virtual ~IPaint() {}
    virtual void paint(RC1 *, QPainter *) = 0;
    virtual int getParamCount() = 0;
    virtual float getParam(quint16 n) = 0;
    virtual float getParamMin(quint16 n) = 0;
    virtual float getParamMax(quint16 n) = 0;
    virtual void setParam(quint16 n, float v) = 0;
};

#endif // PAINTER_H
