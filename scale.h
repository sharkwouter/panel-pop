/*
 * scale.h
 *
 *  Created on: 9.2.2016
 *      Author: sharkwouter
 */

#ifndef SCALE_H_
#define SCALE_H_

#ifndef __PSP__
    const int WINDOW_WIDTH = 480;
    const int WINDOW_HEIGHT = 272;
    const int FONT_SIZE = 8;
    const int FONT_MENU_SIZE = 48;
    const int STACK_RAISE_STEPS = 16;
#else
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    const int FONT_SIZE = 16;
    const int FONT_MENU_SIZE = 48;
    const int STACK_RAISE_STEPS = 32;
#endif

#endif /* SCALE_H_ */