#include <QDebug>
#include <sys/time.h>
#include "view.h"
#include <QtWidgets>
#include <QTimer>

View::View(QWidget *parent) :
    QGLWidget(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents,true);
//    qDebug() << "View()";
    s=new Storage();

    QTimer *timer = new QTimer(this);
//! [4] //! [5]
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//! [5] //! [6]
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

    painter.fillRect(0,0,width,height,Qt::red);
    painter.fillRect(20,20,width-40,height-40,Qt::black);
    painter.fillRect(40,40,width-80,height-80,Qt::green);

    painter.setBrush(Qt::green);
    for(int i=0; i<s->getLen();i++) {
        painter.fillRect(s->getX(i),s->getY(i),50,50,Qt::blue);
        painter.drawEllipse(s->getX(i)+5,s->getY(i)+5,40,40);
//        qDebug() << "fillRect " << s->getX(i) << " " << s->getY(i);
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

void View::resizeEvent(QResizeEvent *event)
{
    width=event->size().width();
    height=event->size().height();
}

bool View::event(QEvent *event)
{
    QList<QTouchEvent::TouchPoint> touchPoints;
    timeval t1;
    QString sEvent;
    if( event->type()==QEvent::TouchEnd ||
        event->type()==QEvent::TouchUpdate ||
        event->type()==QEvent::TouchBegin ) {

        gettimeofday(&t1, NULL);
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
            s->put(touchPoint.pos().x(),touchPoint.pos().y());
        }
        return true;
    } else if(  event->type()==QEvent::MouseMove ||
                event->type()==QEvent::MouseButtonPress ||
                event->type()==QEvent::MouseButtonRelease ) {

        gettimeofday(&t1, NULL);
        const QMouseEvent * meve = static_cast<QMouseEvent *>(event);
        if(event->type()==QEvent::MouseMove) {
            sEvent="MouseMove";
        } else if(event->type()==QEvent::MouseButtonPress) {
            sEvent="MouseButtonPress";
        } else if(event->type()==QEvent::MouseButtonRelease) {
            sEvent="MouseButtonRelease";
        }
//        qDebug() << sEvent << ": x:" << meve->pos().x() << " y:" << meve->pos().y() << " t: " << t1.tv_sec << "." << t1.tv_usec;
        s->put(meve->pos().x(),meve->pos().y());
        return true;
    }
    return QWidget::event(event);
}
