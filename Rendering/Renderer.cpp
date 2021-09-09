/*
 * Renderer.cpp
 *
 *  Created on: Aug 16, 2015
 *      Author: axel
 */

#include "Renderer.h"

Renderer::Renderer() :
    _SDLContext(SDLContext::getInstance()),
    _texture(nullptr),
    _SDLRenderer(_SDLContext.getRenderer()),
    _blockSprites(_SDLContext.getBlockSprites()),
    _popupSprites(_SDLContext.getPopupSprites()),
    _cursorSprites(_SDLContext.getCursorSprites()),
    _garbageSprites(_SDLContext.getGarbageSprites()),
    _garbagequeueSprites(_SDLContext.getGarbagequeueSprites()),
    _matchPointSprites(_SDLContext.getMatchpointSprites()),
    _pauseSprite(_SDLContext.getPauseSprite()),
    _particleSprite(_SDLContext.getParticleSprite()) {
}

Renderer::~Renderer() {
    SDL_DestroyTexture(_texture);
}

