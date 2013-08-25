#include <QApplication>
#include "rc1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RC1 w;
    w.show();
    
    return a.exec();
}
