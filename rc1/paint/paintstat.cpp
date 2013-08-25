#include "paintstat.h"

PaintStat::PaintStat()
{
    nparams=0;
}

void PaintStat::paint(RC1 *rc1, QPainter *pnt)
{
    int fontsize=rc1->getLayout()->getWidth()/64;
    int linehight=rc1->getLayout()->getWidth()/36;
    EventStat * evstat = rc1->getEvstat();
    pnt->setPen(Qt::black);
    pnt->setFont(QFont("Sans",fontsize,5));
    QString fpss;
    fpss.sprintf("rc1.c1audio.com : %d fps@", rc1->getFps());
    fpss.append(rc1->getFpsT()->toString());
    pnt->drawText(10,2*linehight,fpss);
    fpss.sprintf("%d touchs | %d start | %d move | %d end | %d trans",
                 evstat->getToucheventcount(),
                 evstat->getTouchstartcount(),
                 evstat->getTouchmovecount(),
                 evstat->getTouchendcount(),
                 evstat->getTransitioncount());
    pnt->drawText(10,3*linehight,fpss);
    fpss.sprintf("%d osc | %d noteon | %d noteoff | %d alreadyon",
                 evstat->getOsccount(),
                 evstat->getOscnoteoncount(),
                 evstat->getOscnoteoffcount(),
                 evstat->getAlreadyoncount());
    pnt->drawText(10,4*linehight,fpss);
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
