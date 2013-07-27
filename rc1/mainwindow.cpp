#include "mainwindow.h"
#include <sys/time.h>
#include <QtGui>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{   
    view=new View();
    setCentralWidget(view);
    view->setVisible(true);
    startTimer(1000);
    view->show();
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    qDebug() << "MainWindow::Timer event";
    repaint();
}

bool MainWindow::event(QEvent *event)
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
            qDebug() << sEvent << ": x:" << touchPoint.pos().x() << " y:" << touchPoint.pos().y() << " t: " << t1.tv_sec << "." << t1.tv_usec;
        }
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
        qDebug() << sEvent << ": x:" << meve->pos().x() << " y:" << meve->pos().y() << " t: " << t1.tv_sec << "." << t1.tv_usec;
    }
}
