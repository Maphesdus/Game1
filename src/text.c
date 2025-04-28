// text.c
#include "text.h"
#include <stdio.h>

static TTF_Font* globalFont = NULL;


/// Initialize Text System:
int initTextSystem(const char* fontPath, int fontSize) {
    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
        return -1;
    }

    globalFont = TTF_OpenFont(fontPath, fontSize);
    if (!globalFont) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return -1;
    }

    return 0;
}


/// Shutdown Text System:
void shutdownTextSystem() {
    if (globalFont) {
        TTF_CloseFont(globalFont);
        globalFont = NULL;
    }
    TTF_Quit();
}


/// Render Text:
void renderText(SDL_Renderer* renderer, const char* message, int x, int y, SDL_Color color) {
    if (!globalFont) return;

    SDL_Surface* surface = TTF_RenderText_Blended(globalFont, message, color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest = { x, y, surface->w, surface->h };

    SDL_RenderCopy(renderer, texture, NULL, &dest);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
