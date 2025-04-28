#include <SDL2/SDL.h>       // Simple DirectMedia Layer Graphics Library (needed for rendering graphics in a window)
#include <SDL_mixer.h>      // Simple DirectMedia Layer Sound Library (needed for playing audio files for music and sound effects)
#include <SDL2/SDL_ttf.h>   // Simple DirectMedia Layer TrueType Fonts Library (needed for displaying text in the graphics window)

#include <stdio.h>  // Standard Input/Output
#include <stdlib.h> // Standard Library
#include <time.h>   // Needed to generate random numbers

#include "globals.h"
#include "sdl_init.h"
#include "graphics.h"
#include "audio.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "gamepad.h"
#include "tilemap.h"
#include "player.h"
#include "text.h"

//int DAT_loader(); // Forward declaration: This tells the compiler that DAT_loader() exists somewhere else.



/// WinMain:
// Main Window
int WinMain(int argc, char* argv[]) {
    // Directory:
    SDL_Log("Current working directory: %s", SDL_GetBasePath());

    // Initialize the Window and Renderer:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if (initSDL(&window, &renderer) != 0)return 1;

    // Get Center of Window:
    int winWidth, winHeight;
    SDL_GetWindowSize(window, &winWidth, &winHeight);
    int centerX = winWidth / 2;
    int centerY = winHeight / 2;

    // Initialize the Audio:
    //if (initAudio() != 0) return 1;

    // Initialize Text:
    //if (initTextSystem("assets/fonts/arial/Arial.ttf", 28) != 0) return 1;
    //if (initTextSystem("assets/fonts/Qager-zrlmw.ttf", 12) != 0) return 1;
    if (initTextSystem("assets/fonts/PressStart2P-vaV7.ttf", 12) != 0) return 1;

    // Initialize the Gamepad:
    initGamepad();

    // Initialize Images:
    texture1 = loadImage(renderer, "assets/hero.bmp");
    texture2 = loadImage(renderer, "assets/chrono.bmp");

    // Load tileset texture:
    SDL_Texture* tileset = loadImage(renderer, "assets/tileset_01.bmp");

    // Create Tile Map:
    TileMap* path = CreateTileMap(50, 50, tileset);

    // Set some tiles
    //SetTile(path, 0, 0, 0);
    //SetTile(path, 1, 0, 1);
    //SetTile(path, 2, 0, 2);
    //SetTile(path, 3, 0, 3);

    // Seed the random number generator
    srand(time(NULL));

    // Generate a random number between 0 and RAND_MAX
    //int randomNumber = rand();
    int min = 0;
    int max = 3;


    for(int i = 0; i <= 20; i++){
        for(int j = 0; j <= 9; j++){
            int randomNumber = rand() % (max - min + 1) + min;
            int tile = randomNumber;
            SetTile(path, i, j, tile);
        }
    }




    // Last Frame Time:
    Uint32 lastFrameTime = SDL_GetTicks();


    // Initialize Player 1:
    Player player1;
    initPlayer(&player1, centerX - 15, centerY, texture1);

    // Initialize Player 2:
    Player player2;
    initPlayer(&player2, centerX + 15, centerY, texture2);

    /// Main loop
    SDL_Event event;
    int running = 1;

    // Main Render Loop:
    while (running) {

        // Event Loop:
        while (SDL_PollEvent(&event)) {
            // Process Input (keyboard, mouse, gamepad)
            processInput(&event, &running, &player1, &player2);
        } // End Event Loop

        // BEFORE rendering / updating players
        handleKeyboardInput(&running, &player1, &player2);

        // Clear the screen:
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black
        SDL_RenderClear(renderer);


        // Setup DeltaTime:
        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        // Render Tiles:
        RenderTileMap(path, renderer);

        // Update Players:
        int moving1 = (player1.velX != 0 || player1.velY != 0);
        int moving2 = (player2.velX != 0 || player2.velY != 0);
        updatePlayer(&player1, deltaTime, moving1);
        updatePlayer(&player2, deltaTime, moving2);

        // Render Players:
        renderPlayer(renderer, &player1);
        renderPlayer(renderer, &player2);

        // Draw Rectange:
        //drawRectangle(SDL_Renderer* renderer, int R, int G, int B, int A, int posX, int posY, int width, int height)
        drawRectangle(renderer, 255, 0, 0, 255, 5, 5, 15, 150);
        drawRectangle(renderer, 255, 0, 0, 255, winWidth - 155, 5, 15, 150);

        // Render Text:
        SDL_Color white = {255, 255, 255, 255};  // White color with full alpha
        renderText(renderer, "HP: 100%", 7, 7, white);


        // Present the rendered frame
        SDL_RenderPresent(renderer);

        SDL_Delay(16);  // Roughly 60 FPS

    } // End Render Loop


    // Clean up:
    if (texture1) SDL_DestroyTexture(texture1); // Destroy/Cleanup texture1
    if (texture2) SDL_DestroyTexture(texture2); // Destroy/Cleanup texture2

    cleanupGamepad();
    cleanupAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO); // Quit Audio Subsystem
    shutdownTextSystem(); // Shutdown Text System
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER); // Quit Game Controller Subsystem
    DestroyTileMap(path); // Cleanup/Destroy tilemap

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
