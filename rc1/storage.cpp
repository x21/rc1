#include "storage.h"
#include <QDebug>

Storage::Storage()
{
    len=1000;
    x = new int[len];
    y = new int[len];
    put_pnt=0;
}

void Storage::put(int x, int y)
{
//    qDebug() << "Storage put " << put_pnt << " x: " << x << " y: " << y;
    this->x[put_pnt]=x;
    this->y[put_pnt]=y;
    put_pnt++;
    if(put_pnt>=len) {
        put_pnt=0;
    }
}

int Storage::getX(int i)
{
    if(i<len) {
        int j=put_pnt-i;
        if(j<0) {
            j+=len;
        }
        return x[j];
    } else {
        return -1;
    }
}

int Storage::getY(int i)
{
    if(i<len) {
        int j=put_pnt-i;
        if(j<0) {
            j+=len;
        }
        return y[j];
    } else {
        return -1;
    }
}

int Storage::getLen()
{
    return len;
}
