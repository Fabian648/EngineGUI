//
// Created by fabia on 23.11.2024.
//

#include "utils.h"

std::vector<SDL_Rect> list_rect;

void createRectangle(int width, int height, int x, int y) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    list_rect.push_back(rect);
}

bool isPointInRect(int x, int y, const SDL_Rect& rect) {
    return x >= rect.x && x <= rect.x + rect.w &&
           y >= rect.y && y <= rect.y + rect.h;
}
