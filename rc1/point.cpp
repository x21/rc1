#include "point.h"

Point::Point()
{
    x=0;
    y=0;
    width=1;
    height=1;
    xn=0;
    yn=0;
    t=0;
    gid=0;
}

void Point::set(int x, int y, int w, int h)
{
    this->width=w;
    this->height=h;
    setX(x);
    setY(y);
}

void Point::setX(int x)
{
    this->x=x;
    this->xn=(double)x/(double)width;
}

void Point::setY(int y)
{
    this->y=y;
    this->yn=(double)y/(double)height;
}

void Point::setWidth(int w)
{
    if(w==0) {
        w=1;
    }
    width=w;
    this->x=xn*(double)w;
}

void Point::setHeight(int h)
{
    if(h==0) {
        h=1;
    }
    height=h;
    this->y=yn*(double)h;
}

void Point::setT(long t)
{
    this->t=t;
}


void Point::setGid(int id)
{
    gid = id;
}

int Point::getX()
{
    return x;
}

int Point::getY()
{
    return y;
}

double Point::getXn()
{
    return xn;
}

double Point::getYn()
{
    return yn;
}

long Point::getT()
{
    return t;
}

int Point::getGid()
{
    return gid;
}
