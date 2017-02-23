#ifndef MENU_ITEM
#define MENU_ITEM

#include <Arduino.h>
// type  pointer to void(void) function
// typedef void (*voidNoArgsFuncPtrType)(void);

class MenuItem {
  private:
    const char* _menuName;
    // voidNoArgsFuncPtrType _action;

  public:
    MenuItem(const char* menuName);
    ~MenuItem();
    const char *getName();
    void printMenu();

};

#endif
