#include <QDebug>
#include "eventhandlerrect.h"
#include "comm/senderdebug.h"
#include "comm/senderoscpuredata.h"

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

//void EventHandlerRect::processPoint(int p->getGid(), Qt::TouchPointState touchPointState, quint16 x1, quint16 y1)
void EventHandlerRect::processPoint(Point * p)
{
    // 1. figure out, at which index (evptr) the data for this touch point is stored
    qint16 evptr=p->getGid()%ntp;

    // qDebug() << "processPoint ptr " << evptr << " id " << p->getGid();
    if(p->getState()==Qt::TouchPointPressed) {
        if(act[evptr]!=true) {  // if needed, else ieventsub will be set to 0 by accitent -> hanging note
            act[evptr]=true;
            ievent[evptr]=p->getGid();
            ieventout[evptr]=ieventoutnext;
            ieventoutnext++;
        }
    }

    if( p->getState() == Qt::TouchPointPressed ||
        p->getState() == Qt::TouchPointMoved ) {

        double xnorm=p->getXn();
        double ynorm=p->getYn();

//        qDebug() << "pressed: x1:" << x1 << " y1:" << y1 << " xnorm: " << xnorm << " ynorm: " << ynorm;

        // 2.b. translate to MisuEvent index
        int iy=0;
        int ix=0;
        int iseg=0;
        int ysum=0;
        int xsum=0;
        while(p->getY()>ysum && iy<mod->getNrows()) {
            ysum+=mod->getRowheightpx(iy);
            iseg+=mod->getNseg(iy);
            iy++;
//            qDebug() << "loop1 iy:" << iy << " iseg:" << iseg << " ysum: " << ysum;
        }
        if(iy>0) {
            iy--;
            iseg-=mod->getNseg(iy);
            while(p->getX()>xsum && ix<mod->getNseg(iy)) {
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
                snd->note(chan[evptr],ieventout[evptr],note[evptr],0);
            }
            ieventout[evptr]=ieventoutnext;
            ieventoutnext++;
            snd->note(mod->getChan(iseg),ieventout[evptr], v1, veldef);
            note[evptr]=v1;
            chan[evptr]=mod->getChan(iseg);
        }

        if(mod->getCtlx(iseg)>0) {
            if(xnorm!=ccval1[evptr]) {
                ccval1[evptr]=xnorm;
                if(useCCCVal==true) {
                    cccval1=ccval1[evptr]/cccvalAvg+(cccvalAvg-1)*cccval1/cccvalAvg;
                    snd->cc(mod->getChan(iseg), ieventout[evptr], mod->getCtlx(iseg), cccval1);
                } else {
                    snd->cc(mod->getChan(iseg), ieventout[evptr], mod->getCtlx(iseg), xnorm);
                }
            }
        }
        if(mod->getCtly(iseg)>0) {
            if(ynorm!=ccval2[evptr]) {
                ccval2[evptr]=ynorm;
                if(useCCCVal==true) {
                    cccval2=ccval2[evptr]/cccvalAvg+(cccvalAvg-1)*cccval2/cccvalAvg;
                    snd->cc(mod->getChan(iseg), ieventout[evptr], mod->getCtly(iseg), cccval2);
                } else {
                    snd->cc(mod->getChan(iseg), ieventout[evptr], mod->getCtly(iseg), ynorm);
                }
            }
        }

    } else if( p->getState() == Qt::TouchPointReleased ) {
        act[evptr]=false;
        snd->note(chan[evptr],ieventout[evptr],note[evptr],0);
        note[evptr]=-1;
    }
}

void EventHandlerRect::init()
{
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
    chan=new int[ntp];

    for(int i=0;i<ntp;i++) {
        ievent[i]=-1;
        ieventout[i]=0;
        act[i]=false;
        note[i]=-1;
        chan[i]=-1;
        ccval1[i]=-1;
        ccval2[i]=-1;
    }
}
