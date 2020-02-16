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

        // Update hitbox based on x, y, width, and height parameters
        void updateHitBox();

        // Update zone capture status based on players in/out of zone
        void updateZone(SDL_Rect player1HitBox, SDL_Rect player2HitBox);


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