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

    bool Map::clearPath(SDL_Rect playerBoxPos) {
        if (getTile(playerBoxPos.x, playerBoxPos.y) == 1) {
            return false;
        }
        else if (getTile(playerBoxPos.x, playerBoxPos.y + playerBoxPos.h) == 1) {
            return false;
        }
        else if (getTile(playerBoxPos.x + playerBoxPos.w, playerBoxPos.y) == 1) {
            return false;
        }
        else if (getTile(playerBoxPos.x + playerBoxPos.w, playerBoxPos.y + playerBoxPos.h) == 1) {
            return false;
        }

        if (playerBoxPos.x + TILE_WIDTH < playerBoxPos.x + playerBoxPos.w) {
            if (getTile(playerBoxPos.x + TILE_WIDTH, playerBoxPos.y) == 1) {
                return false;
            }
            else if (getTile(playerBoxPos.x + TILE_WIDTH, playerBoxPos.y + playerBoxPos.h) == 1) {
                return false;
            }
        }
        
        if (playerBoxPos.y + TILE_HEIGHT < playerBoxPos.y + playerBoxPos.h) {
            if (getTile(playerBoxPos.x, playerBoxPos.y + TILE_HEIGHT) == 1) {
                return false;
            }
            else if (getTile(playerBoxPos.x + playerBoxPos.w, playerBoxPos.y + TILE_HEIGHT) == 1) {
                return false;
            }
        }

        return true;
    }

    int Map::getTile(int xPos, int yPos) {
        int tileX = xPos / TILE_WIDTH;
        int tileY = yPos / TILE_HEIGHT;

        int tilePos = tileX + (tileY * NUM_WIDTH_TILES);

        return mapTiles[tilePos];
    }

    int Map::getTilePos(int xPos, int yPos) {
        int tileX = xPos / TILE_WIDTH;
        int tileY = yPos / TILE_HEIGHT;

        return tileX + (tileY * NUM_WIDTH_TILES);
    }

    SDL_Rect Map::getTileRect(int tilePos) {
        SDL_Rect tileRect;

        tileRect.x = (tilePos % NUM_WIDTH_TILES) * TILE_WIDTH;
        tileRect.w = TILE_WIDTH;

        tileRect.y = (tilePos / NUM_WIDTH_TILES) * TILE_HEIGHT;
        tileRect.h = TILE_HEIGHT;

        return tileRect;
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