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
_SDLRenderer(_SDLContext.getRenderer())
{}

Renderer::~Renderer() {
	// TODO Auto-generated destructor stub
}

