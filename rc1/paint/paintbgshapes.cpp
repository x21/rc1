#include "paintbgshapes.h"

PaintBgShapes::PaintBgShapes()
{
    sPenAct=160;
    lPenAct=220;
    sPenPsv=160;
    lPenPsv=10;
    sBrushAct=160;
    lBrushAct=100;
    sBrushPsv=160;
    lBrushPsv=80;
}

void PaintBgShapes::paint(RC1 *view, QPainter * pnt) {

    int eIndex=0;
    int xpaint=0;
    int ypaint=0;
    int xpaint1=0;
    int ypaint1=0;

    pnt->setPen(Qt::NoPen);
    for(int y = 0; y < view->getLayout()->getNrows(); y++) {
        ypaint1=ypaint+view->getLayout()->getRowheightpx(y);
        xpaint=0;
        for (int x = 0; x < view->getLayout()->getNseg(y); x ++) {
            xpaint1=xpaint+view->getLayout()->getSegwidthpx(eIndex);

            int col=21*(view->getLayout()->getNote(eIndex)%12);
            int lightP=lPenPsv;
            int lightB=lBrushPsv;
            int satP=sPenPsv;
            int satB=sBrushPsv;

            /*
            for(int i=0;i<pan->seqgrid->getOnIds()->size();i++) {
//                qDebug() << "onId " << i;
                if(xpaint<=pan->seqgrid->getOnXbyN(i)) {
//                    qDebug() << xpaint << " <= " << pan->seqgrid->getOnXbyN(i);
                    if(xpaint+xpaint1>pan->seqgrid->getOnXbyN(i)) {
//                        qDebug() << xpaint+xpaint1 << " > " << pan->seqgrid->getOnXbyN(i);
                        if(ypaint<=pan->seqgrid->getOnYbyN(i)) {
//                            qDebug() << ypaint << " <= " << pan->seqgrid->getOnYbyN(i);
                            if(ypaint+ypaint1>pan->seqgrid->getOnYbyN(i)) {
//                                qDebug() << ypaint+ypaint1 << " > " << pan->seqgrid->getOnYbyN(i);
                                lightP=lPenAct;
                                lightB=lBrushAct;
                                satP=sPenAct;
                                satB=sBrushAct;
                            }
                        }
                    }
                }
            }
            */

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
            pnt->drawRect(xpaint,ypaint,xpaint1,ypaint1);

            xpaint=xpaint1;
            eIndex++;
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
