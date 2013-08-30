#include "pointpaintsphere.h"

PointPaintSphere::PointPaintSphere()
{
}

void PointPaintSphere::paint(Point *point, RC1 *v, QPainter *pnt)
{
    int rad=v->getLayout()->getWidth()*(v->getNow()-point->getT())/v->getTtl();
//    qDebug() << v->getNow() << " " << point->getT() << " " << rad;
    pnt->setBrush(Qt::NoBrush);
    pnt->setPen(Qt::white);
    pnt->drawEllipse(point->getX()-rad,point->getY()-rad, rad*2, rad*2);
}

int PointPaintSphere::getParamCount()
{
    return 0;
}

float PointPaintSphere::getParam(quint16 n)
{
    return 0;
}

float PointPaintSphere::getParamMin(quint16 n)
{
    return 0;
}

float PointPaintSphere::getParamMax(quint16 n)
{
    return 0;
}

void PointPaintSphere::setParam(quint16 n, float v)
{

}
