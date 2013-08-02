#ifndef VIEW_H
#define VIEW_H

#include <QGLWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QEvent>
#include <QTime>

//#include "iview.h"
#include "storage.h"
#include "event/ieventhandler.h"

#include "paint/ipaint.h"

class IPaint;

class View : public QGLWidget
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);
    Storage *getStorage() const;
    LayoutModel *getLayout() const;
    long getNow();
    int getFps();
    QTime *getFpsT();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    bool event(QEvent *event);


private:
    Storage * storage;
    LayoutModel * layout;
    IEventHandler * ehand;
    IPaint ** painters;

    long now;

    // fps statistic
    int fps;
    int fcnt;
    QTime fpsT;

    // emulated touch point id for mouse events
    int eventId;
    bool nomouse;
    
};

#endif // VIEW_H
