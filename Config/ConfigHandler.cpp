/*
 * ConfigHandler.cpp
 *
 *  Created on: 11.2.2016
 *      Author: axelw
 */

#include "ConfigHandler.h"
#include "../SDLContext.h"
#include "../States/StateManager.h"
#include "../InputEvents/JoyHat.h"
#include "../InputEvents/JoyButton.h"
#include "../InputEvents/JoyAxisDirection.h"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_mixer.h>
#include <exception>
#include <iostream>
#include <string>
#include <json/json.h>
#include <fstream>


ConfigHandler::ConfigHandler() {
}

ConfigHandler &ConfigHandler::getInstance() {
    static ConfigHandler instance;
    return instance;
}

bool ConfigHandler::loadConfig() {
    std::ifstream configFile(CONFIG_FILENAME);
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, configFile, &_settingsTree, &errs)) {
        std::cerr << "error in reading config file, using defaults..." << std::endl;
        std::cerr << errs;
        configFile.close();
        return false;
    }
    std::cout << _settingsTree << std::endl;
    configFile.close();
    return true;
}

bool ConfigHandler::saveConfig() {
    std::ofstream configFile(CONFIG_FILENAME, std::ios::binary);
    configFile << _settingsTree;
    configFile.close();
    return true;
}

InputConfig ConfigHandler::getKeyConfig() {

    return InputConfig(parseInputEvent("up"),
                       parseInputEvent("down"),
                       parseInputEvent("left"),
                       parseInputEvent("right"),
                       parseInputEvent("swap"),
                       parseInputEvent("raiseStack"),
                       parseInputEvent("start"));

}

InputEvent *ConfigHandler::parseInputEvent(const std::string &configKey) {
    std::string value = _settingsTree["keys"].get(configKey, "").asString();

    char type = value[0];
    switch (type) {
        case 'K':return new KeyboardKey(SDL_GetScancodeFromName(value.substr(1).c_str()));
        case 'J': {
            auto jidEnd = value.find('_', 1);
            auto jidStr = value.substr(1, jidEnd - 1);
            int joystickId = atoi(jidStr.c_str());
            char eventType = value[jidEnd + 1];
            switch (eventType) {
                case 'B': {
                    int buttonId = atoi(value.substr(jidEnd + 2).c_str());
                    return new JoyButton(joystickId, buttonId);
                }
                case 'A': {
                    int aidEnd = value.find('_', jidEnd + 1);
                    int axisId = atoi(value.substr(jidEnd + 2, (aidEnd - 1 - (jidEnd + 1))).c_str());
                    JoyAxisDirection::Direction
                        axisDir = value[aidEnd + 1] == '+' ? JoyAxisDirection::POSITIVE : JoyAxisDirection::NEGATIVE;
                    return new JoyAxisDirection(joystickId, axisId, axisDir);
                }
            }
        }
    } // TODO: handle errors lol
}

void ConfigHandler::setKeyConfig(InputConfig config) {
    StateManager::getInstance().setKeys(config);
    _settingsTree["up"] = config._up->toString();
    _settingsTree["down"] = config._down->toString();
    _settingsTree["left"] = config._left->toString();
    _settingsTree["right"] = config._right->toString();
    _settingsTree["swap"] = config._swap->toString();
    _settingsTree["raiseStack"] = config._raiseStack->toString();
    _settingsTree["start"] = config._start->toString();

}

void ConfigHandler::setFullscreen(bool fs) {
    _settingsTree["video"]["fullscreen"] = fs;
    if (fs != SDLContext::getInstance().isFullscreen()) {
        SDLContext::getInstance().toggleFullscreen();
    }
}

void ConfigHandler::setMusicVolume(int vol) {
    _settingsTree["audio"]["music_volume"] = vol;
    Mix_VolumeMusic(vol);
}

void ConfigHandler::setSfxVolume(int vol) {
    _settingsTree["audio"]["sfx_volume"] = vol;
    Mix_Volume(-1, vol);
}

bool ConfigHandler::getFullscreen() {
    return _settingsTree["video"].get("fullscreen", false).asBool();
}

int ConfigHandler::getMusicVolume() {
    return _settingsTree["audio"].get("music_volume", MIX_MAX_VOLUME).asInt();
}

int ConfigHandler::getSfxVolume() {
    return _settingsTree["audio"].get("sfx_volume", MIX_MAX_VOLUME).asInt();
}

int ConfigHandler::getEndlessHighScore() {
    return _settingsTree["endless"].get("high_score", 0).asInt();
}

void ConfigHandler::setEndlessHighScore(int score) {
    _settingsTree["endless"]["high_score"] = score;
}
