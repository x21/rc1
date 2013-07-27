#ifndef STORAGE_H
#define STORAGE_H

class Storage
{
public:
    Storage();
    void put(int x, int y);
    int getX(int i);
    int getY(int i);
    int getLen();

private:
    int * x;
    int * y;
    int len;
    int put_pnt;
};

#endif // STORAGE_H
