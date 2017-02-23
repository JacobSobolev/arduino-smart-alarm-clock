#include "AlarmClockManager.h"


AlarmClockManager::AlarmClockManager()
: _lcdPinNumber1(7), _lcdPinNumber2(6), _lcdPinNumber3(5),
_lcdPinNumber4(4), _lcdPinNumber5(3), _lcdPinNumber6(2),
_lcdNumOfCols(16), _lcdNumOfRows(2), _menuSize(3), _timeToResetToDefualtMenu(50)

{
  _timeFromLastInput = 0;
  _insideMenu = 0;
  _insideMenuIndex = 0;

  _lcd = new LiquidCrystal(_lcdPinNumber1, _lcdPinNumber2, _lcdPinNumber3,
  _lcdPinNumber4, _lcdPinNumber5, _lcdPinNumber6);

  _menu = new Menu(_menuSize);
  _menu->addItemToMenu(0, "Menu 1");
  _menu->addItemToMenu(1, "Set Clock");
  _menu->addItemToMenu(2, "Set Alarm");

  _buttonsManager = new ButtonsManager();

  _soundManager = new SoundManager();
}

AlarmClockManager::~AlarmClockManager()
{
}

void AlarmClockManager::init()
{
  _lcd->begin(_lcdNumOfCols, _lcdNumOfRows);
  _buttonsManager->initAll();
  _soundManager->init();
  _rtc.start();
  // _rtc.set(0, 6, 9, 23, 2, 2017); //08:00:00 24.12.2014 //sec, min, hour, day, month, year
}

void AlarmClockManager::printCurrentMenu()
{

  if (_menu->getCurrentIndex() == 0){
    printRealTimeOnLcd();

  } else {
    if (_insideMenu){
        if (_menu->getCurrentIndex() == 1){
          printSetTimeOnLcd();
        }
        else if (_menu->getCurrentIndex() == 2){
          printSetAlarmOnLcd();
        }
    }
    else{
      _lcd->setCursor(0,0);
      const char* menuStr = _menu->getCurrentMenu()->getName();
      _lcd->print(menuStr);
    }
  }
}

void AlarmClockManager::handleButtonsInput()
{

  _buttonsManager->handleAll();
  if(_buttonsManager->getButtonLastEvent(0) == eButtonPressLength::pressShort){
    if (!_insideMenu){
      _menu->moveIndexUp();
      _timeFromLastInput = 0;

      _lcd->clear();
    }
    else
    {
      incCurrentTimeField();
      // if (_menu->getCurrentIndex() == 1)
      // {
      //
      // } else if (_menu->getCurrentIndex() == 2)
      // {
      //
      // }
    }
    // Serial.print(1);
  }
  else if (_buttonsManager->getButtonLastEvent(1)  == eButtonPressLength::pressShort){
    if (!_insideMenu)
    {
      _menu->moveIndexDown();
      _timeFromLastInput = 0;
      _lcd->clear();
    }
    else
    {
      decCurrentTimeField();
      // if (_menu->getCurrentIndex() == 1)
      // {
      //
      // } else if (_menu->getCurrentIndex() == 2)
      // {
      //
      // }
    }
    // Serial.print(2);
  }
  else if (_buttonsManager->getButtonLastEvent(2)  == eButtonPressLength::pressShort){
    //TODO : action
    // Serial.println("was pressed");
    // if (_soundManager->getPlayMusic()){
    //   _soundManager->setPlayMusic(false);
    // }
    // else{
    //   _soundManager->setPlayMusic(true);
    // }
    if (_menu->getCurrentIndex() == 1){
      if (!_insideMenu){
        _insideMenu = true;
        _insideMenuIndex = 0;
        _lcd->clear();
        _lcd->blink();
      }
      else {
        moveToNextIndexInsideMenu();
      }
    }
    else if (_menu->getCurrentIndex() == 2){
      if (!_insideMenu){
        _insideMenu = true;
        _insideMenuIndex = 0;
        _lcd->clear();
        _lcd->blink();
      }
      else {
        moveToNextIndexInsideMenu();
      }
    }

    // Serial.print(3);
  }
  else
  {
    // Serial.print(".");
    if (_timeFromLastInput >= _timeToResetToDefualtMenu && !_menu->isOnDefualtMenu() && !_insideMenu){
      _menu->resetToDefualtMenu();
      _lcd->clear();
    } else if (!_insideMenu){
      _timeFromLastInput ++;
    }
  }
}

void AlarmClockManager::printRealTimeOnLcd()
{
  uint8_t sec, min, hour, day, month;
  uint16_t year;
  _rtc.get(&sec, &min, &hour, &day, &month, &year);
  char* msg = new char[17];
  _lcd->setCursor(4,0);
  sprintf(msg,"%2d:%02d:%02d",hour,min,sec);
  _lcd->print(msg);
  _lcd->setCursor(3,1);
  sprintf(msg,"%2d/%02d/%02d",day,month,year);
  _lcd->print(msg);

  delete []msg;
}

