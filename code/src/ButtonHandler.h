#ifndef BUTTON_HANDLER
#define BUTTON_HANDLER

#include <Arduino.h>
#include "eButtonPressLength.h"

class ButtonHandler {
  public:

    ButtonHandler(const int i_PinNumber,const int i_LongPressDuration,const char* i_ButtonName);
    void init();
    eButtonPressLength handle();
    eButtonPressLength getLastEvent();
    const char* getName();
  private:
    const int pinNumber;
    const int longPressDuration;
    const char* buttonName;
    boolean wasPressed;
    int PressCounter;
    eButtonPressLength lastEvent;
};

#endif
