#ifndef BUTTONS_MANAGER
#define BUTTONS_MANAGER

#include "ButtonHandler.h"

class ButtonsManager {
  public:
    ButtonsManager();
    void initAll();
    void handleAll();
    void printEventsToSerial();

  private:
    const int defaultLongPressDuration;
    const int numberOfButtons;
    const int defaultButtonPinNumber1;
    const int defaultButtonPinNumber2;
    const int defaultButtonPinNumber3;
    const char* defaultButtonName1;
    const char* defaultButtonName2;
    const char* defaultButtonName3;

    // ButtonHandler button1;
    // ButtonHandler button2;
    // ButtonHandler button3;
    ButtonHandler buttonArr[3];



};


#endif
