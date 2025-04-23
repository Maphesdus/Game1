#include "globals.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "gamepad.h"

/// Process Input:
void processInput(SDL_Event* event, int* running, Player* p1, Player* p2) {
    switch (event->type) {
        case SDL_QUIT:
            *running = 0;
            break;

        /// Handle Mouse Input:
        case SDL_MOUSEBUTTONDOWN:   // Mouse Button Down
        case SDL_MOUSEMOTION:       // Mouse Motion
            handleMouseInput(event);
            break;

        /// Handle Gamepad Input:
        case SDL_CONTROLLERBUTTONDOWN:  // Controller Button Down
        case SDL_CONTROLLERAXISMOTION:  // Controller Axis Motion
            handleGamepadInput(event, p1);
            break;

            /// Connect Additional Controller Device:
        case SDL_CONTROLLERDEVICEADDED: // Controller Device Added
            initGamepad(); // Re-initialize the gamepad when a new one is connected
            break;

    }

    // Call keyboard handler once per frame (smooth input)
    //handleKeyboardInput(running, p1, p2);
}
