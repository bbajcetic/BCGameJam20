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

bool runGame() {

    // Event handler
    SDL_Event e;

    // Create temp player for test *******
    Player player1;
    player1.loadTexture("./assets/character_test.png", 9, 3, 3);
    player1.changePosition(0,0);

    Map* arena;
    arena = new Map();
    arena->loadMap("src/centralv2.map");
    arena->loadMapTexture("./assets/character_test.png",
                        "./assets/wall.png",
                        "./assets/path.png");

    while(running) {

        // Poll events
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        printf("Quitting game.\n");
                        running = false;
                        break;
                    default:
                        break;
                }
            }

            // Player movement handler
            player1.updateVelocity(e);
        }

        // Update player position based on velocity
        player1.updatePosition(arena);

        // Clear renderer
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

        arena->renderMap();
        player1.renderPlayer();

		// Update screen
		SDL_RenderPresent(gRenderer);
    }
    return false;
}