/*
 * EndlessGameRenderer.cpp
 *
 *  Created on: Feb 28, 2016
 *      Author: axel
 */

#include "EndlessGameRenderer.h"

#include <SDL2/begin_code.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include <sstream>

#include "../Game/EndlessGame.h"
#include "../SDLContext.h"

EndlessGameRenderer::EndlessGameRenderer(EndlessGame &game) :
    GameRenderer(game),
    _game(game),
    _boardRenderer(_game.getBoard(0)),
    _bShake(0) {
    _texture = SDL_CreateTexture(_SDLRenderer, SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    _bg = _SDLContext.makeTextureFromImage("assets/images/bg1.png");
    _1pbg = _SDLContext.makeTextureFromImage("assets/images/1p.png");
}

EndlessGameRenderer::~EndlessGameRenderer() {

}

void EndlessGameRenderer::tick() {
    if (!_game.isPaused()) {
        _boardRenderer.tick();
        handleParticles();
        handleShake();
    }
}

SDL_Texture *EndlessGameRenderer::renderGame() {

    SDL_SetRenderTarget(_SDLRenderer, _texture);
    SDL_SetRenderDrawColor(_SDLRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_SDLRenderer);

    SDL_RenderCopy(_SDLRenderer, _bg, NULL, NULL);
    SDL_RenderCopy(_SDLRenderer, _1pbg, NULL, NULL);

    if (!_game.isPaused()) {

        renderBoard();
        renderParticles();

    }
    renderStatsText();

    if (_game.isPaused()) {
        SDL_SetTextureColorMod(_texture, 0x50, 0x50, 0x50);
        SDL_RenderCopy(_SDLRenderer, _texture, NULL, NULL);
        SDL_SetTextureColorMod(_texture, 0xFF, 0xFF, 0xFF);
        _game.getPauseMenu().render();
    } else {
        SDL_SetTextureColorMod(_texture, 0xFF, 0xFF, 0xFF);
    }

    if (_game.getState() == Game::State::ENDED
        && SDL_GetTicks() % 1000 >= 500) {
        _SDLContext.renderText("PUSH START", {255, 255, 255},
                               _SDLContext._fontSquare, GAMEOVER_TEXT_X, GAMEOVER_TEXT_Y);
    }

    return _texture;
}

void EndlessGameRenderer::renderBoard() {
    SDL_Rect pos;
    double shake;
    SDL_Texture *boardTexture;
    pos.h = BOARD_HEIGHT;
    pos.w = BOARD_WIDTH;

    pos.x = BOARD0_X;
    pos.y = BOARD0_Y;
    shake = _bShake;
    boardTexture = _boardRenderer.renderBoard();

    int shakeOffset = .5 * shake * sin(shake);
    SDL_Rect src = {0, 0, BOARD_WIDTH,
                    BOARD_HEIGHT};

    if (shakeOffset >= 0) {
        pos.y += shakeOffset;
        pos.h -= shakeOffset;
        src.h -= shakeOffset;
    } else {
        pos.h += shakeOffset;
        src.y -= shakeOffset;
        src.h += shakeOffset;
    }

    SDL_SetRenderTarget(_SDLRenderer, _texture);
    SDL_RenderCopy(_SDLRenderer, boardTexture, &src, &pos);
}

void EndlessGameRenderer::renderStatsText() {
    renderGameTime(ENDLESS_TEXT_X, ENDLESS_TIME_Y);
    //speed
    std::ostringstream os;
    os << STACK_RAISE_TICKS_START + 1 - _game.getBoard(0).getStackRaiseTicks();
    _SDLContext.renderText(os.str(), {255, 255, 255}, _SDLContext._fontPs,
                           ENDLESS_TEXT_X, ENDLESS_SPEED_Y);
    //score
    os.str("");
    os.clear();
    os << _game.getBoard(0).getScore();
    _SDLContext.renderText(os.str(), {255, 255, 255}, _SDLContext._fontPs,
                           ENDLESS_TEXT_X, ENDLESS_SCORE_y);
    //high score
    os.str("");
    os.clear();
    os << _game.getHighScore();
    _SDLContext.renderText(os.str(), {255, 255, 255}, _SDLContext._fontPs,
                           ENDLESS_TEXT_X, ENDLESS_HIGHSCORE_Y);
}

void EndlessGameRenderer::shakeBoard(int id, int duration) {
    _bShake = duration;
}

void EndlessGameRenderer::handleShake() {
    if (_bShake > 0) {
        --_bShake;
    }
}
