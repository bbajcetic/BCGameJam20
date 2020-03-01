#include <cmath>

#include "collision.h"

// Check collision between two SDL_Rect objects without rotation
bool isCollisionRectNoRotate(SDL_Rect obj1, SDL_Rect obj2) {
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

// Check collision between two SDL_FCircle objects
bool isCollisionFCircles(SDL_FCircle circle1, SDL_FCircle circle2) {
    float dx = circle1.x - circle2.x;
    float dy = circle1.y - circle2.y;
    
    float dist = sqrt(dx*dx + dy*dy);

    if (dist < (circle1.r + circle2.r)) {
        return true;
    }
    return false;
}

// Check collision between an SDL_Rect (no rotation) and an SDL_FCircle
bool isCollisionFCircleRect(SDL_FCircle circle, SDL_Rect rect) {
    float xEdge = circle.x;
    float yEdge = circle.y;

    // If circle is to left of rect
    if (circle.x < (float)rect.x) {
        xEdge = (float)rect.x;
    }
    // Else if circle is to right of rect
    else if (circle.x > (float)(rect.x + rect.w)) {
        xEdge = (float)(rect.x + rect.w);
    }

    // If circle to above rect
    if (circle.y < (float)rect.y) {
        yEdge = (float)rect.y;
    }
    // Else if circle is below rect
    else if (circle.y > (float)(rect.y + rect.h)) {
        yEdge = (float)(rect.y + rect.h);
    }

    float dx = circle.x - xEdge;
    float dy = circle.y - yEdge;

    float dist = sqrt(dx*dx + dy*dy);

    if (dist <= circle.r) {
        return true;
    }
    return false;
}