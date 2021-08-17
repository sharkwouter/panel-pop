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
    _spriteSheet(_SDLContext.getSpriteSheet()),
    _blockSprites(_SDLContext.getBlockSprites()),
    _popupSprites(_SDLContext.getPopupSprites()),
    _cursorSprites(_SDLContext.getCursorSprites()),
    _pauseSprite(_SDLContext.getPauseSprite()) {
}

Renderer::~Renderer() {
    SDL_DestroyTexture(_texture);
}

