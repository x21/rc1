#ifndef PAINERSHAPES_H
#define PAINERSHAPES_H

#include "ipaint.h"

class PaintShapes : public IPaint
{
public:
    PaintShapes();
    virtual void paint(View *view, QPainter *pnt);
    virtual int getParamCount();
    virtual float getParam(quint16 n);
    virtual float getParamMin(quint16 n);
    virtual float getParamMax(quint16 n);
    virtual void setParam(quint16 n, float v);

private:
    float * params;
    quint16 nparams;
    quint16 ncols;
    quint16 nrows;
};

#endif // PAINERSHAPES_H
