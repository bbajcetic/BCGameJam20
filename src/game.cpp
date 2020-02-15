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

bool runGame() {

    // Event handler
    SDL_Event e;

    // Create temp player for test *******
    Player player1;
    player1.loadTexture("./assets/example.png", 1, 1, 1);
    player1.changePosition(50,50);

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
        player1.updatePosition();

        // Clear renderer
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

        player1.renderPlayer();

		// Update screen
		SDL_RenderPresent(gRenderer);
    }
    return false;
}