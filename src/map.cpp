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

    void Map::emptyMap() {
        for (int i = 0; i < NUM_WIDTH_TILES * NUM_HEIGHT_TILES; i++) {
            mapTiles[i] = 0;
        }
    }

    void Map::renderMap() {

    }