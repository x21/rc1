#ifndef EVENTSTAT_H
#define EVENTSTAT_H

class EventStat
{
public:
    EventStat();
    void resetStat();

    int getToucheventcount() const;
    void incToucheventcount();

    int getTouchstartcount() const;
    void incTouchstartcount();

    int getTouchmovecount() const;
    void incTouchmovecount();

    int getTouchendcount() const;
    void incTouchendcount();

    int getTransitioncount() const;
    void incTransitioncount();

    int getOsccount() const;
    void incOsccount();

    int getOscnoteoncount() const;
    void incOscnoteoncount();

    int getOscnoteoffcount() const;
    void incOscnoteoffcount();

    int getAlreadyoncount() const;
    void incAlreadyoncount();

private:
    int toucheventcount;
    int touchstartcount;
    int touchmovecount;
    int touchendcount;
    int osccount;
    int oscnoteoncount;
    int oscnoteoffcount;

    int transitioncount;
    int alreadyoncount;
};

#endif // EVENTSTAT_H
