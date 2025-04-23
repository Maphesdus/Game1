#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

// ENUM Direction:
typedef enum { DOWN, LEFT, RIGHT, UP } Direction;

// Player Structure:
typedef struct {
    int posX, posY;     // Position
    int width, height;  // Size
    float velX, velY;   // Velocity
    //float velocity;     // Velocity
    float speed;        // Speed
    Direction direction; // Direction

    int frame;              // current animation frame
    int frameCount;         // total number of frames
    int frameTime;          // how long each frame lasts (ms)
    int frameTimer;         // how much time has passed
    SDL_Texture *texture;   // sprite sheet texture
    SDL_Rect srcRect;       // which frame to draw
    SDL_Rect destRect;      // where to draw it
} Player;



void initPlayer(Player* player, int startX, int startY, SDL_Texture* tex);  // Initialize Player
void updatePlayer(Player* player, int deltaTime, int moving);               // Update Player
void renderPlayer(SDL_Renderer* renderer, const Player* player);            // Render Player

#endif
