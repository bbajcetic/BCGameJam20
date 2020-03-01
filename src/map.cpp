#include <fstream>

#include "map.h"
#include "collision.h"

    Map::Map() {
        mapBackground = NULL;
        mapOverlay = NULL;
        tempWall = NULL;
        tempGround = NULL;

        emptyMap();
    }
    Map::~Map() {
        free();
    }

    void Map::free() {
        if (mapBackground != NULL) {
            mapBackground->free();
            mapBackground = NULL;
        }
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

    void Map::loadMapTexture(std::string mapBackgroundPath,
                            std::string mapOverlayPath,
                            std::string wallPath,
                            std::string groundPath) {
        mapBackground = new Texture();
        mapBackground->loadTexture(mapBackgroundPath, 1, 1, 1);

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

    bool Map::clearPath(SDL_FCircle playerHitbox) {        
        int xCheck;
        int yCheck;
        xCheck = playerHitbox.x - playerHitbox.r;
        yCheck = playerHitbox.y - playerHitbox.r;

        // Check all tiles within specified rectangle
        while (xCheck < playerHitbox.x + playerHitbox.r) {
            while (yCheck < playerHitbox.y + playerHitbox.r) {
                // Check if tile is a wall
                if (getTile(xCheck, yCheck) == 1) {
                    // Check if tile collides with player
                    if (isCollisionFCircleRect(playerHitbox, getTileRect(getTilePos(xCheck, yCheck)))) {
                        return false;
                    }
                }
                yCheck = yCheck + TILE_HEIGHT;
            }
            yCheck = playerHitbox.y - playerHitbox.r;
            xCheck = xCheck + TILE_WIDTH;
        }

        // Check right x
        xCheck = playerHitbox.x + playerHitbox.r;
        yCheck = playerHitbox.y - playerHitbox.r;
        while (yCheck < playerHitbox.y + playerHitbox.r) {
            // Check if tile is a wall
            if (getTile(xCheck, yCheck) == 1) {
                // Check if tile collides with player
                if (isCollisionFCircleRect(playerHitbox, getTileRect(getTilePos(xCheck, yCheck)))) {
                    return false;
                }
            }
            yCheck = yCheck + TILE_HEIGHT;
        }

        // Check bottom y
        xCheck = playerHitbox.x - playerHitbox.r;
        yCheck = playerHitbox.y + playerHitbox.r;
        while (xCheck < playerHitbox.x + playerHitbox.r) {
            // Check if tile is a wall
            if (getTile(xCheck, yCheck) == 1) {
                // Check if tile collides with player
                if (isCollisionFCircleRect(playerHitbox, getTileRect(getTilePos(xCheck, yCheck)))) {
                    return false;
                }
            }
            xCheck = xCheck + TILE_WIDTH;
        }

        // Check bottom right
        xCheck = playerHitbox.x + playerHitbox.r;
        yCheck = playerHitbox.y + playerHitbox.r;
        if (getTile(xCheck, yCheck) == 1) {
            // Check if tile collides with player
            if (isCollisionFCircleRect(playerHitbox, getTileRect(getTilePos(xCheck, yCheck)))) {
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

        // Draw background
        mapBackground->render(0,0);

        // Draw walls and stuff maybe
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

        // Draw overlay
        mapOverlay->render(0,0);
    }