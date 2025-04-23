#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "player.h"

/// Process Input:
void processInput(SDL_Event* event, int* running, Player* p1, Player* p2);



#endif
