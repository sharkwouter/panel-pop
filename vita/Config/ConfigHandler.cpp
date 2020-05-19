/*
 * ConfigHandler.cpp
 *
 *  Created on: 11.2.2016
 *      Author: axelw
 */

#include "ConfigHandler.h"
#include "../../SDLContext.h"
#include "../../States/StateManager.h"
#include "../../InputEvents/JoyHat.h"
#include "../../InputEvents/JoyButton.h"
#include "../../InputEvents/JoyAxisDirection.h"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_mixer.h>
#include <exception>
#include <iostream>
#include <string>

ConfigHandler::ConfigHandler() {
}

ConfigHandler &ConfigHandler::getInstance() {
    static ConfigHandler instance;
    return instance;
}

bool ConfigHandler::loadConfig() {
    return true;
}

bool ConfigHandler::saveConfig() {
    return true;
}

InputConfig ConfigHandler::getKeyConfig(int player) {
    return InputConfig(parseInputEvent(Button::up),
                       parseInputEvent(Button::down),
                       parseInputEvent(Button::left),
                       parseInputEvent(Button::right),
                       parseInputEvent(Button::swap),
                       parseInputEvent(Button::raiseStack),
                       parseInputEvent(Button::start));
}

InputEvent *ConfigHandler::parseInputEvent(const Button &configKey) {
    std::string value;
    switch (configKey) {
        case up: value = "J0_A1_-";
        case down: value = "J0_A1_+";
        case left: value = "J0_A0_-";
        case right: value = "J0_A0_+";
        case swap: value = "J0_B2";
        case raiseStack: value = "J0_B1";
        case start: value = "J0_B1";
        default: value = "J0_B10";
    }

    char type = value[0];
    switch (type) {
        case 'K':return new KeyboardKey(SDL_GetScancodeFromName(value.substr(1).c_str()));
        case 'J': {
            auto jidEnd = value.find('_', 1);
            auto jidStr = value.substr(1, jidEnd - 1);
            int joystickId = std::stoi(jidStr);
            char eventType = value[jidEnd + 1];
            switch (eventType) {
                case 'B': {
                    int buttonId = std::stoi(value.substr(jidEnd + 2));
                    return new JoyButton(joystickId, buttonId);
                }
                case 'H': {
                    int hidEnd = value.find('_', jidEnd + 1);
                    int hatId = std::stoi(value.substr(jidEnd + 2, (hidEnd - 1 - (jidEnd + 1))));
                    int hatDir = std::stoi(value.substr(hidEnd + 1));
                    return new JoyHat(joystickId, hatId, hatDir);
                }
                case 'A': {
                    int aidEnd = value.find('_', jidEnd + 1);
                    int axisId = std::stoi(value.substr(jidEnd + 2, (aidEnd - 1 - (jidEnd + 1))));
                    JoyAxisDirection::Direction
                        axisDir = value[aidEnd + 1] == '+' ? JoyAxisDirection::POSITIVE : JoyAxisDirection::NEGATIVE;
                    return new JoyAxisDirection(joystickId, axisId, axisDir);
                }
            }
        }
    } // TODO: handle errors lol
}

bool ConfigHandler::getFullscreen() {
    return false;
}

int ConfigHandler::getMusicVolume() {
    return MIX_MAX_VOLUME;
}

int ConfigHandler::getSfxVolume() {
    return MIX_MAX_VOLUME;
}

int ConfigHandler::getEndlessHighScore() {
    return 0;
}

void ConfigHandler::setEndlessHighScore(int score) {
}
