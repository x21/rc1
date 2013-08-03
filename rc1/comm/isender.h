#ifndef ISENDER_H
#define ISENDER_H

class ISender
{
public:
    virtual ~ISender() {}
    virtual void cc(int c, int voiceId, int cc, double v1)=0;
    virtual void pc(int c, int v1)=0;
    virtual void note(int c, int voiceId, int f, int v)=0;
};

#endif // ISENDER_H
