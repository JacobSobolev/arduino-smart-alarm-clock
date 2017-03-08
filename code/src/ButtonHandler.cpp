#include <Arduino.h>
#include "ButtonHandler.h"
#include "eButtonPressLength.h"


ButtonHandler::ButtonHandler(const int i_PinNumber,const int i_LongPressDuration,const char* i_ButtonName)
:  pinNumber(i_PinNumber), longPressDuration(i_LongPressDuration) ,buttonName(i_ButtonName)
{
}

void ButtonHandler::init()
{
  pinMode(pinNumber, INPUT);
  digitalWrite(pinNumber, HIGH); // pull-up
  wasPressed = false;
  PressCounter = 0;
  lastEvent = eButtonPressLength::pressNone;
}

eButtonPressLength ButtonHandler::handle()
{
  eButtonPressLength event;
  int isPressed = !digitalRead(pinNumber);

  if (!isPressed && wasPressed) {
    // handle release event
    if (PressCounter < longPressDuration)
      event = eButtonPressLength::pressShort;
    else
      event = eButtonPressLength::pressLong;
  }
  else
    event = eButtonPressLength::pressNone;

  // update press running duration
  if (isPressed)
    ++PressCounter;
  else
    PressCounter = 0;

  // remember state, and event
  wasPressed = isPressed;
  lastEvent = event;
  return event;
}

eButtonPressLength ButtonHandler::getLastEvent()
{
  return lastEvent;
}

const char* ButtonHandler::getName()
{
  return buttonName;
}
