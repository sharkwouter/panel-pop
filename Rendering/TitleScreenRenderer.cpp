/*
 * TitleScreenRenderer.cpp
 *
 *  Created on: 15.1.2016
 *      Author: axelw
 */

#include "TitleScreenRenderer.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <string>

#include "../Main.h"
#include "../SDLContext.h"
#include "../States/TitleScreen.h"

TitleScreenRenderer::TitleScreenRenderer(TitleScreen &ts) :
    _titleScreen(ts) {
    _texture = SDL_CreateTexture(_SDLRenderer, SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    _titleImg = _SDLContext.makeTextureFromImage("assets/images/title.png");
    _versionText = _SDLContext.makeTextureFromFont(PANELPOP_VERSION,
                                                   {0, 0, 0}, _SDLContext._fontPs);
}

TitleScreenRenderer::~TitleScreenRenderer() {
    SDL_DestroyTexture(_titleImg);
    SDL_DestroyTexture(_versionText);
}

SDL_Texture *TitleScreenRenderer::render() {
    SDL_SetRenderTarget(_SDLRenderer, _texture);
    SDL_RenderCopy(_SDLRenderer, _titleImg, NULL, NULL);
    SDL_Rect versionpos = {TITLESCREEN_VERSION_X, 0, 0, 0};
    SDL_QueryTexture(_versionText, NULL, NULL, &versionpos.w, &versionpos.h);
    versionpos.y = WINDOW_HEIGHT - versionpos.h;
    SDL_RenderCopy(_SDLRenderer, _versionText, NULL, &versionpos);

    _titleScreen.getMenu().render();

    return _texture;
}
