#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>

#include <view.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    View * view;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent *event);
    bool event(QEvent *event);
};

#endif // MAINWINDOW_H
