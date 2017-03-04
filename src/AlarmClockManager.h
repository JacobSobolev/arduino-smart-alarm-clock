#ifndef ALARM_CLOCK_MANAGER
#define ALARM_CLOCK_MANAGER

#include <Arduino.h>
#include <Wire.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time
#include <Menu.h>
#include <ButtonsManager.h>
#include <SoundManager.h>
#include <eButtonPressLength.h>
#include <LcdManager.h>
#include <Clock.h>
#include <eClockElementType.h>
#include <eTmElementType.h>
#include <LightManager.h>

class AlarmClockManager {
private:
  const int _menuSize;
  const int _timeToResetToDefualtMenu;
  const int _menuNumberIterations1;
  const int _menuNumberIterations2;
  const int _menuNumberIterations3;
  const int _menuNumberIterations4;
  const char* _menuName1;
  const char* _menuName2;
  const char* _menuName3;
  const char* _menuName4;


  int _timeFromLastInput;
  bool _insideMenu;
  int _insideMenuIndex;
  bool _alarmTriggered;
  bool _alarmSet;
  bool _alarmLightSet;


  Menu* _menu;
  ButtonsManager* _buttonsManager;
  SoundManager* _soundManager;
  LcdManager* _lcdManager;
  Clock* _clock;
  LightManager* _lightManager;

  void moveToNextIndexInsideMenu();
  void preformMenuAction();

public:
  AlarmClockManager();
  ~AlarmClockManager();
  void init();
  void printCurrentMenu();
  void handleButtonsInput();
  void playAlarm();
  void checkAlarm();
  void updateLightValue();
};

#endif
