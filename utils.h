#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <vector>

extern std::vector<SDL_Rect> list_rect;

void createRectangle(int width, int height, int x, int y);
bool isPointInRect(int x, int y, const SDL_Rect& rect);

#endif // UTILS_H
