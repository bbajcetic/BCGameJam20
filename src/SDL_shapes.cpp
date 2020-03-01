#include "SDL_shapes.h"

void drawSubCircle(SDL_Renderer* renderer, int x_center, int y_center, int x, int y);

// Draw a circle on the current rendering target
// Using Bresenham's algorithm found here:
// https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
int SDL_RenderDrawCircle(SDL_Renderer* renderer, SDL_FCircle circle) {
    // Call SDL_RenderDrawPoint(renderer, x, y);
    int x = 0;
    int y = (int)circle.r;
    int d = 3 - 2*circle.r;

    drawSubCircle(renderer, (int)circle.x, int(circle.y), x, y);
    while (y >= x) {
        x++;

        if (d > 0) {
            y--;
            d = d + (4*(x-y)) + 10;
        }
        else {
            d = d + (4*x) + 6;
        }
        drawSubCircle(renderer, (int)circle.x, (int)circle.y, x, y);
    }
}
// Helper function for SDL_RenderDrawCircle
void drawSubCircle(SDL_Renderer* renderer, int x_center, int y_center, int x, int y) {
    SDL_RenderDrawPoint(renderer, x_center+x, y_center+y);
    SDL_RenderDrawPoint(renderer, x_center-x, y_center+y);
    SDL_RenderDrawPoint(renderer, x_center+x, y_center-y);
    SDL_RenderDrawPoint(renderer, x_center-x, y_center-y);

    SDL_RenderDrawPoint(renderer, x_center+y, y_center+x);
    SDL_RenderDrawPoint(renderer, x_center-y, y_center+x);
    SDL_RenderDrawPoint(renderer, x_center+y, y_center-x);
    SDL_RenderDrawPoint(renderer, x_center-y, y_center-x);
}