#ifndef PAINTSTAT_H
#define PAINTSTAT_H

#include "ipaint.h"

class PaintStat : public IPaint
{
public:
    PaintStat();
    virtual void paint(RC1 *rc1, QPainter *pnt);
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
    QString platform_os;
    int fontDiv;
    int lineDiv;
};

#endif // PAINTSTAT_H
