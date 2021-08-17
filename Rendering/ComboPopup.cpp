/*
 * ComboPopup.cpp
 *
 *  Created on: Oct 25, 2015
 *      Author: axel
 */

#include "ComboPopup.h"

ComboPopup::ComboPopup() {

}

ComboPopup::ComboPopup(int x, int y, int value, int lifetime) :
    Popup(x, y, value, lifetime) {
}

void ComboPopup::render() {
    SDL_Rect dst;
    dst.x = _x;
    dst.y = _y;
    dst.w = 12;
    dst.h = 27;
    SDL_Rect sheet;
    sheet.x = 0;
    sheet.y = 27;
    sheet.w = 12;
    sheet.h = 27;
    SDL_RenderCopy(_SDLRenderer, _popupSprites, &sheet, &dst);
    dst.x += sheet.w;

    sheet.w = 12;
    dst.w = 12;
    for (char &c : _digits) {
        int digit = c - '0';
        if (digit == 0) {
            sheet.x = 120;
        } else {
            sheet.x = 12 + (digit - 1) * 12;
        }
        SDL_RenderCopy(_SDLRenderer, _popupSprites, &sheet, &dst);
        dst.x += sheet.w;
    }

    sheet.x = 132;
    sheet.w = 12;
    dst.w = 12;
    SDL_RenderCopy(_SDLRenderer, _popupSprites, &sheet, &dst);
}

ComboPopup::~ComboPopup() {
}

