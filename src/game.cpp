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

bool runGame() {

    // Event handler
    SDL_Event e;

    // Create temp texture for test
    Texture* exampleTex = new Texture();
    exampleTex->loadTexture("./assets/example.png", 1, 1, 1);

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
        }

        // Clear renderer
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

        exampleTex->render(10,10);

		// Update screen
		SDL_RenderPresent(gRenderer);
    }
    return false;
}