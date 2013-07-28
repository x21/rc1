#ifndef SENDERDEBUG_H
#define SENDERDEBUG_H

#include "isender.h"

class SenderDebug : public ISender
{
public:
    SenderDebug();
    virtual void cc(int c, int voiceId, int cc, double v1);
    virtual void pc(int c, int v1);
    virtual void noteOn(int c, int voiceId, int v1, int v2);
    virtual void noteOff(int c, int voiceId, int v1);
};

#endif // SENDERDEBUG_H
