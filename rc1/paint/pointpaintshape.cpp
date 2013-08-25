#include "pointpaintshape.h"

PointPaintShape::PointPaintShape()
{
    nparams=14*6; // rows*cols
    params=new float[nparams];
    for(int i=0;i<nparams;i++) {
        params[i]=0;
    }

    // init x/y
    params[1]=1;
    params[8]=1;

    // radius 5 constant
    params[12]=5;
    params[18]=5;

    // radius by time
    params[17]=50;
    params[23]=50;

    // color pen constant
    params[24]=255;
    params[30]=255;
    params[36]=255;
    params[42]=255;

    // color brish constant
    params[48]=0;
    params[54]=0;
    params[60]=0;
    params[66]=50;

    // rotation constan 45
    params[72]=45;
    // rotate once per lt
    params[77]=360;

    // shape constan 1 (rect)
    params[78]=1;


}

void PointPaintShape::setParam(quint16 n, float v)
{
    params[n]=v;
}

float PointPaintShape::getParamMax(quint16 n)
{
    return 0;
}

float PointPaintShape::getParamMin(quint16 n)
{
    return 1;
}

float PointPaintShape::getParam(quint16 n)
{
    return params[n];
}

int PointPaintShape::getParamCount()
{
    return nparams;
}

void PointPaintShape::paint(Point * point, RC1 * v, QPainter * pnt)
{
    float radX=calcRow(2,point,v);
    float radY=calcRow(3,point,v);
    quint8 hPen=calcRow(4,point,v);
    quint8 sPen=calcRow(5,point,v);
    quint8 lPen=calcRow(6,point,v);
    quint8 aPen=calcRow(7,point,v);
    quint8 hBrush=calcRow(8,point,v);
    quint8 sBrush=calcRow(9,point,v);
    quint8 lBrush=calcRow(10,point,v);
    quint8 aBrush=calcRow(11,point,v);
    qint16 rot=calcRow(12,point,v);
    quint8 shp=calcRow(13,point,v);
    pnt->setPen(QColor::fromHsl(hPen,sPen,lPen,aPen));
    pnt->setBrush(QColor::fromHsl(hBrush,sBrush,lBrush,aBrush));
    /*
    pnt->drawEllipse(calcRow(0,i,pan)-radX,calcRow(1,i,pan)-radY, radX*2, radY*2);
    */
    pnt->translate(calcRow(0,point,v),calcRow(1,point,v));
    pnt->rotate(rot);
    if(shp==0) {
        pnt->drawEllipse(-radX,-radY, radX*2, radY*2);
    } else if(shp==1) {
        pnt->drawRect(-radX,-radY, radX*2, radY*2);
    } else if(shp==2) {
        QPoint points[4] = {
            QPoint(-radX, radY),
            QPoint(radX, radY),
            QPoint(0, -radY),
            QPoint(-radX, radY)
        };
        pnt->drawPolygon(points,4);
    }
    pnt->resetTransform();
}

float PointPaintShape::calcRow(quint16 row, Point * pnt, RC1 * v) {
    quint16 i0=row*6;
    float res=params[i0];       // spalte 0: konstantanteil
    res+=params[i0+1]*pnt->getX();
    res+=params[i0+2]*pnt->getY();
    res+=params[i0+3]*pnt->getXn();
    res+=params[i0+4]*pnt->getYn();
    res+=params[i0+5]*(v->getNow()-pnt->getT())/v->getTtl();
//    qDebug() << " row " << row << " col " << col << " res " << res;
    return res;
}
