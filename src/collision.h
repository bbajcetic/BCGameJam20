#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>

#include "SDL_shapes.h"

// Check collision between two SDL_Rect objects without rotation
bool isCollisionRectNoRotate(SDL_Rect obj1, SDL_Rect obj2);

// Check collision between two SDL_FCircle objects
bool isCollisionFCircles(SDL_FCircle circle1, SDL_FCircle circle2);

// Check collision between an SDL_Rect (no rotation) and an SDL_FCircle
bool isCollisionFCircleRect(SDL_FCircle circle, SDL_Rect rect);

#endif