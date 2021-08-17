/*
 * MainMenu.h
 *
 *  Created on: 22.2.2016
 *      Author: axelw
 */

#ifndef MENUS_MAINMENU_H_
#define MENUS_MAINMENU_H_

#include "Menu.h"
#include "../scale.h"

class MainMenu : public Menu {
 public:
  MainMenu();
  virtual ~MainMenu();
  void render() const;
 private:
  int menu_x = WINDOW_WIDTH * 0.5;
  int menu_y = WINDOW_HEIGHT * 0.4;
};

#endif /* MENUS_MAINMENU_H_ */
