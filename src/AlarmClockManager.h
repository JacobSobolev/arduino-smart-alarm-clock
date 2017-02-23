#ifndef ALARM_CLOCK_MANAGER
#define ALARM_CLOCK_MANAGER

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <DS1307.h>
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

  int _timeFromLastInput;
  boolean _insideMenu;
  int _insideMenuIndex;

  LiquidCrystal* _lcd;
  Menu* _menu;
  ButtonsManager* _buttonsManager;
  DS1307 _rtc;
  SoundManager* _soundManager;

  void printRealTimeOnLcd();
  void printSetTimeOnLcd();
  void printSetAlarmOnLcd();
  void moveToNextIndexInsideMenu();
  void setBlinkCursor();
  void setDataByMenu(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t month, uint16_t year);
  void decCurrentTimeField();
  void incCurrentTimeField();

public:
  AlarmClockManager();
  ~AlarmClockManager();
  void init();
  void printCurrentMenu();
  void handleButtonsInput();
  void playAlarm();

};

#endif
