#include "MenuItem.h"

MenuItem::MenuItem(const char* menuName, const int numberOfInputIterations)
: _menuName(menuName), _numberOfInputIterations(numberOfInputIterations)
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


const int MenuItem::getNumberOfInputIterations()
{
  return _numberOfInputIterations;
}
