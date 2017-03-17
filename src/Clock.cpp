#include <Clock.h>

Clock::Clock(){

}

Clock::~Clock(){

}

void Clock::init(){
  setSyncProvider(RTC.get);
}

void Clock::setTimeElement(time_t time, eClockElementType elementClock)
{
  if (elementClock == eClockElementType::currentTime){
      breakTime(time, _timeCurrent);
  } else if (elementClock == eClockElementType::timeToSet)
  {
    breakTime(time, _timeToSet);
  } else if (elementClock == eClockElementType::timeToAlarm){
    breakTime(time, _timeToAlarm);
  }
}

tmElements_t Clock::getTimeElement(eClockElementType elementClock){
  tmElements_t tmToReturn;
  if (elementClock == eClockElementType::currentTime){
    tmToReturn = _timeCurrent;
  } else if (elementClock == eClockElementType::timeToSet)
  {
    tmToReturn = _timeToSet;
  } else if (elementClock == eClockElementType::timeToAlarm){
    tmToReturn = _timeToAlarm;
  }

  return tmToReturn;
}

void Clock::dtCurrentTimeField(int dt, eClockElementType elementClock, eTmElementType elementTime)
{
  tmElements_t tm;
  if (elementClock == eClockElementType::currentTime){
    tm = _timeCurrent;
  } else if (elementClock == eClockElementType::timeToSet)
  {
    tm = _timeToSet;
  } else if (elementClock == eClockElementType::timeToAlarm){
    tm = _timeToAlarm;
  }

  if (elementTime == eTmElementType::hours){
    tm.Hour += dt;
    if (tm.Hour  == 24){
      tm.Hour = 0;
    } else if (tm.Hour == 255){
      tm.Hour = 24;
    }
  }
  else if (elementTime == eTmElementType::minutes){
    tm.Minute += dt;
    if (tm.Minute == 60){
      tm.Minute = 0;
    } else if (tm.Minute == 255){
      tm.Minute = 59;
    }
  }
  else if (elementTime == eTmElementType::seconds){
    tm.Second += dt;
    if (tm.Second == 60){
      tm.Second = 0;
    } else if (tm.Second == 255){
      tm.Second = 59;
    }
  }
  else if (elementTime == eTmElementType::days){
    tm.Day += dt;
    if (tm.Month == 2){
      if (tm.Year % 4 == 0 ){
        if (tm.Day  == 30){
            tm.Day = 1;
        } else if (tm.Day == 0){
          tm.Day = 29;
        }
      }
      else {
        if (tm.Day  == 29){
          tm.Day = 1;
        } else if (tm.Day == 0){
          tm.Day = 28;
        }
      }
    }
    else if (((tm.Month == 4) || (tm.Month == 6) || (tm.Month == 9) || (tm.Month == 11))){
      if (tm.Day  == 31){
          tm.Day = 1;
      } else if (tm.Day == 0){
        tm.Day = 30;
      }

    } else {
      if ( tm.Day == 32){
          tm.Day = 1;
      } else if (tm.Day == 0){
        tm.Day = 31;
      }
    }
  }
  else if (elementTime == eTmElementType::months){
    tm.Month += dt;
    if (tm.Month == 13){
      tm.Month = 1;
    } else if (tm.Month == 0){
      tm.Month = 12;
    }
  }
  else if (elementTime == eTmElementType::years){
    tm.Year += dt;
  }

  if (elementClock == eClockElementType::currentTime){
    _timeCurrent = tm;
  } else if (elementClock == eClockElementType::timeToSet)
  {
    _timeToSet = tm;
  } else if (elementClock == eClockElementType::timeToAlarm){
     _timeToAlarm = tm;
  }
}

void Clock::setSystemRtcTime(){
  time_t t = makeTime(_timeToSet);
  setTime(t);
  RTC.set(t);
}
