// text.h
#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/// Initializes SDL_ttf and loads a font. Returns 0 on success, -1 on failure.
int initTextSystem(const char* fontPath, int fontSize);

/// Frees resources used by the text system.
void shutdownTextSystem();

/// Renders text at (x, y) with the specified color.
void renderText(SDL_Renderer* renderer, const char* message, int x, int y, SDL_Color color);

#endif
