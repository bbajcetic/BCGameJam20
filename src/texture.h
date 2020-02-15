#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

// Globals
extern SDL_Renderer* gRenderer;

class Texture {
public:
	// Constructor
	Texture();

	// Destructor
	~Texture();

	// Load image
	bool loadTexture(std::string texturePath, int frames, int rows, int cols);

	// Free texture
	void free();

	// Render texture at specified location
	void render(int x, int y, SDL_Rect* clip = NULL, SDL_Rect* dest = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Get texture dimensions
	int getWidth();
	int getHeight();

	// Get sprite information
	int getFrames();
	int getRow();
	int getCol();

private:
	// Texture
	SDL_Texture* gTexture;

	// Dimensions
	int textureWidth;
	int textureHeight;

	// Sprite information
	int numFrames;
	int numRow;
	int numCol;
};

#endif