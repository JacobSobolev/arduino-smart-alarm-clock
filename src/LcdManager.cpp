#include <LcdManager.h>

LcdManager::LcdManager()
:_lcdPinNumber1(7), _lcdPinNumber2(6), _lcdPinNumber3(5),
_lcdPinNumber4(4), _lcdPinNumber5(3), _lcdPinNumber6(2),
_lcdNumOfCols(16), _lcdNumOfRows(2)
{
  _lcd = new LiquidCrystal(_lcdPinNumber1, _lcdPinNumber2, _lcdPinNumber3,
  _lcdPinNumber4, _lcdPinNumber5, _lcdPinNumber6);
}

LcdManager::~LcdManager()
{

}

void LcdManager::init()
{
  _lcd->begin(_lcdNumOfCols, _lcdNumOfRows);
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

void LcdManager::clearLcd(){
  _lcd->clear();
}

void LcdManager::printRealTimeOnLcd(tmElements_t tm, boolean alarmSet){
  if (alarmSet){
    _lcd->setCursor(0,0);
    _lcd->write(byte(0));
  }
  char* msg = new char[17];
  _lcd->setCursor(4,0);
  sprintf(msg,"%2d:%02d:%02d",tm.Hour,tm.Minute,tm.Second);
  _lcd->print(msg);
  _lcd->setCursor(3,1);
  sprintf(msg,"%2d/%02d/%02d",tm.Day,tm.Month,tm.Year + 1970);
  _lcd->print(msg);
  delete []msg;
}

void LcdManager::printInsideMenuWithClock(tmElements_t tm, const char* str1,const char* str2, int menuIndex){
  char* msg = new char[17];
  _lcd->setCursor(0,0);
  _lcd->print(str1);
  _lcd->setCursor(6,0);
  sprintf(msg,"%2d:%02d:%02d",tm.Hour,tm.Minute,tm.Second);
  _lcd->print(msg);
  _lcd->setCursor(0,1);
  _lcd->print(str2);
  _lcd->setCursor(6,1);
  sprintf(msg,"%2d/%02d/%02d",tm.Day,tm.Month,tm.Year + 1970);
  _lcd->print(msg);
  setBlinkCursor(menuIndex);
  delete []msg;
}

void LcdManager::printMenuTextOnLcd(const char* str){
  _lcd->setCursor(6,0);
  _lcd->print("MENU");
  _lcd->setCursor(4,1);
  _lcd->print(str);
  _lcd->setCursor(15,1);
 _lcd->write(byte(1));
 _lcd->setCursor(0,1);
 _lcd->write(byte(2));
}

void LcdManager::printAlarmTriggeredOnLcd()
{
  _lcd->setCursor(6,0);
  _lcd->print("Alarm");
  _lcd->setCursor(5,1);
  _lcd->print("Wake Up");
}

void LcdManager::setBlinkCursor(int index){
  if (index == 0){
    _lcd->setCursor(7,0);
  }
  else if (index == 1){
    _lcd->setCursor(10,0);
  }
  else if (index == 2){
    _lcd->setCursor(13,0);
  }
  else if (index == 3){
    _lcd->setCursor(7,1);
  }
  else if (index == 4){
    _lcd->setCursor(10,1);
  }
  else if (index == 5){
    _lcd->setCursor(15,1);
  }
}

void LcdManager::setBlink(boolean enabled){
  if (enabled){
    _lcd->blink();
  }
  else {
    _lcd->noBlink();
  }

}
