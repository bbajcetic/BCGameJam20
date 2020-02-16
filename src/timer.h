#pragma once

#include <SDL2/SDL.h>

class GameTimer {
public:
	GameTimer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isRunning();
	bool isPaused();
private:
	Uint32 ticksAtStart;
	Uint32 ticksAtPause;

	bool running;
	bool paused;
};