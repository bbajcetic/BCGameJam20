#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "constants.h"
#include "game.h"
#include "network.h"


/* Functions */

// Initialize SDL
bool initSDL();

// Free memory, quit SDL
void quitSDL();


/* Globals */

// Rendering window
SDL_Window* gWindow = NULL;

// Renderer
SDL_Renderer* gRenderer = NULL;

// Game loop
bool running = true;

int main(int argc, char *argv[]) {
    if (!initSDL()) {
        printf("Initialization failed!\n");
    }
    else {
        // Game loop
        runGame();
        printf("Game ending\n");
    }

    Network_clean();
    quitSDL();
    return 0;
}


/* Function Definitions */

// Initialize SDL
bool initSDL() {
	// Init flag
	bool loaded = true;

	// Initialization
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL initialization failed! SDL_Error: %s\n", SDL_GetError());
		loaded = false;
	}
	else {
		// Create window
		gWindow = SDL_CreateWindow("BC Game Jam 2020 Prevail", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window creation failed! SDL_Error: %s\n", SDL_GetError());
			loaded = false;
		}
		else {
			// Create Renderer
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				printf("Renderer creation failed! SDL Error: %s\n", SDL_GetError());
				loaded = false;
			}
			else 	{
				// Initialize image loading
				int imgFlag = IMG_INIT_JPG | IMG_INIT_PNG;
				if (!IMG_Init(imgFlag) & imgFlag) {
					printf("SDL_Image initialization failed! SDL_image Error: %s\n", IMG_GetError());
					loaded = false;
				}

				// Initialize SDL Mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					printf("SDL_Mixer initialization failed! SDL_mixer Error: %s\n", Mix_GetError());
					loaded = false;
				}
			}
		}
	}
	return loaded;
}

// Free memory, quit SDL
void quitSDL() {
	// Free and Destroy
    // Textures
    // Music

	// Destroy renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
