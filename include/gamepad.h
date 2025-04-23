#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <SDL2/SDL.h>
#include "player.h"

/// Global Variables:
extern SDL_GameController* controller;
//extern int velX, velY;

/// Function Declarations:
void initGamepad(void); // Initialize Gamepad
void handleGamepadInput(SDL_Event* event, Player* player);  // Handle Gamepad Input
void cleanupGamepad(void);  // Cleanup Gamepad


#endif // GAMEPAD_H
