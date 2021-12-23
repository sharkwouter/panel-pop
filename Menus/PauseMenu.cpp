/*
 * PauseMenu.cpp
 *
 *  Created on: 6.2.2016
 *      Author: axelw
 */

#include "PauseMenu.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <string>
#include <vector>

#include "../Game/Game.h"
#include "../SDLContext.h"
#include "../States/StateManager.h"
#include "MenuItem.h"

PauseMenu::PauseMenu(Game &game) :
    _game(game) {
    addItem(MenuItem("RESUME", [this]() { _game.inputTogglePause(); }));
    addItem(
        MenuItem("QUIT",
                 []() { StateManager::getInstance().returnToTitle(); }));

    SDL_QueryTexture(_pauseSprite, NULL, NULL, &_sprite_w, &_sprite_h);
    _menu_x = WINDOW_WIDTH / 2 - _sprite_w / 2;
    _menu_y = WINDOW_HEIGHT / 2 - _sprite_h / 2;
}

PauseMenu::~PauseMenu() {
}

void PauseMenu::render() const {
    //background
    SDL_Rect sprite = {0, 0, _sprite_w, _sprite_h};
    SDL_Rect pos = {_menu_x, _menu_y, _sprite_w, _sprite_h};
    SDL_RenderCopy(_SDLRenderer, _pauseSprite, &sprite, &pos);

    int x = pos.x + FONT_SIZE + 4;
    int y = pos.y + FONT_SIZE / 2;

    _SDLContext.renderText("-PAUSE-", {255, 255, 255}, _SDLContext._fontPs, x,
                           y);

    x = pos.x + FONT_SIZE;
    y += PAUSE_MENU_TEXT_GAP;

    for (unsigned i = 0; i < _items.size(); ++i) {
        y += FONT_SIZE + PAUSE_MENU_TEXT_GAP;
        std::string text = _items.at(i).getName();
        if (_selection == i && (SDL_GetTicks() - _time) % 1000 < 500) {
            text = "\u25b6" + text;
        } else {
            text = " " + text;
        }
        _SDLContext.renderText(text, {255, 255, 255}, _SDLContext._fontPs, x,
                               y);
    }

}

void PauseMenu::inputCancel() {
    _game.inputTogglePause();
}
