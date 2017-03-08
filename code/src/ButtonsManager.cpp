#include "ButtonsManager.h"


ButtonsManager::ButtonsManager()
: _defaultLongPressDuration(25), _numberOfButtons(3),
_defaultButtonPinNumber1(8),  _defaultButtonPinNumber2(9),  _defaultButtonPinNumber3(10),
_defaultButtonName1("button1"), _defaultButtonName2("button2"), _defaultButtonName3("button3")
{
  _buttonArr = new ButtonHandler*[_numberOfButtons];
  _buttonArr[0] = new ButtonHandler(_defaultButtonPinNumber1, _defaultLongPressDuration, _defaultButtonName1);
  _buttonArr[1] = new ButtonHandler(_defaultButtonPinNumber2, _defaultLongPressDuration, _defaultButtonName2);
  _buttonArr[2] = new ButtonHandler(_defaultButtonPinNumber3, _defaultLongPressDuration, _defaultButtonName3);
}

ButtonsManager::~ButtonsManager()
{
  if (_buttonArr != NULL){
    for (int i=0;i<_numberOfButtons;i++){
      delete []_buttonArr[i];
    }
    delete []*_buttonArr;
  }
}

void ButtonsManager::initAll()
{
  for (int i=0; i < _numberOfButtons; i++){
    _buttonArr[i]->init();
  }
}

void ButtonsManager::handleAll()
{
  for (int i=0; i < _numberOfButtons; i++){
    _buttonArr[i]->handle();
  }
}


eButtonPressLength ButtonsManager::getButtonLastEvent(int index)
{
  return _buttonArr[index]->getLastEvent();
}
