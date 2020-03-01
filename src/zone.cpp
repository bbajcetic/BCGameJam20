#include <SDL2/SDL.h>

#include "zone.h"
#include "collision.h"

    Zone::Zone() {
        zoneTexture = NULL;

        xPos = 0;
        yPos = 0;
        width = 0;
        height = 0;

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
    }

    void Zone::loadZoneTexture(std::string zonePath) {
        zoneTexture = new Texture();
        zoneTexture->loadTexture(zonePath, 1, 1, 1);
        SDL_SetTextureAlphaMod(zoneTexture->getTexture(), Uint8(100));
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
                printf("P1 in\n");
            }
        }
        // Else if p2 is in
        else if (isCollisionFCircleRect(player2Hitbox, zoneHitbox)) {
            // Update zone status in favour of p2
            printf("P2 in\n");
        }
    }

    void Zone::renderZone() {
        zoneTexture->render(xPos, yPos, NULL, &zoneHitbox);
    }