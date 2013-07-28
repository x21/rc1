#ifndef VIEW_H
#define VIEW_H

#include <QGLWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QEvent>
#include <QTime>

#include "storage.h"
#include "event/ieventhandler.h"

class View : public QGLWidget
{
    Q_OBJECT

private:
    Storage * stor;
    LayoutModel * lmod;
    IEventHandler * ehand;

    // fps statistic
    int fps;
    int fcnt;
    QTime fpsT;

    // emulated touch point id for mouse events
    int eventId = 1;
    bool nomouse = false;

public:
    explicit View(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    bool event(QEvent *event);

signals:
    
public slots:
    
};

#endif // VIEW_H
