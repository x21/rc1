#ifndef SENDERDEBUG_H
#define SENDERDEBUG_H

#include "isender.h"

class SenderDebug : public ISender
{
public:
    SenderDebug();
    virtual void cc(int c, int voiceId, int cc, double v1);
    virtual void pc(int c, int v1);
    virtual void note(int c, int voiceId, int f, int v);
};

#endif // SENDERDEBUG_H
