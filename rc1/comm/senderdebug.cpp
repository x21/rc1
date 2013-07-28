#include "senderdebug.h"

#include <QDebug>

SenderDebug::SenderDebug()
{
}

void SenderDebug::cc(int c, int voiceId, int cc, double v1)
{
    qDebug() << "SenderDebug::cc(" << c << "," << voiceId << "," << cc << "," << v1 << ")";
}

void SenderDebug::pc(int c, int v1)
{
    qDebug() << "SenderDebug::pc(" << c << "," << v1 << ")";
}

void SenderDebug::noteOn(int c, int voiceId, int v1, int v2)
{
    qDebug() << "SenderDebug::noteOn(" << c << "," << voiceId << "," << v1 << "," << v2 << ")";
}

void SenderDebug::noteOff(int c, int voiceId, int v1)
{
    qDebug() << "SenderDebug::noteOff(" << c << "," << voiceId << "," << v1 << ")";
}
