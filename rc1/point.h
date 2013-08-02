#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point();

    void set(int x, int y, int w, int h);
    void setX(int x);
    void setY(int y);
    void setWidth(int w);
    void setHeight(int h);
    void setT(long t);
    void setTTL(long ttl);
    void setGid(int id);

    int getX();
    int getY();
    double getXn();
    double getYn();
    long getT();
    int getGid();

private:
    int x;
    int y;
    double xn;
    double yn;
    int width;
    int height;
    long t;
    long ttl;
    int gid;
};

#endif // POINT_H
