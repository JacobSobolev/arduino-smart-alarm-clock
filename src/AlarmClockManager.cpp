#include "AlarmClockManager.h"


AlarmClockManager::AlarmClockManager()
: _lcdPinNumber1(7), _lcdPinNumber2(6), _lcdPinNumber3(5),
_lcdPinNumber4(4), _lcdPinNumber5(3), _lcdPinNumber6(2),
_lcdNumOfCols(16), _lcdNumOfRows(2), _menuSize(3), _timeToResetToDefualtMenu(50)

{
  _timeFromLastInput = 0;

  _lcd = new LiquidCrystal(_lcdPinNumber1, _lcdPinNumber2, _lcdPinNumber3,
  _lcdPinNumber4, _lcdPinNumber5, _lcdPinNumber6);

  _menu = new Menu(_menuSize);
  _menu->addItemToMenu(0, "Menu 1");
  _menu->addItemToMenu(1, "Menu 2");
  _menu->addItemToMenu(2, "Menu 3");

  _buttonsManager = new ButtonsManager();

}

AlarmClockManager::~AlarmClockManager()
{
}

void AlarmClockManager::init()
{
  _lcd->begin(_lcdNumOfCols, _lcdNumOfRows);
  _buttonsManager->initAll();
  _rtc.start();
  // _rtc.set(0, 26, 21, 22, 2, 2017); //08:00:00 24.12.2014 //sec, min, hour, day, month, year
}

void AlarmClockManager::printCurrentMenu()
{

  if (_menu->getCurrentIndex() == 0){
    printRealTimeOnLcd();
    // _lcd->clear();
    // const char* menuStr = _menu->getCurrentMenu()->getName();
    // _lcd->print(menuStr);

  } else {
    // _lcd->clear();
    _lcd->setCursor(0,0);
    const char* menuStr = _menu->getCurrentMenu()->getName();
    _lcd->print(menuStr);
  }
}

void AlarmClockManager::handleButtonsInput()
{

  _buttonsManager->handleAll();
  // Serial.print(_buttonsManager->getButtonLastEvent(0));
  // Serial.print(_buttonsManager->getButtonLastEvent(1));
  if(_buttonsManager->getButtonLastEvent(0) == eButtonPressLength::pressShort){
    _menu->moveIndexUp();
    _timeFromLastInput = 0;
    Serial.print(1);
    _lcd->clear();
  }
  else if (_buttonsManager->getButtonLastEvent(1)  == eButtonPressLength::pressShort){
    _menu->moveIndexDown();
    _timeFromLastInput = 0;
    Serial.print(2);
    _lcd->clear();
  } else if (_buttonsManager->getButtonLastEvent(2)  == eButtonPressLength::pressShort){
    //TODO : action
  } else {
    Serial.print(".");
    if (_timeFromLastInput >= _timeToResetToDefualtMenu && !_menu->isOnDefualtMenu()){
      _menu->resetToDefualtMenu();
      _lcd->clear();
    } else {
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


    // _lcd->clear();
    _lcd->setCursor(4,0);
    sprintf(msg,"%2d:%02d:%02d",hour,min,sec);
    _lcd->print(msg);
    _lcd->setCursor(3,1);
    sprintf(msg,"%2d/%02d/%02d",day,month,year);
    _lcd->print(msg);

    delete []msg;

}
