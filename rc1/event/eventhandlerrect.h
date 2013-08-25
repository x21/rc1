#ifndef EVENTHANDLERRECT_H
#define EVENTHANDLERRECT_H

#include "ieventhandler.h"

class EventHandlerRect : public IEventHandler
{
public:
    EventHandlerRect();
    void processPoint(Point * p, RC1 * view);

private:
    int ntp;            // number of simultanously possible touchpoints

    bool * act;         // is touched?
    int * ievent;       // current event Index
    int * ieventout;    // event id sent (one input event can lead in several output events)
    int ieventoutnext;  // id of next output event

    int * note;         // current note
    int * chan;         // current note channel

    double * ccval1;    // current controller1 value: xrel
    double * ccval2;    // current controller1 value: yrel

    double cccval1;     // common cc value, average of individual ccvals
    double cccval2;     // common cc value, average of individual ccvals
    bool useCCCVal;
    int cccvalAvg;      // number of individual ccvals for average calc

    int veldef;         // default velovity

    void init();
};

#endif // EVENTHANDLERRECT_H
