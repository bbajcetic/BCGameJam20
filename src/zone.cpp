#include <SDL2/SDL.h>

#include "zone.h"

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

    void Zone::updateHitBox() {
        zoneHitBox.x = xPos;
        zoneHitBox.y = yPos;
        zoneHitBox.w = width;
        zoneHitBox.h = height;
    }

    void Zone::renderZone() {
        SDL_SetTextureAlphaMod(zoneTexture->getTexture(), Uint8(100));
        zoneTexture->render(xPos, yPos, &zoneHitBox);
    }