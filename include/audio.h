// audio.h
#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h>


extern Mix_Music* bgm;

int initAudio(void);
void cleanupAudio(void);

#endif // AUDIO_H
