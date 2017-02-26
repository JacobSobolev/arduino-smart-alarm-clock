#ifndef LCD_MANAGER
#define LCD_MANAGER


#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Time.h>

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

    void setBlinkCursor(int index);

  public:
    LcdManager();
    ~LcdManager();
    void init();
    void printRealTimeOnLcd(tmElements_t tm, boolean alarmSet);
    void printInsideMenuWithClock(tmElements_t tm, const char* str1,const char* str2, int menuIndex);
    void printMenuTextOnLcd(const char* str);
    void printAlarmTriggeredOnLcd();
    void setBlink(boolean enabled);
    void clearLcd();
    
};

#endif
