/*
 * EndlessGameRenderer.h
 *
 *  Created on: Feb 28, 2016
 *      Author: axel
 */

#ifndef ENDLESSGAMERENDERER_H_
#define ENDLESSGAMERENDERER_H_

#include "BoardRenderer.h"
#include "GameRenderer.h"
#include "../scale.h"

class EndlessGame;

class EndlessGameRenderer : public GameRenderer {
 public:
  EndlessGameRenderer(EndlessGame &);
  virtual ~EndlessGameRenderer();

  void tick();
  SDL_Texture *renderGame();

  void shakeBoard(int id, int duration);

 private:
  EndlessGame &_game;
  BoardRenderer _boardRenderer;

  SDL_Texture *_bg;
  SDL_Texture *_1pbg;

  int _bShake;

  void renderBoard();
  void renderStatsText();
  void handleShake();
};

#endif /* ENDLESSGAMERENDERER_H_ */
