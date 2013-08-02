#ifndef POINTPAINTSHAPE_H
#define POINTPAINTSHAPE_H

#include "ipointpaint.h"

class PointPaintShape : public IPointPaint
{
public:
    PointPaintShape();
    virtual void paint(Point *point, View *v, QPainter *pnt);
    virtual int getParamCount();
    virtual float getParam(quint16 n);
    virtual float getParamMin(quint16 n);
    virtual float getParamMax(quint16 n);
    virtual void setParam(quint16 n, float v);

private:
    float * params;
    quint16 nparams;

    float calcRow(quint16 row, Point *pnt, View *v);
};

#endif // POINTPAINTSHAPE_H
