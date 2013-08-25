#ifndef IPOINTPAINTER_H
#define IPOINTPAINTER_H

#include <QtGui>
#include "rc1.h"

class RC1;

class IPointPaint
{
public:
    virtual ~IPointPaint() {}
    virtual void paint(Point *, RC1 *, QPainter *) = 0;
    virtual int getParamCount() = 0;
    virtual float getParam(quint16 n) = 0;
    virtual float getParamMin(quint16 n) = 0;
    virtual float getParamMax(quint16 n) = 0;
    virtual void setParam(quint16 n, float v) = 0;
};
#endif // IPOINTPAINTER_H
