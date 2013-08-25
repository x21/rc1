#include "paintbgshapes.h"

PaintBgShapes::PaintBgShapes()
{
    sPenAct=160;
    lPenAct=240;
    sBrushAct=160;
    lBrushAct=200;

    sPenPsv=160;
    lPenPsv=10;
    sBrushPsv=160;
    lBrushPsv=80;
}

void PaintBgShapes::paint(RC1 *view, QPainter * pnt) {

    LayoutModel * lay=view->getLayout();

    int iseg=0;
    int xpaint=0;
    int ypaint=0;
    int xpaint1=0;
    int ypaint1=0;

    pnt->setPen(Qt::NoPen);
    for(int y = 0; y < lay->getNrows(); y++) {
        ypaint1=ypaint+lay->getRowheightpx(y);
        xpaint=0;
        for (int x = 0; x < lay->getNseg(y); x ++) {
            xpaint1=xpaint+lay->getSegwidthpx(iseg);

            int col=21*(lay->getNote(iseg)%12);
            int lightP=lPenPsv;
            int lightB=lBrushPsv;
            int satP=sPenPsv;
            int satB=sBrushPsv;

            if(lay->getPressed(iseg) > 0) {
                lightP=lPenAct;
                lightB=lBrushAct;
                satP=sPenAct;
                satB=sBrushAct;
            }

            if(lightB>0) {
                pnt->setBrush(QColor::fromHsl(col,satB,lightB));
            } else {
                pnt->setBrush(Qt::NoBrush);
            }
            if(lightP>0) {
                pnt->setPen(QColor::fromHsl(col,satP,lightP));
            } else {
                pnt->setPen(Qt::NoPen);
            }
            pnt->drawRect(xpaint,ypaint,xpaint1-1,ypaint1-1);

            xpaint=xpaint1;
            iseg++;
        }
        ypaint+=ypaint1;
    }
}

int PaintBgShapes::getParamCount() {
    return 8;
}

float PaintBgShapes::getParam(quint16 n) {
    return 0;
}

float PaintBgShapes::getParamMin(quint16 n) {
    return 0;
}

float PaintBgShapes::getParamMax(quint16 n) {
    return 0;
}

void PaintBgShapes::setParam(quint16 n, float v) {
    switch(n) {
    case 0:
        sPenAct=v;
        break;
    case 1:
        lPenAct=v;
        break;
    case 2:
        sPenPsv=v;
        break;
    case 3:
        lPenPsv=v;
        break;
    case 4:
        sBrushAct=v;
        break;
    case 5:
        lBrushAct=v;
        break;
    case 6:
        sBrushPsv=v;
        break;
    case 7:
        lBrushPsv=v;
    }
}
