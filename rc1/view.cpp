#include <QDebug>
#include <QtWidgets>
#include <QTimer>
#include "view.h"
#include "event/eventhandlerrect.h"
#include "comm/senderdebug.h"

View::View(QWidget *parent) :
    QGLWidget(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents,true);
    qDebug() << "View() size:" << width() << " " << height();
    stor=new Storage();
    lmod=new LayoutModel();
    ehand=new EventHandlerRect(lmod, new SenderDebug());
    lmod->calcGeo(width(),height());

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

    fpsT.start();
    fcnt=0;

}

void View::paintEvent(QPaintEvent *event)
{
    if(fpsT.elapsed()>1000) {
        fpsT.restart();
        fps=fcnt;
        fcnt=0;
    }

    QPainter painter(this);

    painter.fillRect(0,0,width(),height(),Qt::red);
    painter.fillRect(20,20,width()-40,height()-40,Qt::black);
    painter.fillRect(40,40,width()-80,height()-80,Qt::green);

    painter.setBrush(Qt::green);
    for(int i=0; i<stor->getLen();i++) {
        painter.fillRect(stor->getX(i),stor->getY(i),50,50,Qt::blue);
        painter.drawEllipse(stor->getX(i)+5,stor->getY(i)+5,40,40);
//        qDebug() << "fillRect " << s.getX(i) << " " << s.getY(i);
    }

    painter.setBrush(Qt::red);
    painter.setFont(QFont("Sans",50,5));
    painter.drawText(50,150,"touch me ॐ c1Audio");
    QString fpss;
    fpss.sprintf("%d fps",fps);
    painter.drawText(50,250,fpss);
    painter.drawText(50,350,QString(fpsT.toString()));

    fcnt++;
}

void View::resizeEvent(QResizeEvent *)
{
    qDebug() << "resize event";
    lmod->calcGeo(width(),height());
}

bool View::event(QEvent *event)
{
    QList<QTouchEvent::TouchPoint> touchPoints;
    QString sEvent;
    if( event->type()==QEvent::TouchEnd ||
        event->type()==QEvent::TouchUpdate ||
        event->type()==QEvent::TouchBegin ) {

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
            stor->put(touchPoint.pos().x(),touchPoint.pos().y());
            ehand->processPoint(touchPoint.id(),touchPoint.state(),touchPoint.pos().x(),touchPoint.pos().y());
        }
        return true;
    } else if(  !nomouse && (
                event->type()==QEvent::MouseMove ||
                event->type()==QEvent::MouseButtonPress ||
                event->type()==QEvent::MouseButtonRelease )) {

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
        stor->put(meve->pos().x(),meve->pos().y());
        ehand->processPoint(eventId,state,meve->pos().x(),meve->pos().y());
        return true;
    }
    return QWidget::event(event);
}
