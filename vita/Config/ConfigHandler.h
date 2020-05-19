/*
 * ConfigHandler.h
 *
 *  Created on: 11.2.2016
 *      Author: axelw
*/

#ifndef CONFIG_CONFIGHANDLER_H_
#define CONFIG_CONFIGHANDLER_H_

#include <SDL2/SDL_scancode.h>
#include "../../Config/InputConfig.h"
#include "../../InputEvents/KeyboardKey.h"

enum Button {up, down, left, right, swap, raiseStack, start};

class ConfigHandler {
 public:

  static ConfigHandler &getInstance();

  bool loadConfig();
  bool saveConfig();

  InputConfig getKeyConfig(int player);
  void setKeyConfig(InputConfig, int player);
  void setFullscreen(bool);
  void setMusicVolume(int);
  void setSfxVolume(int);

  bool getFullscreen();
  int getMusicVolume();
  int getSfxVolume();

  int getEndlessHighScore();
  void setEndlessHighScore(int);

 private:
  ConfigHandler();
  ConfigHandler(ConfigHandler const &) = delete;
  void operator=(ConfigHandler const &) = delete;

  InputEvent *parseInputEvent(const Button &configKey);
};

#endif /* CONFIG_CONFIGHANDLER_H_ */