void AlarmClockManager::printSetTimeOnLcd()
{
  uint8_t sec, min, hour, day, month;
  uint16_t year;
  _rtc.get(&sec, &min, &hour, &day, &month, &year);
  char* msg = new char[17];
  _lcd->setCursor(0,0);
  _lcd->print("Set");
  _lcd->setCursor(6,0);
  sprintf(msg,"%2d:%02d:%02d",hour,min,sec);
  _lcd->print(msg);
  _lcd->setCursor(0,1);
  _lcd->print("Clock");
  _lcd->setCursor(6,1);
  sprintf(msg,"%2d/%02d/%02d",day,month,year);
  _lcd->print(msg);
  setBlinkCursor();
  delete []msg;
}

void AlarmClockManager::printSetAlarmOnLcd()
{
  uint8_t sec, min, hour, day, month;
  uint16_t year;
  _rtc.get(&sec, &min, &hour, &day, &month, &year);
  char* msg = new char[17];
  _lcd->setCursor(0,0);
  _lcd->print("Set");
  _lcd->setCursor(6,0);
  sprintf(msg,"%2d:%02d:%02d",hour,min,sec);
  _lcd->print(msg);
  _lcd->setCursor(0,1);
  _lcd->print("Alarm");
  _lcd->setCursor(6,1);
  sprintf(msg,"%2d/%02d/%02d",day,month,year);
  _lcd->print(msg);
  setBlinkCursor();
  delete []msg;
}

void AlarmClockManager::moveToNextIndexInsideMenu()
{
  if(_insideMenuIndex < 5) {
    _insideMenuIndex++;
  }
  else
  {
    _insideMenu = false;
    _lcd->noBlink();
    _lcd->clear();
    _menu->resetToDefualtMenu();
  }
}

void AlarmClockManager::setBlinkCursor()
{
  if (_insideMenuIndex == 0){
    _lcd->setCursor(7,0);
  }
  else if (_insideMenuIndex == 1){
    _lcd->setCursor(10,0);
  }
  else if (_insideMenuIndex == 2){
    _lcd->setCursor(13,0);
  }
  else if (_insideMenuIndex == 3){
    _lcd->setCursor(7,1);
  }
  else if (_insideMenuIndex == 4){
    _lcd->setCursor(10,1);
  }
  else if (_insideMenuIndex == 5){
    _lcd->setCursor(15,1);
  }
}

void AlarmClockManager::setDataByMenu(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t month, uint16_t year)
{
    if (_menu->getCurrentIndex() == 1){
      _rtc.set(sec, min, hour, day, month, year);
    }
    else if (_menu->getCurrentIndex() == 2){

    }
}

void AlarmClockManager::incCurrentTimeField()
{
  uint8_t sec, min, hour, day, month;
  uint16_t year;
  _rtc.get(&sec, &min, &hour, &day, &month, &year);
  if (_insideMenuIndex == 0){
    hour++;
    if (hour == 24){
      hour = 0;
    }
  }
  else if (_insideMenuIndex == 1){
    min++;
    if (min == 60){
      min = 0;
    }
  }
  else if (_insideMenuIndex == 2){
    sec++;
    if (sec == 60){
      sec = 0;
    }
  }
  else if (_insideMenuIndex == 3){
    day++;
    if (month == 2){
      if (year % 4 == 0 && day == 30){
        day = 1;
      }
      else if (day == 29){
        day = 1;
      }

    }
    else if (((month == 4) || (month == 6) || (month == 9) || (month == 11)) && day == 31){
      day = 1;
    } else if (day == 32){
      day = 1;
    }
  }
  else if (_insideMenuIndex == 4){
    month++;
    if (month == 13){
      month = 1;
    }
  }
  else if (_insideMenuIndex == 5){
    year++;
  }

  setDataByMenu(sec, min, hour, day, month, year);

}

void AlarmClockManager::decCurrentTimeField()
{
  uint8_t sec, min, hour, day, month;
  uint16_t year;
  _rtc.get(&sec, &min, &hour, &day, &month, &year);
  if (_insideMenuIndex == 0){
    if (hour == 0){
      hour = 23;
    }
    else{
      hour--;
    }
  }
  else if (_insideMenuIndex == 1){
    if (min == 0){
      min = 59;
    }
    else{
      min--;
    }
  }
  else if (_insideMenuIndex == 2){
    if (sec == 0){
      sec = 59;
    }
    else{
      sec--;
    }
  }
  else if (_insideMenuIndex == 3){
    day--;
    if (month == 2 ){
      if (year % 4 == 0 && day == 0){
        day = 29;
      }
      else if (day == 0){
        day = 28;
      }
      else{

      }
    }
    else if (((month == 4) || (month == 6) || (month == 9) || (month == 11)) && day == 0){
      day = 30;
    } else if (day == 0){
      day = 31;
    }
  }
  else if (_insideMenuIndex == 4){
    month--;
    if (month == 0){
      month = 12;
    }
  }
  else if (_insideMenuIndex == 5){
    year--;
  }

  setDataByMenu(sec, min, hour, day, month, year);
}


void AlarmClockManager::playAlarm()
{
  _soundManager->playNext();
}
