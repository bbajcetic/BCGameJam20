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

    // Temporarily initialize 2 players here
    Player player1;
    player1.loadTexture("./assets/player1.png", 4, 2, 2);
    player1.changePosition(0,0);

    Player player2;
    player2.loadTexture("./assets/player2.png", 4, 2, 2);
    player2.changePosition(1250, 650);

    // Player send and recieve buffers
    char sendData[1024] = {0};
    char recvData[1024] = {0};

    // Set current state and init host
    int currentState = MAIN_MENU;
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
                        if (currentState == MAIN_MENU) {
                            isHost = false;
                            Network_initialize(Connection::Client);
                            currentState = ACTION;
                        }
                        break;
                    case SDLK_h:
                        if (currentState == MAIN_MENU) {
                            isHost = true;
                            Network_initialize(Connection::Server);
                            currentState = ACTION;
                        }
                        break;
                    default:
                        break;
                }
            }
            else if (e.type == SDL_MOUSEMOTION) {
                if (currentState == ACTION) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                    if (isHost) {
                        player1.turn(x, y);
                    }
                    else {
                        player2.turn(x, y);
                    }
                }
            }
            // Player movement handler
            if (currentState == ACTION) {
                if (isHost) {
                    player1.updateVelocity(e);
                }
                else {
                    player2.updateVelocity(e);
                }
            }
        }

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

        // Update player positions and frames if in ACTION state
        if (currentState == ACTION) {
            if (isHost) {
                // Update player position based on velocity
                player1.updatePosition(arena);

                // Increment player frame
                if (player1.getIsMoving()) {
                    player1.incFrame();
                }
            }
            else {
                // Update player position based on velocity
                player2.updatePosition(arena);

                // Increment player frame
                if (player2.getIsMoving()) {
                    player2.incFrame();
                }
            }
        }

        // Clear renderer
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);


        // Draw menu screen
        if (currentState == MAIN_MENU) {

        }
        // Draw players, map, zones, etc.
        else if (currentState == ACTION) {

            // If host (player 1), send p1 data and recieve p2
            if (isHost) {
                sprintf(sendData, "p1.%d.%d.%f", player1.getxPos(),
                        player1.getyPos(), player1.getAngle());
                Network_update(sendData, recvData, strlen(recvData));

                int newX = 0;
                int newY = 0;
                double newAngle = 0.0;

                char * token = strtok(recvData, ".");
                token = strtok(NULL, ".");
                newX = atoi(token);
                token = strtok(NULL, ".");
                newY = atoi(token);
                token = strtok(NULL, ".");
                newAngle = strtod(token, NULL);

                player2.changePosition(newX, newY);
                player2.changeAngle(newAngle);

            }
            // If not host (player 2), send p2 data and recieve p1
            else {
                sprintf(sendData, "p2.%d.%d.%f", player2.getxPos(),
                        player2.getyPos(), player2.getAngle());
                Network_update(sendData, recvData, strlen(recvData));

                int newX = 0;
                int newY = 0;
                double newAngle = 0.0;

                char * token = strtok(recvData, ".");
                token = strtok(NULL, ".");
                newX = atoi(token);
                token = strtok(NULL, ".");
                newY = atoi(token);
                token = strtok(NULL, ".");
                newAngle = strtod(token, NULL);

                player1.changePosition(newX, newY);
                player1.changeAngle(newAngle);
            }

            arena->renderMap();
            player1.renderPlayer();
            player2.renderPlayer();
            zone.renderZone();
        }
        

		// Update screen
		SDL_RenderPresent(gRenderer);

        // Cap fps
        if (fpsCapTimer.getTicks() < SCREEN_TICKS_PER_FRAME) {
			SDL_Delay(SCREEN_TICKS_PER_FRAME - fpsCapTimer.getTicks());
		}
	}
    return false;
}