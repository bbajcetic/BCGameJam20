#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>

// Check collision between two SDL_Rect objects without rotation
bool isCollision_nonRotate(SDL_Rect obj1, SDL_Rect obj2);

#endif