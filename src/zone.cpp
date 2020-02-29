#include <SDL2/SDL.h>

#include "zone.h"
#include "collision.h"

    Zone::Zone() {
        zoneTexture = NULL;

        xPos = 0;
        yPos = 0;
        width = 0;
        height = 0;

        updateHitBox();
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

        updateHitBox();
    }

    void Zone::changeZoneDimensions(int w, int h) {
        width = w;
        height = h;

        updateHitBox();
    }

    // Update hitbox based on x, y, width, and height parameters
    void Zone::updateHitBox() {
        zoneHitBox.x = xPos;
        zoneHitBox.y = yPos;
        zoneHitBox.w = width;
        zoneHitBox.h = height;
    }

    // Update zone capture status based on players in/out of zone
    void Zone::updateZone(SDL_Rect player1HitBox, SDL_Rect player2HitBox) {
        // If p1 is in/touching zone
        if (isCollisionRectNoRotate(player1HitBox, zoneHitBox)) {
            // if P2 is in as well
            if (isCollisionRectNoRotate(player2HitBox, zoneHitBox)) {
                // Don't update zone status
                printf("P1 and P2 in\n");
            }
            else {
                // Update zone status in favour of p1
                printf("P1 in\n");
            }
        }
        // Else if p2 is in
        else if (isCollisionRectNoRotate(player2HitBox, zoneHitBox)) {
            // Update zone status in favour of p2
            printf("P2 in\n");
        }
    }

    void Zone::renderZone() {
        zoneTexture->render(xPos, yPos, NULL, &zoneHitBox);
    }