#include "collision.h"

// Check collision between two SDL_Rect objects without rotation
bool isCollision_nonRotate(SDL_Rect obj1, SDL_Rect obj2) {
    int minAx = obj1.x;
    int maxAx = obj1.x + obj1.w;
    int minAy = obj1.y;
    int maxAy = obj1.y + obj1.h;

    int minBx = obj2.x;
    int maxBx = obj2.x + obj2.w;
    int minBy = obj2.y;
    int maxBy = obj2.y + obj2.h;

    /* x check */
    if (minAx <= maxBx && maxAx >= minBx) {
        /* y check */
        if (minAy <= maxBy && maxAy >= minBy) {
            return true;
        }
    }
    return false;
}