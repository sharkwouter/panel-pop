/*
 * ChainPanel.cpp
 *
 *  Created on: Aug 25, 2015
 *      Author: axel
 */

#include "ChainPopup.h"

ChainPopup::ChainPopup() {
}

ChainPopup::ChainPopup(int x, int y, int value, int lifetime) :
    Popup(x, y, value, lifetime) {
}

void ChainPopup::render() {
    SDL_Rect dst;
    dst.x = _x;
    dst.y = _y;
    dst.w = 24;
    dst.h = 27;
    SDL_Rect sheet;
    sheet.x = 0;
    sheet.y = 0;
    sheet.w = 24;
    sheet.h = 27;
    SDL_RenderCopy(_SDLRenderer, _popupSprites, &sheet, &dst);
    dst.x += sheet.w;

    sheet.w = 12;
    dst.w = 12;
    for (char &c : _digits) {
        int digit = c - '0';
        if (digit == 0) {
            sheet.x = 144;
        } else {
            sheet.x = 24 + (digit - 1) * 12;
        }
        SDL_RenderCopy(_SDLRenderer, _popupSprites, &sheet, &dst);
        dst.x += sheet.w;
    }

    sheet.x = 144;
    sheet.w = 12;
    dst.w = 12;
    SDL_RenderCopy(_SDLRenderer, _popupSprites, &sheet, &dst);
}

ChainPopup::~ChainPopup() {
}
