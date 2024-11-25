#include "utils.h"

std::vector<SDL_Rect> list_rect;

void createRectangle(int width, int height, int x, int y) {
    SDL_Rect rect = {x, y, width, height};
    list_rect.push_back(rect);
}

bool isPointInRect(int x, int y, const SDL_Rect& rect) {
    return x >= rect.x && x <= rect.x + rect.w &&
           y >= rect.y && y <= rect.y + rect.h;
}
