#ifndef SDL_SHAPES_H
#define SDL_SHAPES_H

#include <SDL2/SDL.h>

/* Extra shape types */

typedef struct SDL_Circle {
    int x, y;
    int r;
} SDL_Circle;

typedef struct SDL_FCircle {
    float x, y;
    float r;
} SDL_FCircle;

/* Extra shape rendering */

// Draw a circle on the current rendering target
int SDL_RenderDrawCircle(SDL_Renderer* renderer, SDL_FCircle circle);

#endif