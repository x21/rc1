#include "paintstat.h"

PaintStat::PaintStat()
{
    nparams=0;
}

void PaintStat::paint(RC1 *view, QPainter *pnt)
{
    pnt->setBrush(Qt::red);
    pnt->setFont(QFont("Sans",30,5));
    QString fpss;
    fpss.sprintf("%d fps@",view->getFps());
    fpss.append(view->getFpsT()->toString());
    pnt->drawText(10,50,fpss);
}

int PaintStat::getParamCount() {
    return nparams;  // 8*9 parameters
}

float PaintStat::getParam(quint16 n) {
    if(n<nparams) {
        return params[n];
    }
}

float PaintStat::getParamMin(quint16 n) {
    return 0;
}

float PaintStat::getParamMax(quint16 n) {
    return 0;
}

void PaintStat::setParam(quint16 n, float v) {
    if(n<nparams) {
        params[n]=v;
    }
}
