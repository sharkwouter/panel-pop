/*
 * scale.h
 *
 *  Created on: 9.2.2016
 *      Author: sharkwouter
 */

#ifndef SCALE_H_
#define SCALE_H_

#ifndef __PSP__
    const int TILE_SIZE = 16;
    const int WINDOW_WIDTH = 480;
    const int WINDOW_HEIGHT = 272;
    const int FONT_SIZE = 8;
    const int FONT_MENU_SIZE = 24;

    const int BOARD0_X = 109;
    const int BOARD0_Y = 38;
    const int BOARD1_X = 292;
    const int BOARD1_Y = 38;
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
#endif

const int BOARD_WIDTH = TILE_SIZE*6;
const int BOARD_HEIGHT = TILE_SIZE*12;

#endif /* SCALE_H_ */