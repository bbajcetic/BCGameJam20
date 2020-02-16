#include <SDL2/SDL.h>

#include "timer.h"

GameTimer::GameTimer() {
	ticksAtStart = 0;
	ticksAtPause = 0;

	running = false;
	paused = false;
}

void GameTimer::start() {
	running = true;
	paused = false;

	ticksAtStart = SDL_GetTicks();
	ticksAtPause = 0;
}

void GameTimer::stop() {
	running = false;
	paused = false;

	ticksAtStart = 0;
	ticksAtPause = 0;
}

void GameTimer::pause() {
	if (running && !paused) {
		paused = true;

		ticksAtPause = SDL_GetTicks() - ticksAtStart;
		ticksAtStart = 0;
	}
}

void GameTimer::unpause() {
	if (running && paused) {
		paused = false;

		ticksAtStart = SDL_GetTicks() - ticksAtPause;
		ticksAtPause = 0;
	}
}

Uint32 GameTimer::getTicks() {
	if (running) {
		if (paused) {
			return ticksAtPause;
		}
		else {
			return SDL_GetTicks() - ticksAtStart;
		}
	}
	return 0;
}

bool GameTimer::isRunning() {
	return running;
}

bool GameTimer::isPaused() {
	return paused;
}
