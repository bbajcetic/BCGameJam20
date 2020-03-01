#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <string>

#include "texture.h"
#include "constants.h"
#include "SDL_shapes.h"

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

const int NUM_WIDTH_TILES = SCREEN_WIDTH / TILE_WIDTH;
const int NUM_HEIGHT_TILES = SCREEN_HEIGHT / TILE_HEIGHT;

class Map {
    public:
        Map();
        ~Map();

        void free();

        // Load map from map file
        void loadMap(std::string mapPath);
        void emptyMap();
        // Load map texture
        void loadMapTexture(std::string mapBackgroundPath,
                            std::string mapOverlayPath,
                            std::string wallPath,
                            std::string groundPath);

        bool clearPath(SDL_FCircle playerHitbox);

        int getTile(int xPos, int yPos);
        int getTilePos(int xPos, int yPos);
        SDL_Rect getTileRect(int tilePos);

        void renderMap();
    private:
        Texture* mapBackground;
        Texture* mapOverlay;

        // 0 means walkable, 1 means wall
        int mapTiles[NUM_WIDTH_TILES * NUM_HEIGHT_TILES];


        // Textures used for temporarilly displaying bare bones map
        Texture* tempWall;
        Texture* tempGround;
};

#endif