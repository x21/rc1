#ifndef VIEW_H
#define VIEW_H

#include <QGLWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QEvent>
#include <QTime>

#include <storage.h>

class View : public QGLWidget
{
    Q_OBJECT

private:
    int width;
    int height;

    Storage * s;

    // fps statistic
    int fps;
    int fcnt;
    QTime fpsT;

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
