#ifndef STORAGE_H
#define STORAGE_H

#include <point.h>

class Storage
{
public:
    Storage();
    Point *getPoint(int i);
    void next();
    int getLen();

private:
    Point **pnts;
    int len;
    int put_pnt;
    int np;
};

#endif // STORAGE_H
