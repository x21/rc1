#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

#include <QEvent>
#include "point.h"
#include "comm/isender.h"
#include "conf/layoutmodel.h"

class IEventHandler //: public QObject
{
public:
    virtual ~IEventHandler() {}
    //    virtual void processPoint(int touchPointId, Qt::TouchPointState touchPointState, quint16 touchPointPosX, quint16 touchPointPosY)=0;
    virtual void processPoint(Point * p)=0;
};

#endif // IEVENTHANDLER_H
