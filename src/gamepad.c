#include <stdio.h>

#include "globals.h"
#include "gamepad.h"

#define SDL_JOYSTICK_AXIS_MAX 52767.0f
#define DEADZONE 8000

SDL_GameController* controller = NULL;
//int velX = 0, velY = 0;


/// Initialize Gamepad:
void initGamepad(void) {

    if (SDL_WasInit(SDL_INIT_GAMECONTROLLER) == 0) {
        SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
    }

    if (SDL_NumJoysticks() > 0 && SDL_IsGameController(0)) {
        controller = SDL_GameControllerOpen(0);
        if (!controller) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Gamepad Error", SDL_GetError(), NULL);
        } else {
            printf("Game controller connected: %s\n", SDL_GameControllerName(controller));
        }
    } else {
        printf("No compatible game controller found.\n");
    }
}


/// Handle Gamepad Input:
void handleGamepadInput(SDL_Event* event, Player* player) {
    switch (event->type) {

        // Controller Button Down:
        case SDL_CONTROLLERBUTTONDOWN:
            printf("Gamepad button %d pressed\n", event->cbutton.button);
            switch (event->cbutton.button) {
                case SDL_CONTROLLER_BUTTON_DPAD_LEFT:  player->posX -= 10; break;
                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: player->posX += 10; break;
                case SDL_CONTROLLER_BUTTON_DPAD_UP:    player->posY -= 10; break;
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN:  player->posY += 10; break;
            }
            break;

        // Controller Axis Motion:
        case SDL_CONTROLLERAXISMOTION:
        printf("Gamepad axis %d moved to %d\n", event->caxis.axis, event->caxis.value);
        analogActiveP1 = (abs(event->caxis.value) > 2000);

        // Movement scale
        float scale = 0.1f;  // Max movement speed

        if (event->caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
            //player->velX = (abs(event->caxis.value) > DEADZONE) ? event->caxis.value / DEADZONE : 0;
            player->velX = (abs(event->caxis.value) > DEADZONE) ? (event->caxis.value / SDL_JOYSTICK_AXIS_MAX) * scale : 0.0f;
        } else if (event->caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
            //player->velY = (abs(event->caxis.value) > DEADZONE) ? event->caxis.value / DEADZONE : 0;
            player->velY = (abs(event->caxis.value) > DEADZONE) ? (event->caxis.value / SDL_JOYSTICK_AXIS_MAX) * scale : 0.0f;
        }
        break;
    }
}


/// Cleanup Gamepad:
void cleanupGamepad(void) {
    if (controller) {
        SDL_GameControllerClose(controller);
        controller = NULL;
    }
}
