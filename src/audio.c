// audio.c
#include <SDL2/SDL.h>   // For SDL_INIT_AUDIO, SDL_WasInit, etc.
#include <SDL_mixer.h>  // Needed for SDL audio functions
#include <stdio.h>      // Needed for the printf() function

#include "globals.h"
#include "audio.h"

Mix_Music* bgm = NULL;

int initAudio(void) {
    if (SDL_WasInit(SDL_INIT_AUDIO) == 0) {
        SDL_InitSubSystem(SDL_INIT_AUDIO);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    bgm = Mix_LoadMUS("music.wav");
    if (!bgm) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return 1;
    }

    Mix_PlayMusic(bgm, 1);
    return 0;
}

void cleanupAudio(void) {
    if (bgm) {
        Mix_FreeMusic(bgm);
        bgm = NULL;
    }
    Mix_CloseAudio();
}
