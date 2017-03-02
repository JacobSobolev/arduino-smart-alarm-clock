#ifndef CLOCK
#define CLOCK

#include <Arduino.h>
#include <Time.h>
#include <DS3232RTC.h>
#include <eClockElementType.h>
#include <eTmElementType.h>

class Clock{
  private:
    tmElements_t _timeCurrent;
    tmElements_t _timeToSet;
    tmElements_t _timeToAlarm;

  public:
    Clock();
    ~Clock();
    void init();
    void setTimeElement(time_t time, eClockElementType elementClock);
    tmElements_t getTimeElement(eClockElementType elementClock);
    void dtCurrentTimeField(int dt, eClockElementType elementClock, eTmElementType elementTime);
};

#endif
