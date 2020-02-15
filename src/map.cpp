#include <fstream>

#include "map.h"

    Map::Map() {
        mapOverlay = NULL;
        tempWall = NULL;
        tempGround = NULL;

        emptyMap();
    }
    Map::~Map() {
        free();
    }

    void Map::free() {
        if (mapOverlay != NULL) {
            mapOverlay->free();
            mapOverlay = NULL;
        }
        if (tempWall != NULL) {
            tempWall->free();
            tempWall = NULL;
        }
        if (tempGround != NULL) {
            tempGround->free();
            tempGround = NULL;
        }
    }

    // Load map from map file
    void Map::loadMap(std::string mapPath) {
        std::ifstream mapInfo(mapPath);
        if (!mapInfo) {
            printf("ERROR: Failed to load map path %s\n", mapPath.c_str());
            return;
        }
        int tileInfo;
        int i = 0;
        while(mapInfo >> tileInfo) {
            mapTiles[i] = tileInfo;
            i++;
        }
    }

    void Map::loadMapTexture(std::string mapOverlayPath,
                            std::string wallPath,
                            std::string groundPath) {
        mapOverlay = new Texture();
        mapOverlay->loadTexture(mapOverlayPath, 1, 1, 1);

        tempWall = new Texture();
        tempWall->loadTexture(wallPath, 1, 1, 1);
        
        tempGround = new Texture();
        tempGround->loadTexture(groundPath, 1, 1, 1);
    }

    void Map::emptyMap() {
        for (int i = 0; i < NUM_WIDTH_TILES * NUM_HEIGHT_TILES; i++) {
            mapTiles[i] = 0;
        }
    }

    void Map::renderMap() {
        int xP = 0;
        int yP = 0;
        for (int i = 0; i < NUM_WIDTH_TILES * NUM_HEIGHT_TILES; i++) {
            xP = TILE_WIDTH * (i%NUM_WIDTH_TILES);
            yP = TILE_HEIGHT * (i/NUM_WIDTH_TILES);

            // Draw ground
            if (mapTiles[i] == 0) {
               tempGround->render(xP, yP);
            }
            // Draw wall
            else if (mapTiles[i] == 1) {
                tempWall->render(xP, yP);
            }
            
        }
    }