#include "AlarmClockManager.h"


AlarmClockManager::AlarmClockManager()
: _lcdPinNumber1(7), _lcdPinNumber2(6), _lcdPinNumber3(5),
_lcdPinNumber4(4), _lcdPinNumber5(3), _lcdPinNumber6(2),
_lcdNumOfCols(16), _lcdNumOfRows(2), _menuSize(3), _timeToResetToDefualtMenu(50),
_menuNumberIterations1(0), _menuNumberIterations2(6), _menuNumberIterations3(3),
_menuName1("Menu 1"), _menuName2("Set Time"), _menuName3("Set Alarm")

{
  _timeFromLastInput = 0;
  _insideMenu = false;
  _insideMenuIndex = 0;
  _alarmTriggered = false;
  _alarmSet = false;

  _lcd = new LiquidCrystal(_lcdPinNumber1, _lcdPinNumber2, _lcdPinNumber3,
  _lcdPinNumber4, _lcdPinNumber5, _lcdPinNumber6);

  _menu = new Menu(_menuSize);
  _menu->addItemToMenu(0, _menuName1, _menuNumberIterations1);
  _menu->addItemToMenu(1, _menuName2, _menuNumberIterations2);
  _menu->addItemToMenu(2, _menuName3, _menuNumberIterations3);

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
  // setTime(14, 34, 0, 23, 2, 2017);
  // RTC.set(now());
  // _rtc.start();
  setSyncProvider(RTC.get);
  // RTC.alarmInterrupt(13, true);
  // RTC.setAlarm(ALM1_MATCH_DATE, 0, 1, 1);
  // if(timeStatus() != timeSet)
  // {
  //   Serial.println("Unable to sync with the RTC");
  //
  //
  // }
  // else
  // {
  //   Serial.println("RTC has set the system time");
  // }

  byte bellChar[8] = {
    0b00100,
    0b01010,
    0b01010,
    0b01010,
    0b01010,
    0b11111,
    0b00000,
    0b00100
  };
  byte rightSignChar[8] = {
  	0b10000,
  	0b11000,
  	0b11100,
  	0b11110,
  	0b11110,
  	0b11100,
  	0b11000,
  	0b10000
  };

  byte leftSignChar[8] = {
  	0b00001,
  	0b00011,
  	0b00111,
  	0b01111,
  	0b01111,
  	0b00111,
  	0b00011,
  	0b00001
  };
  _lcd->createChar(0, bellChar);
  _lcd->createChar(1, rightSignChar);
  _lcd->createChar(2, leftSignChar);


}

void AlarmClockManager::printCurrentMenu()
{

  if (!_alarmTriggered){
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
        _lcd->setCursor(6,0);
        _lcd->print("MENU");
        const char* menuStr = _menu->getCurrentMenu()->getName();
        _lcd->setCursor(4,1);
        _lcd->print(menuStr);
        _lcd->setCursor(15,1);
       _lcd->write(byte(1));
       _lcd->setCursor(0,1);
       _lcd->write(byte(2));
      }
    }
  }
  else
  {
    printAlarmTriggeredOnLcd();
  }

}

