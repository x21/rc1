#include "eventstat.h"

EventStat::EventStat()
{
    resetStat();
}

int EventStat::getOscnoteoffcount() const
{
    return oscnoteoffcount;
}

void EventStat::incOscnoteoffcount()
{
    oscnoteoffcount++;
}

int EventStat::getOscnoteoncount() const
{
    return oscnoteoncount;
}

void EventStat::incOscnoteoncount()
{
    oscnoteoncount++;
}

int EventStat::getOsccount() const
{
    return osccount;
}

void EventStat::incOsccount()
{
    osccount++;
}

int EventStat::getTransitioncount() const
{
    return transitioncount;
}

void EventStat::incTransitioncount()
{
    transitioncount++;
}

int EventStat::getTouchendcount() const
{
    return touchendcount;
}

void EventStat::incTouchendcount()
{
    touchendcount++;
}

int EventStat::getTouchmovecount() const
{
    return touchmovecount;
}

void EventStat::incTouchmovecount()
{
    touchmovecount++;
}

int EventStat::getTouchbegincount() const
{
    return touchsbegincount;
}

void EventStat::incTouchbegincount()
{
    touchsbegincount++;
}

int EventStat::getToucheventcount() const
{
    return toucheventcount;
}

void EventStat::incToucheventcount()
{
    toucheventcount++;
}

int EventStat::getAlreadyoncount() const
{
    return alreadyoncount;
}

void EventStat::incAlreadyoncount()
{
    alreadyoncount++;
}

void EventStat::resetStat()
{
    toucheventcount=0;
    touchsbegincount=0;
    touchmovecount=0;
    touchendcount=0;
    transitioncount=0;
    osccount=0;
    oscnoteoncount=0;
    oscnoteoffcount=0;
    alreadyoncount=0;
}
