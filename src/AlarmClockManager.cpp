#include "AlarmClockManager.h"


AlarmClockManager::AlarmClockManager()
: _menuSize(3), _timeToResetToDefualtMenu(50),
_menuNumberIterations1(0), _menuNumberIterations2(6), _menuNumberIterations3(3),
_menuName1("Menu 1"), _menuName2("Set Time"), _menuName3("Set Alarm")

{
  _timeFromLastInput = 0;
  _insideMenu = false;
  _insideMenuIndex = 0;
  _alarmTriggered = false;
  _alarmSet = false;

  _lcdManager = new LcdManager();

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
  _buttonsManager->initAll();
  _soundManager->init();
  _lcdManager->init();
  setSyncProvider(RTC.get);

}

void AlarmClockManager::printCurrentMenu()
{

  if (!_alarmTriggered){
    if (_menu->getCurrentIndex() == 0){
      if(timeStatus() == timeSet) {
        breakTime(now(),_timeCurrent);
        _lcdManager->printRealTimeOnLcd(_timeCurrent,_alarmSet);
      }
    } else {
      if (_insideMenu){
          if (_menu->getCurrentIndex() == 1){
            // printSetTimeOnLcd();
            if(timeStatus() == timeSet) {
              _lcdManager->printInsideMenuWithClock(_timeToSet,"Set","Time", _insideMenuIndex);
            }
          }
          else if (_menu->getCurrentIndex() == 2){
            if(timeStatus() == timeSet) {
              _lcdManager->printInsideMenuWithClock(_timeToAlarm,"Set","Alarm",  _insideMenuIndex);
            }
          }
      }
      else{
        const char* menuStr = _menu->getCurrentMenu()->getName();
        _lcdManager->printMenuTextOnLcd(menuStr);
      }
    }
  }
  else
  {
    _lcdManager->printAlarmTriggeredOnLcd();
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

        _lcdManager->clearLcd();
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
    }
    else if (_buttonsManager->getButtonLastEvent(1)  == eButtonPressLength::pressShort){
      if (!_insideMenu)
      {
        _menu->moveIndexDown();
        _timeFromLastInput = 0;
        _lcdManager->clearLcd();
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
    }
    else if (_buttonsManager->getButtonLastEvent(2)  == eButtonPressLength::pressShort){
      if (_menu->getCurrentIndex() == 1){
        if (!_insideMenu){
          _insideMenu = true;
          _insideMenuIndex = 0;
          breakTime(now(), _timeToSet);
          _lcdManager->clearLcd();
          _lcdManager->setBlink(true);
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
          _lcdManager->clearLcd();
          _lcdManager->setBlink(true);
        }
        else {
          moveToNextIndexInsideMenu();
        }
      }
    }
    else
    {
      if (_timeFromLastInput >= _timeToResetToDefualtMenu && !_menu->isOnDefualtMenu() && !_insideMenu){
        _menu->resetToDefualtMenu();
        _lcdManager->clearLcd();
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
      _lcdManager->clearLcd();
      _alarmTriggered = false;
      _soundManager->setPlayMusic(false);
    }
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
    _lcdManager->setBlink(false);
    _lcdManager->clearLcd();
    _menu->resetToDefualtMenu();

  }
}


void AlarmClockManager::preformMenuAction()
{
    if (_menu->getCurrentIndex() == 1){
      time_t t = makeTime(_timeToSet);
      setTime(t);
      RTC.set(t);
      _alarmSet = false;
    }
    else if (_menu->getCurrentIndex() == 2){
      _alarmSet = true;
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
    if (tm.Month == 13){
      tm.Month = 1;
    }
  }
  else if (_insideMenuIndex == 5){
    tm.Year ++;
  }
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
}


void AlarmClockManager::playAlarm()
{
  _soundManager->playNext();
}

void AlarmClockManager::checkAlarm()
{
  if ( _alarmSet && !_alarmTriggered ) {
    if (_timeCurrent.Hour == _timeToAlarm.Hour &&
      _timeCurrent.Minute == _timeToAlarm.Minute &&
      _timeCurrent.Second >= _timeToAlarm.Second)
    {
      _lcdManager->clearLcd();
      _soundManager->setPlayMusic(true);
      _alarmTriggered = true;
      _alarmSet = false;
    }
  }
}
