#ifndef IPAINTER_H
#define IPAINTER_H

#include <QtGui>
#include "view.h"

class View;

class IPaint
{
public:
    virtual ~IPaint() {}
    virtual void paint(View *, QPainter *) = 0;
    virtual int getParamCount() = 0;
    virtual float getParam(quint16 n) = 0;
    virtual float getParamMin(quint16 n) = 0;
    virtual float getParamMax(quint16 n) = 0;
    virtual void setParam(quint16 n, float v) = 0;
};

#endif // PAINTER_H
