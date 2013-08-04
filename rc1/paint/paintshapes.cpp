#include "paintshapes.h"

PaintShapes::PaintShapes()
{
    nparams=1;
    params=new float[nparams];
    params[0]=5000.0;
    pps=new PointPaintShape();
}

void PaintShapes::paint(View *view, QPainter *pnt)
{
    pnt->setBrush(Qt::green);
    Storage * storage = view->getStorage();
    for(int i=0; i<storage->getLen();i++) {
        Point * p = storage->getPoint(i);
        if(p!=NULL) {
            if(view->getNow()-p->getT() < params[0]) {
                if(p->getX()>=0 && p->getY()>=0) {
                    pps->paint(p,view,pnt);
                }
            }
        }
    }
}

int PaintShapes::getParamCount() {
    return nparams;  // 8*9 parameters
}

float PaintShapes::getParam(quint16 n) {
    if(n<nparams) {
        return params[n];
    }
}

float PaintShapes::getParamMin(quint16 n) {
    return 0;
}

float PaintShapes::getParamMax(quint16 n) {
    return 0;
}

void PaintShapes::setParam(quint16 n, float v) {
    if(n<nparams) {
        params[n]=v;
    }
}
