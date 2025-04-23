#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL2/SDL.h>

typedef struct {
    int width;
    int height;
    int* tiles;           // 1D array storing tile indices
    SDL_Texture* tileset; // Sprite sheet
} TileMap;

TileMap* CreateTileMap(int width, int height, SDL_Texture* tileset);
void DestroyTileMap(TileMap* map);
void RenderTileMap(TileMap* map, SDL_Renderer* renderer);
void SetTile(TileMap* map, int x, int y, int tileIndex);
int  GetTile(TileMap* map, int x, int y);

#endif
