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
#include <QDebug>
#include <QtWidgets>
#include <QTimer>
#include "rc1.h"
#include "event/eventhandlerrect.h"
#include "comm/senderdebug.h"
#include "comm/senderoscpuredata.h"
#include "paint/paintbgshapes.h"
#include "paint/pointpaintshape.h"
#include "paint/pointpaintsphere.h"
#include "paint/paintstat.h"


RC1::RC1(QWidget *parent) :
    QGLWidget(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents,true);
    qDebug() << "View() size:" << width() << " " << height();
    eventId = 1;
    nomouse = false;
    ttl=10000;

    storage=new Storage();
    layout=new LayoutModel();
    sender=new SenderOscPuredata(this);
//    sender=new SenderDebug();
    ehand=new EventHandlerRect();
    evstat=new EventStat();

    layout->calcGeo(width(),height());    

    nPrePainters=1;
    prepainters=new IPaint*[nPrePainters];
    prepainters[0]=new PaintBgShapes();

    nPointPainters=5;
    pointpainters=new IPointPaint*[nPointPainters];
//    pointpainters[0]=new PointPaintSphere();
    pointpainters[0]=new PointPaintShape();
    pointpainters[1]=new PointPaintShape();
    pointpainters[2]=new PointPaintShape();
    pointpainters[3]=new PointPaintShape();
    pointpainters[4]=new PointPaintShape();

    nPostPainters=1;
    postpainters=new IPaint*[nPostPainters];
    postpainters[0]=new PaintStat();
    
    painterOn=new bool[nPrePainters+nPointPainters+nPostPainters];
    painterOn[0]=true;
    painterOn[1]=true;
    painterOn[2]=false;
    painterOn[3]=false;
    painterOn[4]=false;
    painterOn[5]=false;
    painterOn[6]=true;

    oscin = new QOscServer(3333,this);
    oscin->registerPathObject(this);

    resetStat();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

    fpsT.start();
    fcnt=0;    
}

void RC1::paintEvent(QPaintEvent *event)
{
    now=QDateTime::currentMSecsSinceEpoch();

    if(fpsT.elapsed()>1000) {
        fpsT.restart();
        fps=fcnt;
        fcnt=0;
//        qDebug() << "fps: " << fps;
    }

    QPainter painter(this);
    int k=0;
    for(int i=0;i<nPrePainters;i++) {
        if(painterOn[k]) {
            prepainters[i]->paint(this,&painter);
        }
        k++;
    }
    for(int i=storage->getLen()-1;i>0;i--) {
        Point * p = storage->getPoint(i);
        if(p!=NULL) {
            int lifetime=now-p->getT();
            if(lifetime >0 && lifetime< ttl) {
                if(p->getX()>=0 && p->getY()>=0) {
                    for(int j=0;j<nPointPainters;j++) {
                        if(painterOn[j+k]) {
                            pointpainters[j]->paint(p,this,&painter);
                        }
                    }
                }
            }
        }
    }
    k+=nPointPainters;
    for(int i=0;i<nPostPainters;i++) {
        if(painterOn[k]) {
            postpainters[i]->paint(this,&painter);
        }
        k++;
    }
    fcnt++;
}

void RC1::resizeEvent(QResizeEvent *)
{
    //qDebug() << "resize event";
    layout->calcGeo(width(),height());
    for(int i=0;i<storage->getLen();i++) {
        storage->getPoint(i)->setWidth(width());
        storage->getPoint(i)->setHeight(height());
    }
}

