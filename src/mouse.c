#include <stdio.h>

#include "globals.h"
#include "mouse.h"

/// Handle Mouse Input:
void handleMouseInput(SDL_Event* event) {
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
            printf("Mouse button %d pressed at (%d, %d)\n",
                   event->button.button, event->button.x, event->button.y);
            break;

        case SDL_MOUSEMOTION:
            printf("Mouse moved to (%d, %d)\n", event->motion.x, event->motion.y);
            break;
    }
}
