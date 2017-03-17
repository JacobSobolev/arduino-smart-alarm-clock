#ifndef LCD_MANAGER
#define LCD_MANAGER


#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Time.h>
#include <eTmElementType.h>
#include <eSubmenuType.h>

class LcdManager {
  private:
    const uint8_t _lcdPinNumber1;
    const uint8_t _lcdPinNumber2;
    const uint8_t _lcdPinNumber3;
    const uint8_t _lcdPinNumber4;
    const uint8_t _lcdPinNumber5;
    const uint8_t _lcdPinNumber6;
    const uint8_t _lcdNumOfCols;
    const uint8_t _lcdNumOfRows;

    LiquidCrystal* _lcd;

    void setBlinkCursor(int index, eSubMenuType subMenuType);

  public:
    LcdManager();
    ~LcdManager();
    void init();
    void printRealTimeOnLcd(tmElements_t tm, bool alarmSet, bool alarmLight);
    void printMenuTextOnLcd(const char* str);
    void printInsideMenuWithClock(tmElements_t tm, const char* str1,const char* str2, int menuIndex);
    void printInsideMenuLight(int currentValue, int alarmValue, int menuIndex);
    void printAlarmTriggeredOnLcd();
    void setBlink(boolean enabled);
    void clearLcd();
    eTmElementType getTmElementByIndex(int index);

};

#endif
