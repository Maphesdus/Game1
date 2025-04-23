// graphics.h
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

SDL_Texture* loadImage(SDL_Renderer* renderer, const char* filepath);
SDL_Rect drawRectangle(SDL_Renderer* renderer, int R, int G, int B, int A, int posX, int posY, int width, int height);

#endif // GRAPHICS_H
