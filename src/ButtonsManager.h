#ifndef BUTTONS_MANAGER
#define BUTTONS_MANAGER

#include "ButtonHandler.h"
#include "eButtonPressLength.h"

class ButtonsManager {
private:
  const int defaultLongPressDuration;
  const int numberOfButtons;
  const int defaultButtonPinNumber1;
  const int defaultButtonPinNumber2;
  const int defaultButtonPinNumber3;
  const char* defaultButtonName1;
  const char* defaultButtonName2;
  const char* defaultButtonName3;

  ButtonHandler buttonArr[3];

  public:
    ButtonsManager();
    void initAll();
    void handleAll();
    void printEventsToSerial();
    eButtonPressLength getButtonLastEvent(int index);

};


#endif
