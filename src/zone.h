#ifndef ZONE_H
#define ZONE_H

#include <string>

#include "texture.h"

class Zone {
    public:
        Zone();
        ~Zone();

        void free();

        void loadZoneTexture(std::string zonePath);

        void changePosition(int x, int y);
        void changeZoneDimensions(int w, int h);

        void updateHitBox();

        void renderZone();
    private:
        Texture* zoneTexture;

        SDL_Rect zoneHitBox;

        int xPos;
        int yPos;

        int width;
        int height;        
};

#endif