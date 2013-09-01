/*

Copyright (C) 2013 by Claudio Zopfi, Zurich, Suisse, z@x21.ch

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef VIEW_H
#define VIEW_H

#include <QGLWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QEvent>
#include <QTime>

#include "storage.h"
#include "eventstat.h"
#include "conf/layoutmodel.h"
#include "comm/isender.h"
#include "event/ieventhandler.h"
#include "paint/ipaint.h"
#include "paint/ipointpaint.h"
#include "comm/libofqf/qosctypes.h"

class IPaint;
class IPointPaint;
class IEventHandler;

class RC1 : public QGLWidget, PathObject
{
    Q_OBJECT

public:
    explicit RC1(QWidget *parent = 0);
    Storage *getStorage() const;
    LayoutModel *getLayout() const;
    ISender *getSender() const;
    EventStat *getEvstat() const;
    long getNow();
    int getFps();
    QTime *getFpsT();

    long getTtl() const;
    void setTtl(long value);


protected:
    /*  QGLWidget implementation */
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    bool event(QEvent *event);

    /*  PathObject (Server) implementation */
    virtual void signalData( QString, QVariant, QHostAddress *, quint16 );

private:
    Storage * storage;
    LayoutModel * layout;
    ISender * sender;
    IEventHandler * ehand;
    IPaint ** prepainters;
    IPointPaint ** pointpainters;
    IPaint ** postpainters;
    // painter switch
    bool * painterOn;
    // event statistic
    EventStat * evstat;
    QOscServer * oscin;

    QList<QHostAddress> ignoreAddr;

    int nPrePainters;
    int nPointPainters;
    int nPostPainters;

    long now;
    long ttl;   // time to live for points

    // frame statistic
    int fps;
    int fcnt;
    QTime fpsT;

    // emulated touch point id for mouse events
    int eventId;
    bool nomouse;
    
    // lists, required to manage tuio
    QList<quint32> tuioAlive;
    QList<quint16> tuioSources;
    
    void resetStat();
};

#endif // VIEW_H