bool RC1::event(QEvent *event)
{
    QList<QTouchEvent::TouchPoint> touchPoints;
    if( event->type()==QEvent::TouchEnd ||
            event->type()==QEvent::TouchUpdate ||
            event->type()==QEvent::TouchBegin ) {

        QDateTime ct = QDateTime::currentDateTime();
        long t=ct.toMSecsSinceEpoch();

        nomouse=true;
        touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
        foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
            //            qDebug() << sEvent << ": x:" << touchPoint.pos().x() << " y:" << touchPoint.pos().y() << " t: " << t1.tv_sec << "." << t1.tv_usec;
            evstat->incToucheventcount();
            Point * p = storage->getPoint(0);
            p->set(touchPoint.pos().x(),touchPoint.pos().y(),this->width(),this->height());
            p->setT(t);
            p->setGid(touchPoint.id());
            p->setState(touchPoint.state());
            storage->next();
            ehand->processPoint(p,this);
        }
        return true;
    } else if( !nomouse && (
                    event->type()==QEvent::MouseMove ||
                    event->type()==QEvent::MouseButtonPress ||
                    event->type()==QEvent::MouseButtonRelease )) {

        QDateTime ct = QDateTime::currentDateTime();
        long t=ct.toMSecsSinceEpoch();

        const QMouseEvent * meve = static_cast<QMouseEvent *>(event);

        Qt::TouchPointState state;

        if(event->type()==QEvent::MouseMove) {
            state=Qt::TouchPointMoved;
        } else if(event->type()==QEvent::MouseButtonPress) {
            state=Qt::TouchPointPressed;
            eventId++;
        } else if(event->type()==QEvent::MouseButtonRelease) {
            state=Qt::TouchPointReleased;
        }
        //        qDebug() << sEvent << ": x:" << meve->pos().x() << " y:" << meve->pos().y() << " t: " << t1.tv_sec << "." << t1.tv_usec;
        evstat->incToucheventcount();
        Point * p = storage->getPoint(0);
        p->set(meve->pos().x(),meve->pos().y(),this->width(),this->height());
        p->setT(t);
        p->setGid(eventId);
        p->setState(state);
        storage->next();
        ehand->processPoint(p,this);
        return true;
    }
    return QWidget::event(event);
}

