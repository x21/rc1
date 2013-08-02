#include <QDebug>
#include <QtWidgets>
#include <QTimer>
#include "view.h"
#include "event/eventhandlerrect.h"
#include "comm/senderdebug.h"
#include "paint/paintbgshapes.h"
#include "paint/paintshapes.h"
#include "paint/paintstat.h"


View::View(QWidget *parent) :
    QGLWidget(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents,true);
    qDebug() << "View() size:" << width() << " " << height();
    eventId = 1;
    nomouse = false;

    storage=new Storage();
    layout=new LayoutModel();
    ehand=new EventHandlerRect(layout, new SenderDebug());
    layout->calcGeo(width(),height());

    painters=new IPaint*[3];
    painters[0]=new PaintBgShapes();
    painters[1]=new PaintShapes();
    painters[2]=new PaintStat();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

    fpsT.start();
    fcnt=0;    
}

void View::paintEvent(QPaintEvent *event)
{
    now=QDateTime::currentMSecsSinceEpoch();

    if(fpsT.elapsed()>1000) {
        fpsT.restart();
        fps=fcnt;
        fcnt=0;
    }

    QPainter painter(this);

    painters[0]->paint(this,&painter);
    painters[1]->paint(this,&painter);
    painters[2]->paint(this,&painter);

/*    painter.fillRect(0,0,width(),height(),Qt::red);
    painter.fillRect(20,20,width()-40,height()-40,Qt::black);
    painter.fillRect(40,40,width()-80,height()-80,Qt::green);*/

    fcnt++;
}

void View::resizeEvent(QResizeEvent *)
{
    //qDebug() << "resize event";
    layout->calcGeo(width(),height());
    for(int i=0;i<storage->getLen();i++) {
        storage->getPoint(i)->setWidth(width());
        storage->getPoint(i)->setHeight(height());
    }
}

bool View::event(QEvent *event)
{
    QList<QTouchEvent::TouchPoint> touchPoints;
    QString sEvent;
    if( event->type()==QEvent::TouchEnd ||
            event->type()==QEvent::TouchUpdate ||
            event->type()==QEvent::TouchBegin ) {

        QDateTime ct = QDateTime::currentDateTime();
        long t=ct.toMSecsSinceEpoch();

        nomouse=true;

        if(event->type()==QEvent::TouchEnd) {
            sEvent="TouchEnd";
        } else if(event->type()==QEvent::TouchUpdate) {
            sEvent="TouchUpdate";
        } else if(event->type()==QEvent::TouchBegin) {
            sEvent="TouchBegin";
        }

        touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
        foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
            //            qDebug() << sEvent << ": x:" << touchPoint.pos().x() << " y:" << touchPoint.pos().y() << " t: " << t1.tv_sec << "." << t1.tv_usec;
            Point * p = storage->getPoint(0);
            p->set(touchPoint.pos().x(),touchPoint.pos().y(),this->width(),this->height());
            p->setT(t);
            p->setGid(touchPoint.id());
            storage->next();
            ehand->processPoint(touchPoint.id(),touchPoint.state(),touchPoint.pos().x(),touchPoint.pos().y());
        }
        return true;
    } else if(  !nomouse && (
                    event->type()==QEvent::MouseMove ||
                    event->type()==QEvent::MouseButtonPress ||
                    event->type()==QEvent::MouseButtonRelease )) {

        QDateTime ct = QDateTime::currentDateTime();
        long t=ct.toMSecsSinceEpoch();

        const QMouseEvent * meve = static_cast<QMouseEvent *>(event);

        Qt::TouchPointState state;

        if(event->type()==QEvent::MouseMove) {
            sEvent="MouseMove";
            state=Qt::TouchPointMoved;
        } else if(event->type()==QEvent::MouseButtonPress) {
            sEvent="MouseButtonPress";
            state=Qt::TouchPointPressed;
            eventId++;
        } else if(event->type()==QEvent::MouseButtonRelease) {
            sEvent="MouseButtonRelease";
            state=Qt::TouchPointReleased;
        }
        //        qDebug() << sEvent << ": x:" << meve->pos().x() << " y:" << meve->pos().y() << " t: " << t1.tv_sec << "." << t1.tv_usec;

        Point * p = storage->getPoint(0);
        p->set(meve->pos().x(),meve->pos().y(),this->width(),this->height());
        p->setT(t);
        p->setGid(eventId);
        storage->next();
        ehand->processPoint(eventId,state,meve->pos().x(),meve->pos().y());
        return true;
    }
    return QWidget::event(event);
}

Storage *View::getStorage() const
{
    return storage;
}

LayoutModel *View::getLayout() const
{
    return layout;
}

long View::getNow()
{
    return now;
}

int View::getFps()
{
    return fps;
}

QTime * View::getFpsT()
{
    return &fpsT;
}
