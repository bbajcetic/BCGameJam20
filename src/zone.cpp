#include <SDL2/SDL.h>

#include "zone.h"
#include "collision.h"
#include "constants.h"



    Zone::Zone() {
        zoneTexture = NULL;
        statusDefaultTexture = NULL;
        statusPlayer1Texture = NULL;
        statusPlayer2Texture = NULL;
        statusBorderTexture = NULL;

        xPos = 0;
        yPos = 0;
        width = 0;
        height = 0;

        statusPlayer1 = 0;
        statusPlayer2 = 0;

        statusUpdateTick = 0;

        yChange = 0;

        updateHitbox();
    }

    Zone::~Zone() {
        free();
    }

    void Zone::free() {
        if (zoneTexture != NULL) {
            zoneTexture->free();
            zoneTexture = NULL;
        }

        if (statusDefaultTexture != NULL) {
            statusDefaultTexture->free();
            statusDefaultTexture = NULL;
        }

        if (statusPlayer1Texture != NULL) {
            statusPlayer1Texture->free();
            statusPlayer1Texture = NULL;
        }

        if (statusPlayer2Texture != NULL) {
            statusPlayer2Texture->free();
            statusPlayer2Texture = NULL;
        }

        if (statusBorderTexture != NULL) {
            statusBorderTexture->free();
            statusBorderTexture = NULL;
        }
    }

    void Zone::loadZoneTexture(std::string zonePath) {
        zoneTexture = new Texture();
        zoneTexture->loadTexture(zonePath, 1, 1, 1);
        SDL_SetTextureAlphaMod(zoneTexture->getTexture(), Uint8(100));
    }

    void Zone::loadStatusTextures(std::string statusPath, std::string statusBorderPath) {
        statusDefaultTexture = new Texture();
        statusDefaultTexture->loadTexture(statusPath, 1, 1, 1);
        SDL_SetTextureColorMod(statusDefaultTexture->getTexture(), 0xFF, 0xFF, 0x00);

        statusPlayer1Texture = new Texture();
        statusPlayer1Texture->loadTexture(statusPath, 1, 1, 1);
        SDL_SetTextureColorMod(statusPlayer1Texture->getTexture(), 0x00, 0xFF, 0x00);

        statusPlayer2Texture = new Texture();
        statusPlayer2Texture->loadTexture(statusPath, 1, 1, 1);
        SDL_SetTextureColorMod(statusPlayer2Texture->getTexture(), 0xFF, 0x00, 0x00);

        statusBorderTexture = new Texture();
        statusBorderTexture->loadTexture(statusBorderPath, 1, 1, 1);
        //SDL_SetTextureColorMod(statusBorderTexture->getTexture(), 0x4C, 0x23, 0x00);
    }

    void Zone::changePosition(int x, int y) {
        xPos = x;
        yPos = y;

        updateHitbox();
    }

    void Zone::changeZoneDimensions(int w, int h) {
        width = w;
        height = h;

        updateHitbox();
    }

    // Update hitbox based on x, y, width, and height parameters
    void Zone::updateHitbox() {
        zoneHitbox.x = xPos;
        zoneHitbox.y = yPos;
        zoneHitbox.w = width;
        zoneHitbox.h = height;
    }

    // Update zone capture status based on players in/out of zone
    void Zone::updateZone(SDL_FCircle player1Hitbox, SDL_FCircle player2Hitbox) {
        // If p1 is in/touching zone
        if (isCollisionFCircleRect(player1Hitbox, zoneHitbox)) {
            // if P2 is in as well
            if (isCollisionFCircleRect(player2Hitbox, zoneHitbox)) {
                // Don't update zone status
                printf("P1 and P2 in\n");
            }
            else {
                // Update zone status in favour of p1
                statusUpdateTick++;
                if (statusUpdateTick > 5) {
                    // Decrease player 2 status if present
                    if (statusPlayer2 > 0) {
                        statusPlayer2--;
                    }
                    // Else, increment player 1 status
                    else {
                        if (statusPlayer1 < 100) {
                            statusPlayer1++;
                        }
                    }
                    statusUpdateTick = 0;
                }
            }
        }
        // Else if p2 is in
        else if (isCollisionFCircleRect(player2Hitbox, zoneHitbox)) {
            // Update zone status in favour of p2
            statusUpdateTick++;
            if (statusUpdateTick > 5) {
                // Decrease player 1 status if present
                if (statusPlayer1 > 0) {
                    statusPlayer1--;
                }
                // Else, increment player 2 status
                else {
                    if (statusPlayer2 < 100) {
                        statusPlayer2++;
                    }
                }
                statusUpdateTick = 0;
            }
        }
    }

    void Zone::renderZone() {
        zoneTexture->render(xPos, yPos, NULL, &zoneHitbox);
    }

    void Zone::renderStatus() {
        SDL_Rect defaultRect, defaultRect2, player1Rect, player1Rect2, player2Rect, player2Rect2;

        // Render default status texture
        if (statusPlayer1 < 100 && statusPlayer2 < 100) {
            defaultRect = {256, yChange, 256, 32};
            defaultRect2 = {256, 0, 256, 0};
            if (yChange <= 688) {
                statusDefaultTexture->render(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT - 48, &defaultRect);
            }
            else if (yChange < 720) {
                defaultRect.h = 720-yChange;
                defaultRect2.h = yChange - 688;
                statusDefaultTexture->render(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT - 48, &defaultRect);
                statusDefaultTexture->render(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT - (16 + (yChange - 688)), &defaultRect2);
            }
        }

        // Render player 1 status texture
        if (statusPlayer1 > 0) {
            player1Rect = {256, yChange, (int)((float)256 * ((float)statusPlayer1 / 100.0)), 32};
            player1Rect2 = {256, 0, (int)((float)256 * ((float)statusPlayer1 / 100.0)), 0};
            if (yChange <= 688) {
                statusPlayer1Texture->render(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT - 48, &player1Rect);
            }
            else if (yChange < 720) {
                player1Rect.h = 720-yChange;
                player1Rect2.h = yChange - 688;
                statusPlayer1Texture->render(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT - 48, &player1Rect);
                statusPlayer1Texture->render(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT - (16 + (yChange - 688)), &player1Rect2);
            }
        }

        // Render player 2 status texture
        if (statusPlayer2 > 0) {
            player2Rect = {256, yChange, (int)((float)256 * ((float)statusPlayer2 / 100.0)), 32};
            player2Rect2 = {256, 0, (int)((float)256 * ((float)statusPlayer2 / 100.0)), 0};
            if (yChange <= 688) {
                statusPlayer2Texture->render(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT - 48, &player2Rect);
            }
            else if (yChange < 720) {
                player2Rect.h = 720-yChange;
                player2Rect2.h = yChange - 688;
                statusPlayer2Texture->render(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT - 48, &player2Rect);
                statusPlayer2Texture->render(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT - (16 + (yChange - 688)), &player2Rect2);
            }
        }

        // Render status border
        statusBorderTexture->render(SCREEN_WIDTH / 2 - 132, SCREEN_HEIGHT - 52);

        yChange++;
        if (yChange >= 720) {
            yChange = 0;
            defaultRect.h = 32;
        }
    }