#ifndef SENDEROSCPUREDATA_H
#define SENDEROSCPUREDATA_H

#include "rc1.h"
#include "isender.h"
#include "comm/libofqf/qoscclientinterface.h"

class SenderOscPuredata : public ISender
{
public:
    SenderOscPuredata(RC1 * rc1);
    virtual void cc(int c, int voiceId, int cc, double v1);
    virtual void pc(int c, int v1);
    virtual void note(int c, int voiceId, int f, int vel);
private:
    QOscClientInterface* oscout;
    RC1 * rc1;

    int prog;           // current program
    quint8 * notestate;      // currently played notes
    quint8 onNoteCnt;   // count of on Notes

    void sendOsc(QString path, QVariant list);

};

#endif // SENDEROSCPUREDATA_H