void RC1::signalData(QString path, QVariant data, QHostAddress * host, quint16 port)
{
//    qDebug() << "got osc signal " << path << " data " << data << " source " << host->toString();
    int ignoreIndex=ignoreAddr.indexOf(*host);
    if(ignoreIndex==-1) {
        QList<QVariant> dl=data.toList();

        if(path=="/misuco/fullscreen") {
            if(dl.size()==1) {
                if(dl.at(0).toInt()>0) {
                    setWindowState(Qt::WindowFullScreen);
                } else {
                    setWindowState(Qt::WindowNoState);
                }
            }
        }

        if(path=="/misuco/ignore") {
            if(dl.size()==1) {
                ignoreAddr.append(QHostAddress(dl.at(0).toString()));
            }
        }

        if(path=="/misuco/listen") {
            if(dl.size()==1) {
                int i=ignoreAddr.indexOf(QHostAddress(dl.at(0).toString()));
                if(i>=0) {
                    ignoreAddr.removeAt(i);
                }
            }
        }

        if(path=="/misuco/ttl") {
            if(dl.size()==1) {
                ttl=dl.at(0).toInt();
            }
        }

        if(path=="/misuco/painter") {
            if(dl.size()==2) {
                painterOn[dl.at(0).toInt()]=dl.at(1).toBool();
            }
        }
        
        if(path=="/tuio/2Dcur") {
            qDebug() << "got /tuio/2Dcur signal " << path << " data " << data << " source " << host->toString();
            if(dl.size()>0) {
                
                // find source host in ip source adress table
                qint16 sourceId=tuioSources.indexOf(host->toIPv4Address());
                // if not yet exists, add it
                if(sourceId==-1) {
                    tuioSources.append(host->toIPv4Address());
                    sourceId=tuioSources.size()-1;
                }
                sourceId++; // source Id=0 is for local events
                
                if(dl.at(0)=="set") {
                    QDateTime ct = QDateTime::currentDateTime();
                    long t=ct.toMSecsSinceEpoch();
                    
                    quint32 sid=dl.at(1).toInt()%65536 + sourceId*65536;
                    // session id:
                    // bit0-15: sid according message
                    // bit16-31: sourceId according to index in ip list
                    quint16 xpos=dl.at(2).toFloat()*layout->getWidth();
                    quint16 ypos=dl.at(3).toFloat()*layout->getHeight();
                    Qt::TouchPointState touchType=Qt::TouchPointMoved;
                    if(!tuioAlive.contains(sid)) {
                        tuioAlive.append(sid);
                        touchType=Qt::TouchPointPressed;
                        //                   qDebug() << "new point with id " << sid;
                    }
                    Point * p = storage->getPoint(0);
                    p->set(xpos,ypos,this->layout->getWidth(),this->layout->getHeight());
                    p->setT(t);
                    p->setGid(sid);
                    p->setState(touchType);
                    storage->next();
                    ehand->processPoint(p,this);
                    
                }
                if(dl.at(0)=="alive") {
                    for(int i=0;i<tuioAlive.size();i++) {
                        if(tuioAlive.at(i)/65536==sourceId) {
                            if(!dl.contains(tuioAlive.at(i)-sourceId*65536)) {
                                QDateTime ct = QDateTime::currentDateTime();
                                long t=ct.toMSecsSinceEpoch();
                                //                            qDebug() << "removing point with id " << tuioAlive.at(i);
                                Point * p = storage->getPoint(0);
                                p->set(0,0,this->layout->getWidth(),this->layout->getHeight());
                                p->setT(t);
                                p->setGid(tuioAlive.at(i));
                                p->setState(Qt::TouchPointReleased);
                                storage->next();
                                ehand->processPoint(p,this);                                
                                tuioAlive.removeAt(i);
                                i--;
                            }
                        }
                    }
                }
            }
        }
        
        /*
        if(path=="/misuco/channel") {
            if(dl.size()==1) {
                defaultChan=dl.at(0).toInt();
            }
        }


        if(path=="/misuco/painterrst") {
            if(dl.size()==1) {
                int p2rst=dl.at(0).toInt();
                for(int i=0;i<drw[p2rst]->getParamCount();i++) {
                    drw[p2rst]->setParam(i,0);
                }
            }
        }

        if(path=="/misuco/paintparam") {
            if(dl.size()==3) {
                drw[dl.at(0).toInt()]->setParam(dl.at(1).toInt(),dl.at(2).toFloat());
            }
        }

        if(path=="/misuco/scale") {
            if(dl.size()>0) {
                nscale=dl.size();
//                neve=nscale;
//                scale=new int[nscale];
                quint16 i=0;
//                quint16 j=0;
                quint16 offset=0;
                while(i<nscale) {
//                    scale[i]=dl.at(j).toInt()+offset;
                    scale[i]=dl.at(i).toInt();
                    i++;
//                    j++;
//                    if(j>=dl.size()) {
//                        j=0;
//                        offset+=12;
//                    }
                }
                scaleRcv();
                updatePan();
            }
        }

        if(path=="/misuco/scale2d") {
            if(dl.size()>0) {
                rows=0;
                nscale=0;
                neve=nscale;
                cpr[rows] = 0;
                quint16 i=0;    // index source
                quint16 j=0;    // index destination
                while(i<dl.size()) {
                    quint16 val=dl.at(i).toInt();
                    if(val>0) {
                        eve[j]=dl.at(i).toInt();
                        evep[j]=defaultProg;
                        evetype[j]=0;
                        evechan[j]=defaultChan;
                        nscale++;
                        cpr[rows]++;
                        j++;
                    } else {
                        rows++;
                        cpr[rows]=0;
                    }
                    i++;
                }
                rows++;
                updatePan();
            }
        }

 */
    }
}

void RC1::resetStat()
{

    fps=0;
}

Storage *RC1::getStorage() const
{
    return storage;
}

LayoutModel *RC1::getLayout() const
{
    return layout;
}

long RC1::getNow()
{
    return now;
}

int RC1::getFps()
{
    return fps;
}

QTime * RC1::getFpsT()
{
    return &fpsT;
}

long RC1::getTtl() const
{
    return ttl;
}

void RC1::setTtl(long value)
{
    ttl = value;
}

ISender * RC1::getSender() const
{
return sender;
}

EventStat *RC1::getEvstat() const
{
return evstat;
}
