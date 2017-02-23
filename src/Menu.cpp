#include <Arduino.h>
#include "Menu.h"
#include "MenuItem.h"


Menu::Menu(int menuSize)
: _menuSize(menuSize)
{
  _menuArr = new MenuItem*[menuSize];
  _menuIndex = 0;
}

Menu::~Menu(){
  if (_menuArr != NULL){
    for (int i=0;i<_menuSize;i++){
      delete []_menuArr[i];
    }
    delete []*_menuArr;
  }
}

void Menu::addItemToMenu(int index, const char* menuName, const int numberOfInputIterations)
{
  if (index >= 0 && index < _menuSize)
  {
    MenuItem* newItem= new MenuItem(menuName, numberOfInputIterations);
    _menuArr[index] = newItem;
  }
}

void  Menu::addItemToMenu(int index, MenuItem* item)
{
    if (index >= 0 && index < _menuSize)
    {
      _menuArr[index] = item;
    }
}

void Menu::printMenuAt(int index)
{
  if (index >= 0 && index < _menuSize)
  {
    MenuItem *item = _menuArr[index];
    item->printMenu();
  }
}

void Menu::moveIndexUp()
{
  _menuIndex++;
  if (_menuIndex >= _menuSize){
    _menuIndex = 0;
  }
}

void Menu::moveIndexDown()
{
  _menuIndex--;
  if (_menuIndex <= -1){
    _menuIndex = _menuSize - 1;
  }
}

MenuItem* Menu::getCurrentMenu()
{
  return _menuArr[_menuIndex];
}

void Menu::resetToDefualtMenu()
{
  _menuIndex = 0;
}

boolean Menu::isOnDefualtMenu()
{
  return _menuIndex == 0;
}

int Menu::getCurrentIndex()
{
    return _menuIndex;
}

const int Menu::getCurrentMenuIterations()
{
  MenuItem *item = _menuArr[_menuIndex];
  return item->getNumberOfInputIterations();
}
