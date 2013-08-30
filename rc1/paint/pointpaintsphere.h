#ifndef POINTPAINTSPHERE_H
#define POINTPAINTSPHERE_H

#include "ipointpaint.h"

class PointPaintSphere : public IPointPaint
{
public:
    PointPaintSphere();
    virtual void paint(Point *point, RC1 *v, QPainter *pnt);
    virtual int getParamCount();
    virtual float getParam(quint16 n);
    virtual float getParamMin(quint16 n);
    virtual float getParamMax(quint16 n);
    virtual void setParam(quint16 n, float v);
};

#endif // POINTPAINTSPHERE_H
