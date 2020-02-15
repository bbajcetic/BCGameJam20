#ifndef MAP_H
#define MAP_H

#include <string>

#include "texture.h"
#include "constants.h"

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

        void renderMap();
    private:
        Texture* mapOverlay;

        // 0 means walkable, 1 means wall
        int mapTiles[NUM_WIDTH_TILES * NUM_HEIGHT_TILES];


        // Textures used for temporarilly displaying bare bones map
        Texture* tempWall;
        Texture* tempGround;
};

#endif