#ifndef PAINTERBGSHAPES_H
#define PAINTERBGSHAPES_H

#include "ipaint.h"

class PaintBgShapes : public IPaint
{
public:
    PaintBgShapes();
    virtual void paint(RC1 *view, QPainter *pnt);
    virtual int getParamCount();
    virtual float getParam(quint16 n);
    virtual float getParamMin(quint16 n);
    virtual float getParamMax(quint16 n);
    virtual void setParam(quint16 n, float v);

private:
    quint8 sPenAct;
    quint8 lPenAct;
    quint8 sPenPsv;
    quint8 lPenPsv;
    quint8 sBrushAct;
    quint8 lBrushAct;
    quint8 sBrushPsv;
    quint8 lBrushPsv;
};

#endif // PAINTERBGSHAPES_H
