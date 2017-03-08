#ifndef MENU_ITEM
#define MENU_ITEM

#include <Arduino.h>

class MenuItem {
  private:
    const char* _menuName;
    const int _numberOfInputIterations;

  public:
    MenuItem(const char* menuName, const int numberOfInputIterations);
    ~MenuItem();
    const char *getName();
    void printMenu();
    const int getNumberOfInputIterations();

};

#endif
