#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "game.h"
#include "constants.h"
#include "texture.h"
#include "player.h"
#include "map.h"
#include "timer.h"
#include "zone.h"
#include "network.h"

enum GameState {
    MAIN_MENU,
    CONNECT,
    ACTION
};

bool runGame() {

    // Event handler
    SDL_Event e;

    // FPS timer
    GameTimer fpsTimer;
    int framesCounter = 0;
    float avgFPS = 0;
    fpsTimer.start();

    // Cap FPS
    GameTimer fpsCapTimer;

    // Create temp player for test *******
    Player player1;
    player1.loadTexture("./assets/player1.png", 4, 2, 2);
    player1.changePosition(0,0);

    bool isHost = false;

    Map* arena;
    arena = new Map();
    arena->loadMap("src/centralv2.map");
    arena->loadMapTexture("./assets/character_test.png",
                        "./assets/wall.png",
                        "./assets/path.png");

    Zone zone;
    zone.loadZoneTexture("./assets/zoneR.png");
    zone.changeZoneDimensions(150, 150);
    zone.changePosition(SCREEN_WIDTH/2 - 75, 50);

    while(running) {

        // Start timer to cap fps
        fpsCapTimer.start();

        // Poll events
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        printf("Quitting game.\n");
                        running = false;
                        break;
                    case SDLK_c:
                        break;
                    case SDLK_h:
                        break;
                    default:
                        break;
                }
            }
            else if (e.type == SDL_MOUSEMOTION) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                player1.turn(x, y);
            }

            // Player movement handler
            player1.updateVelocity(e);
        }

        // Update player position based on velocity
        player1.updatePosition(arena);

        // FPS Calculation
        avgFPS = framesCounter/(fpsTimer.getTicks()/1000.f);
        if (avgFPS > 2000000) {
            avgFPS = 0;
        }
        framesCounter++;

        if (framesCounter > 60) {
            //printf("Current FPS: %f\n", avgFPS);
            fpsTimer.stop();
            fpsTimer.start();
            framesCounter = 0;
        }

        // Increment player frame
        if (player1.getIsMoving()) {
            player1.incFrame();
        }

        // Clear renderer
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

        arena->renderMap();
        player1.renderPlayer();
        zone.renderZone();

		// Update screen
		SDL_RenderPresent(gRenderer);

        // Cap fps
        if (fpsCapTimer.getTicks() < SCREEN_TICKS_PER_FRAME) {
			SDL_Delay(SCREEN_TICKS_PER_FRAME - fpsCapTimer.getTicks());
		}
	}
    return false;
}