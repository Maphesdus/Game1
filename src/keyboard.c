#include <stdio.h>

#include "globals.h"
#include "keyboard.h"
#include "player.h"

extern int posX, posY;

/// Handle Keyboard Input:
/*void handleKeyboardInput(SDL_KeyboardEvent keyEvent, int* running, Player* p1, Player* p2) {
    SDL_Keycode key = keyEvent.keysym.sym;
    printf("Key pressed: %s\n", SDL_GetKeyName(key));

    switch (key) {
        case SDLK_ESCAPE:
            *running = 0;
            break;

        // SDLK_LEFT:
        case SDLK_a: // A key
            velX = -2;
            break;

        // SDLK_RIGHT:
        case SDLK_d: // D key
            velX = 2;
            break;

        // SDLK_UP:
        case SDLK_w: // W key
            velY = -2;
            break;

        // SDLK_DOWN:
        case SDLK_s: // S key
            velY = 2;
            break;
    }
}*/

void handleKeyboardInput(int* running, Player* p1, Player* p2) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL); // KeyState
    int keyPressedP1 = 0;
    int keyPressedP2 = 0;

    //printf("Key pressed: %s\n", SDL_GetKeyName(key));
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
        if (keystate[i]) printf("Key pressed: %s\n", SDL_GetScancodeName(i));

    if (keystate[SDL_SCANCODE_ESCAPE]) {
        *running = 0;
    }

    /*if (player->velX > 0) player->direction = RIGHT;
    else if (player->velX < 0) player->direction = LEFT;
    else if (player->velY > 0) player->direction = DOWN;
    else if (player->velY < 0) player->direction = UP;*/


    // Player 1 (WASD)
    if (keystate[SDL_SCANCODE_W]) { p1->velY = -5; keyPressedP1 = 1; p1->direction = UP; }
    if (keystate[SDL_SCANCODE_S]) { p1->velY =  5; keyPressedP1 = 1; p1->direction = DOWN; }
    if (keystate[SDL_SCANCODE_A]) { p1->velX = -5; keyPressedP1 = 1; p1->direction = LEFT; }
    if (keystate[SDL_SCANCODE_D]) { p1->velX =  5; keyPressedP1 = 1; p1->direction = RIGHT; }

    // Player 2 (Arrow keys)
    if (keystate[SDL_SCANCODE_UP])    { p2->velY = -5; keyPressedP2 = 1; p2->direction = UP; }
    if (keystate[SDL_SCANCODE_DOWN])  { p2->velY =  5; keyPressedP2 = 1; p2->direction = DOWN; }
    if (keystate[SDL_SCANCODE_LEFT])  { p2->velX = -5; keyPressedP2 = 1; p2->direction = LEFT; }
    if (keystate[SDL_SCANCODE_RIGHT]) { p2->velX =  5; keyPressedP2 = 1; p2->direction = RIGHT; }

    /*// Player 1 (WASD)
    if (keystate[SDL_SCANCODE_W]) p1->velY = -5;
    if (keystate[SDL_SCANCODE_S]) p1->velY =  5;
    if (keystate[SDL_SCANCODE_A]) p1->velX = -5;
    if (keystate[SDL_SCANCODE_D]) p1->velX =  5;

    // Player 2 (Arrow keys)
    if (keystate[SDL_SCANCODE_UP])    p2->velY = -5;
    if (keystate[SDL_SCANCODE_DOWN])  p2->velY =  5;
    if (keystate[SDL_SCANCODE_LEFT])  p2->velX = -5;
    if (keystate[SDL_SCANCODE_RIGHT]) p2->velX =  5;*/

    // Reset Velocity (player 1):
    if (!keyPressedP1 && !analogActiveP1) {
        p1->velX = 0;
        p1->velY = 0;
    }

    // Reset Velocity (player 2):
    if (!keyPressedP2 && !analogActiveP2) {
        p2->velX = 0;
        p2->velY = 0;
    }
}
