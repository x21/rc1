#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

#include <QEvent>
#include "rc1.h"
#include "point.h"

class RC1;

class IEventHandler //: public QObject
{
public:
    virtual ~IEventHandler() {}
    virtual void processPoint(Point *, RC1 *)=0;
};

#endif // IEVENTHANDLER_H
