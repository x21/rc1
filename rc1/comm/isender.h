#ifndef ISENDER_H
#define ISENDER_H

class ISender
{
public:
    virtual ~ISender() {}
    virtual void cc(int c, int voiceId, int cc, double v1)=0;
    virtual void pc(int c, int v1)=0;
    virtual void noteOn(int c, int voiceId, int v1, int v2)=0;
    virtual void noteOff(int c, int voiceId, int v1)=0;
};

#endif // ISENDER_H
