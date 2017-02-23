#include "MenuItem.h"

MenuItem::MenuItem(const char* menuName)
: _menuName(menuName)
{
}

MenuItem::~MenuItem()
{
}

const char* MenuItem::getName()
{
  return _menuName;
}


void MenuItem::printMenu()
{
  Serial.print(_menuName);
  Serial.println();
}
