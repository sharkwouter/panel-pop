/*
 * scale.h
 *
 *  Created on: 9.2.2016
 *      Author: sharkwouter
 */

#ifndef SCALE_H_
#define SCALE_H_

#ifdef __PSP__
    const int TILE_SIZE = 16;
    const int WINDOW_WIDTH = 480;
    const int WINDOW_HEIGHT = 272;
    const int FONT_SIZE = 8;
    const int FONT_MENU_SIZE = 24;

    const int BOARD0_X = 109;
    const int BOARD0_Y = 38;
    const int BOARD1_X = 275;
    const int BOARD1_Y = 38;

    const int CURSOR_OFFSET = 3;

    const int STACK_RAISE_TICKS_START = 20;

    const int ENDLESS_HIGHSCORE_X = 0;
    const int ENDLESS_HIGHSCORE_Y = 0;
    const int ENDLESS_SCORE_X = 0;
    const int ENDLESS_SCORE_y = 0;
    const int ENDLESS_SPEED_X = 0;
    const int ENDLESS_SPEED_Y = 0;
    const int ENDLESS_TIME_X = 0;
    const int ENDLESS_TIME_Y = 0;

    const int VERSUS_TIME_X = 220;
    const int VERSUS_TIME_Y = 126;
    const int VERSUS_POINTS_X = 212;
    const int VERSUS_POINTS_Y = 106;
#else
    const int TILE_SIZE = 32;
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    const int FONT_SIZE = 16;
    const int FONT_MENU_SIZE = 48;

    const int BOARD0_X = 58;
    const int BOARD0_Y = 43;
    const int BOARD1_X = 390;
    const int BOARD1_Y = 43;

    const int CURSOR_OFFSET = 6;

    const int STACK_RAISE_TICKS_START = 10;

    const int VERSUS_TIME_X = 280;
    const int VERSUS_TIME_Y = 218;
    const int VERSUS_POINTS_X = 264;
    const int VERSUS_POINTS_Y = 180;
#endif

const int BOARD_WIDTH = TILE_SIZE*6;
const int BOARD_HEIGHT = TILE_SIZE*12;

const int CURSOR_WIDTH = TILE_SIZE * 2 + CURSOR_OFFSET * 2;
const int CURSOR_HEIGHT = TILE_SIZE + CURSOR_OFFSET * 2;
const int CURSOR_SPRITE_X = TILE_SIZE * 7;
const int CURSOR_SPRITE_Y = TILE_SIZE * 2;

#endif /* SCALE_H_ */