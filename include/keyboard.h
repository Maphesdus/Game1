#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL2/SDL.h>
#include "player.h"

/// Handle Keyboard Input:
void handleKeyboardInput(int* running, Player* p1, Player* p2);
//void handleKeyboardInput(SDL_KeyboardEvent keyEvent, int* running, Player* p1, Player* p2);


#endif
