#ifndef EVENTHANDLERRECT_H
#define EVENTHANDLERRECT_H

#include "ieventhandler.h"

class EventHandlerRect : public IEventHandler
{
public:
    EventHandlerRect();
    EventHandlerRect(LayoutModel * mod, ISender * snd);
    void processPoint(int touchPointId, Qt::TouchPointState touchPointState, quint16 touchPointPosX, quint16 touchPointPosY);

private:
    LayoutModel * mod;
    ISender * snd;

    int ntp;   // number of simultanously possible touchpoints

    bool * act;         // is touched?
    int * ievent;       // current event Index
    int * ieventout;    // event id sent (one input event can lead in several output events)
    int ieventoutnext;  // id of next output event

    int * note;   // current note

    double * ccval1;  // current controller1 value: xrel
    double * ccval2;  // current controller1 value: yrel

    double cccval1;   // common cc value, average of individual ccvals
    double cccval2;   // common cc value, average of individual ccvals
    bool useCCCVal;
    int cccvalAvg;    // number of individual ccvals for average calc

    int chan = 1;       // transmit channel
    int veldef = 127;   // default velovity

    void init();
};

#endif // EVENTHANDLERRECT_H
