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

    // Create temp texture for test
    Texture* exampleTex = new Texture();
    exampleTex->loadTexture("./assets/example.png", 1, 1, 1);

    while (running) {
        // Clear renderer
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

        exampleTex->render(10,10);

		// Update screen
		SDL_RenderPresent(gRenderer);
    }
    return false;
}