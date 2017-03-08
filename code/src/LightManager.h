#ifndef LIGHT_MANAGER
#define LIGHT_MANAGER

#include <Arduino.h>

class LightManager {
  private:
    const int _pinNumber;
    int _currentValue;
    int _alarmValue;

  public:
    LightManager();
    ~LightManager();
    void init();
    void updateLightValue();
    int getCurrentValue();
    void setAlarmValue(int value);
    int getAlarmValue();
    void addToAlarmValue(int valueToAdd);
    bool isAlarmValuePassed();

};

#endif
