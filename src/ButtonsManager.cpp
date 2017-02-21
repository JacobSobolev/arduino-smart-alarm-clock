#include "ButtonsManager.h"
#include "ButtonHandler.h"

ButtonsManager::ButtonsManager()
: defaultLongPressDuration(25), numberOfButtons(3),
defaultButtonPinNumber1(8),  defaultButtonPinNumber2(9),  defaultButtonPinNumber3(10),
defaultButtonName1("button1"), defaultButtonName2("button2"), defaultButtonName3("button3"),
buttonArr({ButtonHandler(defaultButtonPinNumber1,defaultLongPressDuration,defaultButtonName1),
          ButtonHandler(defaultButtonPinNumber2,defaultLongPressDuration,defaultButtonName2),
          ButtonHandler(defaultButtonPinNumber3,defaultLongPressDuration,defaultButtonName3)})
{

}



void ButtonsManager::initAll()
{
  for (int i=0;i<numberOfButtons;i++){
    buttonArr[i].init();
  }
}

void ButtonsManager::handleAll()
{
  for (int i=0;i<numberOfButtons;i++){
    buttonArr[i].handle();
  }
}


void ButtonsManager::printEventsToSerial()
{
  int flag = 0;
  static int counter = 0;
  for (int i=0;i<numberOfButtons;i++){
    if (buttonArr[i].getLastEvent()){
        Serial.print(buttonArr[i].getName());
        Serial.print(".SL"[buttonArr[i].getLastEvent()]);
        flag = 1;
    }
  }

  if (flag == 0)
  {
    Serial.print(".");
  }

  if ((++counter & 0x1f) == 0)
  {
    Serial.println();
  }

}