void AlarmClockManager::handleButtonsInput()
{

  _buttonsManager->handleAll();
  if(!_alarmTriggered){
    if(_buttonsManager->getButtonLastEvent(0) == eButtonPressLength::pressShort){
      if (!_insideMenu){
        _menu->moveIndexUp();
        _timeFromLastInput = 0;

        _lcd->clear();
      }
      else
      {
        if (_menu->getCurrentIndex() == 1)
        {
          incCurrentTimeField(_timeToSet);
        } else if (_menu->getCurrentIndex() == 2)
        {
          incCurrentTimeField(_timeToAlarm);
        }
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
        if (_menu->getCurrentIndex() == 1)
        {
          decCurrentTimeField(_timeToSet);
        } else if (_menu->getCurrentIndex() == 2)
        {
          decCurrentTimeField(_timeToAlarm);
        }
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
          breakTime(now(), _timeToSet);
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
          breakTime(now(), _timeToAlarm);
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
  else
  {
    if(_buttonsManager->getButtonLastEvent(0) == eButtonPressLength::pressShort ||
      _buttonsManager->getButtonLastEvent(1) == eButtonPressLength::pressShort ||
      _buttonsManager->getButtonLastEvent(2) == eButtonPressLength::pressShort){
      _lcd->clear();
      _alarmTriggered = false;
      _soundManager->setPlayMusic(false);
    }
  }

}

void AlarmClockManager::printRealTimeOnLcd()
{
  // Serial.println(timeStatus());
  if(timeStatus() == timeSet) {
    if (_alarmSet){

      _lcd->setCursor(0,0);
      _lcd->write(byte(0));
    }
    breakTime(now(),_timeCurrent);
    char* msg = new char[17];
    _lcd->setCursor(4,0);
    sprintf(msg,"%2d:%02d:%02d",_timeCurrent.Hour,_timeCurrent.Minute,_timeCurrent.Second);
    _lcd->print(msg);
    _lcd->setCursor(3,1);
    sprintf(msg,"%2d/%02d/%02d",_timeCurrent.Day,_timeCurrent.Month,_timeCurrent.Year + 1970);
    _lcd->print(msg);

    delete []msg;
  }


}

void AlarmClockManager::printSetTimeOnLcd()
{
  if(timeStatus() == timeSet) {

    char* msg = new char[17];
    _lcd->setCursor(0,0);
    _lcd->print("Set");
    _lcd->setCursor(6,0);
    sprintf(msg,"%2d:%02d:%02d",_timeToSet.Hour,_timeToSet.Minute,_timeToSet.Second);
    _lcd->print(msg);
    _lcd->setCursor(0,1);
    _lcd->print("Time");
    _lcd->setCursor(6,1);
    sprintf(msg,"%2d/%02d/%02d",_timeToSet.Day,_timeToSet.Month,_timeToSet.Year + 1970);
    _lcd->print(msg);
    setBlinkCursor();
    delete []msg;
  }
}

void AlarmClockManager::printSetAlarmOnLcd()
{

  if(timeStatus() == timeSet) {
    char* msg = new char[17];
    _lcd->setCursor(0,0);
    _lcd->print("Set");
    _lcd->setCursor(6,0);
    sprintf(msg,"%2d:%02d:%02d",_timeToAlarm.Hour,_timeToAlarm.Minute,_timeToAlarm.Second);
    _lcd->print(msg);
    _lcd->setCursor(0,1);
    _lcd->print("Alarm");
    setBlinkCursor();
    delete []msg;
  }
}

void AlarmClockManager::moveToNextIndexInsideMenu()
{
  if(_insideMenuIndex < _menu->getCurrentMenuIterations() - 1) {
    _insideMenuIndex++;
  }
  else
  {
    preformMenuAction();
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

void AlarmClockManager::preformMenuAction()
{
    if (_menu->getCurrentIndex() == 1){
      time_t t = makeTime(_timeToSet);
      setTime(t);
      RTC.set(t);
    }
    else if (_menu->getCurrentIndex() == 2){
      _alarmSet = true;
      // Serial.println("alarm set");
      Serial.println(_timeToAlarm.Hour);
      Serial.println(_timeToAlarm.Minute);
      Serial.println(_timeToAlarm.Second);
    }
}

void AlarmClockManager::incCurrentTimeField(tmElements_t &tm)
{
  if (_insideMenuIndex == 0){
    tm.Hour ++;
    if (tm.Hour  == 24){
      tm.Hour = 0;
    }
  }
  else if (_insideMenuIndex == 1){
    tm.Minute ++;
    if (tm.Minute == 60){
      tm.Minute = 0;
    }
  }
  else if (_insideMenuIndex == 2){
    tm.Second ++;
    if (tm.Second == 60){
      tm.Second = 0;
    }
  }
  else if (_insideMenuIndex == 3){
    tm.Day ++;
    if (tm.Month == 2){
      if (tm.Year % 4 == 0 && tm.Day  == 30){
        tm.Day = 1;
      }
      else if (tm.Day  == 29){
        tm.Day = 1;
      }
    }
    else if (((tm.Month == 4) || (tm.Month == 6) || (tm.Month == 9) || (tm.Month == 11))
    && tm.Day  == 31){
      tm.Day = 1;
    } else if ( tm.Day == 32){
      tm.Day = 1;
    }
  }
  else if (_insideMenuIndex == 4){
    tm.Month ++;
    // month++;
    if (tm.Month == 13){
      tm.Month = 1;
    }
  }
  else if (_insideMenuIndex == 5){
    tm.Year ++;
    // year++;
  }
  //
  // setDataByMenu();

}

void AlarmClockManager::decCurrentTimeField(tmElements_t &tm)
{

  if (_insideMenuIndex == 0){
    if (tm.Hour  == 0){
      tm.Hour = 23;
    }
    else
    {
      tm.Hour --;
    }
  }
  else if (_insideMenuIndex == 1){

    if (tm.Minute == 0){
      tm.Minute = 59;
    }
    else
    {
      tm.Minute --;
    }
  }
  else if (_insideMenuIndex == 2){

    if (tm.Second == 0){
      tm.Second = 59;
    }
    else
    {
      tm.Second --;
    }
  }
  else if (_insideMenuIndex == 3){
    if (tm.Month == 2){
      if (tm.Year % 4 == 0 && tm.Day == 1){
        tm.Day = 29;
      }
      else if (tm.Day  == 1){
        tm.Day = 28;
      }
      else{
        tm.Day --;
      }
    }
    else if (((tm.Month == 4) || (tm.Month == 6) || (tm.Month == 9) || (tm.Month == 11))
    && tm.Day  == 1){
      tm.Day = 30;
    } else if ( tm.Day == 1){
      tm.Day = 31;
    }
    else{
      tm.Day --;
    }
  }
  else if (_insideMenuIndex == 4){
    if (tm.Month == 1){
      tm.Month = 12;
    }
    else
    {
      tm.Month --;
    }
  }
  else if (_insideMenuIndex == 5){
    tm.Year--;
  }

  // setDataByMenu();
}


void AlarmClockManager::playAlarm()
{
  _soundManager->playNext();
}

void AlarmClockManager::checkAlarm()
{
  if ( _alarmSet && !_alarmTriggered ) {     //has Alarm1 triggered?
    //yes, act on the alarm
    // Serial.print("checking alarm");
    if (_timeCurrent.Hour == _timeToAlarm.Hour &&
      _timeCurrent.Minute == _timeToAlarm.Minute &&
      _timeCurrent.Second >= _timeToAlarm.Second)
    {
      _lcd->clear();
      _soundManager->setPlayMusic(true);
      _alarmTriggered = true;
      _alarmSet = false;
      Serial.println("alarm");

    }
  }
  else {
      //no alarm
      // Serial.println(".");
  }
}

void AlarmClockManager::printAlarmTriggeredOnLcd()
{
  _lcd->setCursor(6,0);
  _lcd->print("Alarm");
  _lcd->setCursor(5,1);
  _lcd->print("Wake Up");
}
