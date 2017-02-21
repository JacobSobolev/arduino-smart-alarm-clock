#ifndef BUTTON_HANDLER
#define BUTTON_HANDLER

#include <Arduino.h>
#include "eButtonPressLength.h"

class ButtonHandler {
  public:

    ButtonHandler(const int i_PinNumber,const int i_LongPressDuration,const char* i_ButtonName);
    // Initialization done after construction, to permit static instances
    void init();
    // Handler, to be called in the loop()
    eButtonPressLength handle();
    eButtonPressLength getLastEvent();
    const char* getName();
  private:
    const int pinNumber;           // pin to which button is connected
    const int longPressDuration; // longpress duration
    const char* buttonName;
    boolean wasPressed;     // previous state
    int PressCounter;     // press running duration
    eButtonPressLength lastEvent; //previous event
};

#endif
