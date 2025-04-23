#include <stdio.h>

#include "player.h"

/// Initialize Player:
void initPlayer(Player* player, int startX, int startY, SDL_Texture* tex) {
    player->posX = startX;
    player->posY = startY;
    player->width = 32;
    player->height = 48;
    player->velX = 0.0f;
    player->velY = 0.0f;
    player->speed = 1.0f;
    player->texture = tex;
    player->direction = DOWN;


    //player->texture = IMG_LoadTexture(renderer, "assets/player_sprite.png");
    player->frameCount = 6;
    player->frameTime = 100; // milliseconds per frame
    player->frame = 0;
    player->frameTimer = 0;
    player->srcRect = (SDL_Rect){0, 0, 32, 48};
}

/// Update Player:
void updatePlayer(Player* player, int deltaTime, int moving) {
    //printf("Update: velX = %.2f, velY = %.2f\n", player->velX, player->velY);

    // Animation:
    if (moving) {
        // advance animation
            player->frameTimer += deltaTime;
            if (player->frameTimer >= player->frameTime) {
                player->frame = (player->frame + 1) % player->frameCount;
                player->frameTimer = 0;
            }
            player->srcRect.x = player->frame * player->srcRect.w;
    } else {
        player->frame = 0; // standing still
    }

    // Update Direction:
    player->srcRect.y = player->direction * player->srcRect.h;

    // Update Movement by velocity / speed
    player->posX += player->velX * player->speed;
    player->posY += player->velY * player->speed;

    // Optional boundary checks
    if (player->posX < 0) player->posX = 0;
    if (player->posY < 0) player->posY = 0;
    if (player->posX + player->width > 800) player->posX = 800 - player->width;
    if (player->posY + player->height > 600) player->posY = 600 - player->height;
}

/// Render Player:
void renderPlayer(SDL_Renderer *renderer, const Player *player) {
    SDL_Rect dst;
    dst.x = player->posX;
    dst.y = player->posY;
    dst.w = player->srcRect.w;
    dst.h = player->srcRect.h;

    SDL_RenderCopy(renderer, player->texture, &player->srcRect, &dst);
}


/*void renderPlayer(SDL_Renderer* renderer, const Player* player) {
    //SDL_Rect dst = { player->posX, player->posY, player->width, player->height };

    player->destRect.x = player->posX;
    player->destRect.y = player->posY;
    player->destRect.w = player->srcRect.w;
    player->destRect.h = player->srcRect.h;

    //SDL_RenderCopy(renderer, player->texture, NULL, &dst);
    SDL_RenderCopy(renderer, player->texture, &player->srcRect, &player->destRect);
}*/
