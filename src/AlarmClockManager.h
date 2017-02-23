#ifndef ALARM_CLOCK_MANAGER
#define ALARM_CLOCK_MANAGER

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time
#include <Menu.h>
#include <ButtonsManager.h>
#include <SoundManager.h>
#include <eButtonPressLength.h>

class AlarmClockManager {
private:
  const uint8_t _lcdPinNumber1;
  const uint8_t _lcdPinNumber2;
  const uint8_t _lcdPinNumber3;
  const uint8_t _lcdPinNumber4;
  const uint8_t _lcdPinNumber5;
  const uint8_t _lcdPinNumber6;
  const uint8_t _lcdNumOfCols;
  const uint8_t _lcdNumOfRows;
  const int _menuSize;
  const int _timeToResetToDefualtMenu;
  const int _menuNumberIterations1;
  const int _menuNumberIterations2;
  const int _menuNumberIterations3;
  const char* _menuName1;
  const char* _menuName2;
  const char* _menuName3;


  int _timeFromLastInput;
  boolean _insideMenu;
  int _insideMenuIndex;
  boolean _alarmTriggered;
  boolean _alarmSet;

  LiquidCrystal* _lcd;
  Menu* _menu;
  ButtonsManager* _buttonsManager;
  SoundManager* _soundManager;
  tmElements_t _timeToSet;
  tmElements_t _timeCurrent;
  tmElements_t _timeToAlarm;

  void printRealTimeOnLcd();
  void printSetTimeOnLcd();
  void printSetAlarmOnLcd();
  void moveToNextIndexInsideMenu();
  void setBlinkCursor();
  void preformMenuAction();
  void decCurrentTimeField(tmElements_t &tm);
  void incCurrentTimeField(tmElements_t &tm);
  void printAlarmTriggeredOnLcd();

public:
  AlarmClockManager();
  ~AlarmClockManager();
  void init();
  void printCurrentMenu();
  void handleButtonsInput();
  void playAlarm();
  void checkAlarm();

};

#endif
