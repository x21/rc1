#include "storage.h"
#include <QDebug>

Storage::Storage()
{
    len=100;
    pnts = new Point*[len];
    put_pnt=0;
    for(int i=0;i<len;i++) {
        pnts[i]=new Point();
    }
}

/*
void Storage::put(Point *p)
{
//    qDebug() << "Storage put " << put_pnt;
    if(pnts[put_pnt]!=NULL) {
        delete(pnts[put_pnt]);
    }
    pnts[put_pnt]=p;
}
*/

void Storage::next()
{
    put_pnt++;
    if(put_pnt>=len) {
        put_pnt=0;
    }
}

Point *Storage::getPoint(int i)
{
    if(i<len) {
        int j=put_pnt-i;
        if(j<0) {
            j+=len;
        }
        return pnts[j];
    } else {
        return NULL;
    }
}

int Storage::getLen()
{
    return len;
}
