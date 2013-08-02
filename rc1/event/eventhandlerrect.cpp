#include <QDebug>
#include "eventhandlerrect.h"
#include "comm/senderdebug.h"

EventHandlerRect::EventHandlerRect()
{
    mod=new LayoutModel();
    snd=new SenderDebug();
    init();
}

EventHandlerRect::EventHandlerRect(LayoutModel *mod, ISender *snd)
{
    this->mod=mod;
    this->snd=snd;
    init();
}

void EventHandlerRect::processPoint(int touchPointId, Qt::TouchPointState touchPointState, quint16 x1, quint16 y1)
{
    // 1. figure out, at which index (evptr) the data for this touch point is stored
    qint16 evptr=touchPointId%ntp;

    // qDebug() << "processPoint ptr " << evptr << " id " << touchPointId;
    if(touchPointState==Qt::TouchPointPressed) {
        if(act[evptr]!=true) {  // if needed, else ieventsub will be set to 0 by accitent -> hanging note
            act[evptr]=true;
            ievent[evptr]=touchPointId;
            ieventout[evptr]=ieventoutnext;
            ieventoutnext++;
        }
    }

    if( touchPointState == Qt::TouchPointPressed ||
        touchPointState == Qt::TouchPointMoved ) {

        double xnorm=x1/mod->getWidth();
        double ynorm=y1/mod->getHeight();

//        qDebug() << "pressed: x1:" << x1 << " y1:" << y1 << " xnorm: " << xnorm << " ynorm: " << ynorm;

        // 2.b. translate to MisuEvent index
        int iy=0;
        int ix=0;
        int iseg=0;
        int ysum=0;
        int xsum=0;
        while(y1>ysum && iy<mod->getNrows()) {
            ysum+=mod->getRowheightpx(iy);
            iseg+=mod->getNseg(iy);
            iy++;
//            qDebug() << "loop1 iy:" << iy << " iseg:" << iseg << " ysum: " << ysum;
        }
        if(iy>0) {
            iy--;
            iseg-=mod->getNseg(iy);
            while(x1>xsum && ix<mod->getNseg(iy)) {
                xsum+=mod->getSegwidthpx(iseg);
                iseg++; ix++;
//                qDebug() << "loop2 iseg:" << iseg << " xsum: " << xsum;
            }
            if(iseg>0) {
                iseg--;
            }
        }

        int v1=mod->getNote(iseg);

        if(note[evptr]!=v1) {
            if(note[evptr]>0) {
                snd->noteOff(chan,ieventout[evptr],note[evptr]);
            }
            ieventout[evptr]=ieventoutnext;
            ieventoutnext++;
            snd->noteOn(chan,ieventout[evptr], v1, veldef);
            note[evptr]=v1;
        }

        if(mod->getCtlx(iseg)>0) {
            if(xnorm!=ccval1[evptr]) {
                ccval1[evptr]=xnorm;
                if(useCCCVal==true) {
                    cccval1=ccval1[evptr]/cccvalAvg+(cccvalAvg-1)*cccval1/cccvalAvg;
                    snd->cc(chan, ieventout[evptr], mod->getCtlx(iseg), cccval1);
                } else {
                    snd->cc(chan, ieventout[evptr], mod->getCtlx(iseg), xnorm);
                }
            }
        }
        if(mod->getCtly(iseg)>0) {
            if(ynorm!=ccval2[evptr]) {
                ccval2[evptr]=ynorm;
                if(useCCCVal==true) {
                    cccval2=ccval2[evptr]/cccvalAvg+(cccvalAvg-1)*cccval2/cccvalAvg;
                    snd->cc(chan, ieventout[evptr], mod->getCtly(iseg), cccval2);
                } else {
                    snd->cc(chan, ieventout[evptr], mod->getCtly(iseg), ynorm);
                }
            }
        }

    } else if( touchPointState == Qt::TouchPointReleased ) {
        act[evptr]=false;
        snd->noteOff(chan,ieventout[evptr],note[evptr]);
        note[evptr]=-1;
    }
}

void EventHandlerRect::init()
{
    chan = 1;
    veldef = 127;

    ieventoutnext=1;

    useCCCVal=true;
    cccvalAvg=10;
    cccval1=0;
    cccval2=0;

    ntp=32;

    act=new bool[ntp];
    ievent=new int[ntp];
    ieventout=new int[ntp];
    ccval1=new double[ntp];
    ccval2=new double[ntp];
    note=new int[ntp];

    for(int i=0;i<ntp;i++) {
        ievent[i]=-1;
        ieventout[i]=0;
        act[i]=false;
        note[i]=-1;
        ccval1[i]=-1;
        ccval2[i]=-1;
    }
}
