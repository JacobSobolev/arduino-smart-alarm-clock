#include "AlarmClockManager.h"


AlarmClockManager::AlarmClockManager()
: _menuSize(4), _timeToResetToDefualtMenu(50),
_menuNumberIterations1(0), _menuNumberIterations2(6), _menuNumberIterations3(3), _menuNumberIterations4(1),
_menuName1("Menu 1"), _menuName2("Set Time"), _menuName3("Set Alarm"),_menuName4("Set Light")
{
  _timeFromLastInput = 0;
  _insideMenu = false;
  _insideMenuIndex = 0;
  _alarmTriggered = false;
  _alarmSet = false;
  _alarmLightSet = false;

  _menu = new Menu(_menuSize);
  _menu->addItemToMenu(0, _menuName1, _menuNumberIterations1);
  _menu->addItemToMenu(1, _menuName2, _menuNumberIterations2);
  _menu->addItemToMenu(2, _menuName3, _menuNumberIterations3);
  _menu->addItemToMenu(3, _menuName4, _menuNumberIterations4);


  _lcdManager = new LcdManager();
  _buttonsManager = new ButtonsManager();
  _soundManager = new SoundManager();
  _clock = new Clock();
  _lightManager = new LightManager();
}

AlarmClockManager::~AlarmClockManager()
{
}

void AlarmClockManager::init()
{
  _buttonsManager->initAll();
  _soundManager->init();
  _lcdManager->init();
  _clock->init();
  _lightManager->init();
}

void AlarmClockManager::printCurrentMenu()
{

  if (!_alarmTriggered ){
    if (_menu->getCurrentIndex() == 0){
      if(timeStatus() == timeSet) {
        _clock->setTimeElement(now(), eClockElementType::currentTime);
        tmElements_t tm = _clock->getTimeElement(eClockElementType::currentTime);
        _lcdManager->printRealTimeOnLcd(tm, _alarmSet, _alarmLightSet);
      }
    } else {
      if (_insideMenu){
          if (_menu->getCurrentIndex() == 1){
            // printSetTimeOnLcd();
            if(timeStatus() == timeSet) {
              tmElements_t tm = _clock->getTimeElement(eClockElementType::timeToSet);
              _lcdManager->printInsideMenuWithClock(tm,"Set","Time", _insideMenuIndex);
            }
          }
          else if (_menu->getCurrentIndex() == 2){
            if(timeStatus() == timeSet) {
              tmElements_t tm = _clock->getTimeElement(eClockElementType::timeToAlarm);
              _lcdManager->printInsideMenuWithClock(tm, "Set","Alarm",  _insideMenuIndex);
            }
          }
          else if (_menu->getCurrentIndex() == 3){
            _lcdManager->printInsideMenuLight(_lightManager->getCurrentValue(),_lightManager->getAlarmValue(),_insideMenuIndex);
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
          _clock->dtCurrentTimeField(1, eClockElementType::timeToSet, _lcdManager->getTmElementByIndex(_insideMenuIndex));
        } else if (_menu->getCurrentIndex() == 2)
        {
          _clock->dtCurrentTimeField(1, eClockElementType::timeToAlarm, _lcdManager->getTmElementByIndex(_insideMenuIndex));
        }
        else if (_menu->getCurrentIndex() == 3)
        {
          _lightManager->addToAlarmValue(10);
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
          _clock->dtCurrentTimeField(-1, eClockElementType::timeToSet, _lcdManager->getTmElementByIndex(_insideMenuIndex));
        } else if (_menu->getCurrentIndex() == 2)
        {
          _clock->dtCurrentTimeField(-1, eClockElementType::timeToAlarm, _lcdManager->getTmElementByIndex(_insideMenuIndex));
        }
        else if (_menu->getCurrentIndex() == 3)
        {
          _lightManager->addToAlarmValue(-10);
        }
      }
    }
    else if (_buttonsManager->getButtonLastEvent(2)  == eButtonPressLength::pressShort){
      if (_menu->getCurrentIndex() == 1){
        if (!_insideMenu){
          _insideMenu = true;
          _insideMenuIndex = 0;
          _clock->setTimeElement(now(), eClockElementType::timeToSet);
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
          _clock->setTimeElement(now(), eClockElementType::timeToAlarm);
          _lcdManager->clearLcd();
          _lcdManager->setBlink(true);
        }
        else {
          moveToNextIndexInsideMenu();
        }
      }
      else if (_menu->getCurrentIndex() == 3){
        if (!_insideMenu){
          _insideMenu = true;
          _insideMenuIndex = 0;
          _lcdManager->clearLcd();
          _lcdManager->setBlink(true);
          _lightManager->setAlarmValue(_lightManager->getCurrentValue());
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
      _clock->setSystemRtcTime();
      _alarmSet = false;
    }
    else if (_menu->getCurrentIndex() == 2){
      _alarmSet = true;
    } else if (_menu->getCurrentIndex() == 3){
      _alarmLightSet = true;
    }
}

void AlarmClockManager::playAlarm()
{
  _soundManager->playNext();
}

void AlarmClockManager::checkAlarm()
{
  if ( !_alarmTriggered ) {
    if (_alarmSet){
      tmElements_t tmCurrentTime = _clock->getTimeElement(eClockElementType::currentTime);
      tmElements_t tmAlarmTime = _clock->getTimeElement(eClockElementType::timeToAlarm);
      if (tmCurrentTime.Hour == tmAlarmTime.Hour &&
        tmCurrentTime.Minute == tmAlarmTime.Minute &&
        tmCurrentTime.Second >= tmAlarmTime.Second)
      {
        _lcdManager->clearLcd();
        _soundManager->setPlayMusic(true);
        _alarmTriggered = true;
        _alarmSet = false;
      }
    } else if (_alarmLightSet){
      if (_lightManager->isAlarmValuePassed()){
        _lcdManager->clearLcd();
        _soundManager->setPlayMusic(true);
        _alarmTriggered = true;
        _alarmLightSet = false;
      }
    }

  }
}

void AlarmClockManager::updateLightValue()
{
  _lightManager->updateLightValue();
  // Serial.println(_lightManager->getCurrentValue());
}
