#ifndef ZONE_H
#define ZONE_H

#include <string>

#include "texture.h"
#include "SDL_shapes.h"

class Zone {
    public:
        Zone();
        ~Zone();

        void free();

        void loadZoneTexture(std::string zonePath);
        void loadStatusTextures(std::string statusPath, std::string statusBorderPath);

        void changePosition(int x, int y);
        void changeZoneDimensions(int w, int h);

        // Update hitbox based on x, y, width, and height parameters
        void updateHitbox();

        // Update zone capture status based on players in/out of zone
        void updateZone(SDL_FCircle player1Hitbox, SDL_FCircle player2Hitbox);


        void renderZone();
        void renderStatus();
    private:
        Texture* zoneTexture;
        Texture* statusDefaultTexture;
        Texture* statusPlayer1Texture;
        Texture* statusPlayer2Texture;
        Texture* statusBorderTexture;

        SDL_Rect zoneHitbox;

        int xPos;
        int yPos;

        int width;
        int height;

        // Tick count for how often to update status when inside a zone
        int statusUpdateTick;

        int statusPlayer1;
        int statusPlayer2;

        // Used to change how to render zone status bars
        int yChange;
};

#endif