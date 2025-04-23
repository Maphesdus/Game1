#include "tilemap.h"
#include <stdlib.h>

#define TILE_SIZE 64
#define TILES_PER_ROW 4  // 256 / 64

/// Create Tile Map:
TileMap* CreateTileMap(int width, int height, SDL_Texture* tileset) {
    TileMap* map = malloc(sizeof(TileMap));
    map->width = width;
    map->height = height;
    map->tiles = malloc(sizeof(int) * width * height);
    map->tileset = tileset;
    return map;
}

/// Destroy Tile Map:
void DestroyTileMap(TileMap* map) {
    free(map->tiles);
    free(map);
}

/// Set Tile:
void SetTile(TileMap* map, int x, int y, int tileIndex) {
    if (x >= 0 && y >= 0 && x < map->width && y < map->height)
        map->tiles[y * map->width + x] = tileIndex;
}

/// Get Tile:
int GetTile(TileMap* map, int x, int y) {
    if (x >= 0 && y >= 0 && x < map->width && y < map->height)
        return map->tiles[y * map->width + x];
    return -1;
}

/// Render Tile Map:
void RenderTileMap(TileMap* map, SDL_Renderer* renderer) {
    SDL_Rect src = { 0, 0, TILE_SIZE, TILE_SIZE };
    SDL_Rect dst = { 0, 0, TILE_SIZE, TILE_SIZE };

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            int tileIndex = GetTile(map, x, y);
            if (tileIndex < 0) continue;

            src.x = (tileIndex % TILES_PER_ROW) * TILE_SIZE;
            src.y = (tileIndex / TILES_PER_ROW) * TILE_SIZE;

            dst.x = x * TILE_SIZE;
            dst.y = y * TILE_SIZE;

            SDL_RenderCopy(renderer, map->tileset, &src, &dst);
        }
    }
}
