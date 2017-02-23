#ifndef BUTTONS_MANAGER
#define BUTTONS_MANAGER

#include "ButtonHandler.h"
#include "eButtonPressLength.h"

class ButtonsManager {
private:
  const int _defaultLongPressDuration;
  const int _numberOfButtons;
  const int _defaultButtonPinNumber1;
  const int _defaultButtonPinNumber2;
  const int _defaultButtonPinNumber3;
  const char* _defaultButtonName1;
  const char* _defaultButtonName2;
  const char* _defaultButtonName3;

  ButtonHandler** _buttonArr;

  public:
    ButtonsManager();
    ~ButtonsManager();
    void initAll();
    void handleAll();
    eButtonPressLength getButtonLastEvent(int index);

};


#endif
