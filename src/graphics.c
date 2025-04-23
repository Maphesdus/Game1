// graphics.c
#include <stdio.h>

#include "globals.h"
#include "graphics.h"

/// Load Image:
SDL_Texture* loadImage(SDL_Renderer* renderer, const char* filepath){
    SDL_Surface* surface = SDL_LoadBMP(filepath);
    SDL_Texture* texture = NULL;
    int texW = 0, texH = 0;

    printf("BitsPerPixel: %d\n", surface->format->BitsPerPixel);

    // Set magenta (255, 0, 255) as the transparent color
    if (surface->format->BitsPerPixel >= 24) {
        Uint32 colorkey = SDL_MapRGB(surface->format, 255, 0, 255); // Magenta
        if (SDL_SetColorKey(surface, SDL_TRUE, colorkey) != 0) {
            printf("SDL_SetColorKey failed: %s\n", SDL_GetError());
        }
    } else {
        printf("Surface is NULL or format is unsupported.\n");
        // optionally return NULL or fallback
    }

    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    } else {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "BMP Load Error", SDL_GetError(), NULL);
        return NULL;
    }

    if (texture) {
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        printf("Loaded image size: %d x %d\n", texW, texH);
    } else {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Texture Creation Error", SDL_GetError(), NULL);
        return NULL;
    }




    return texture;
}

/// Draw Rectangle:
SDL_Rect drawRectangle(SDL_Renderer* renderer, int R, int G, int B, int A, int posX, int posY, int width, int height){
    SDL_SetRenderDrawColor(renderer, R, G, B, A);  // White
    SDL_Rect rect = { posX, posY, height, width };
    SDL_RenderFillRect(renderer, &rect);
    return rect;
}
