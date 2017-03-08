#ifndef MENU
#define MENU

#include "MenuItem.h"

class Menu {
private:
  const int _menuSize;
  MenuItem** _menuArr;
  int _menuIndex;


public:
  Menu(int);
  ~Menu();
  void addItemToMenu(int index, const char* menuName, const int numberOfInputIterations);
  void addItemToMenu(int index, MenuItem* item);
  void printMenuAt(int index);
  void moveIndexUp();
  void moveIndexDown();
  MenuItem* getCurrentMenu();
  void resetToDefualtMenu();
  boolean isOnDefualtMenu();
  int getCurrentIndex();
  const int getCurrentMenuIterations();

};

#endif
