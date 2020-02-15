#include "texture.h"

// Constructor
Texture::Texture() {
	gTexture = NULL;

	textureWidth = 0;
	textureHeight = 0;

	numFrames = 0;
	numRow = 0;
	numCol = 0;
}

// Destructor
Texture::~Texture() {
	free();
}

// Load texture
bool Texture::loadTexture(std::string texturePath, int frames, int rows, int cols) {
	// Free old texture
	free();

	// Texture to load
	SDL_Texture* newTexture = NULL;

	// Load surface
	SDL_Surface* newSurface = IMG_Load(texturePath.c_str());
	if (newSurface == NULL) {
		printf("Loading image failed! SDL_image Error: %s\n", IMG_GetError());
	}
	else {
		// Set Color Key
		SDL_SetColorKey(newSurface, SDL_FALSE, SDL_MapRGB(newSurface->format, 0x2a, 0xaa, 0x33));

		// Create texture
		newTexture = SDL_CreateTextureFromSurface(gRenderer, newSurface);

		if (newTexture == NULL) {
			printf("Texture creation failed! SDL Error: %s\n", SDL_GetError());
		}
		else {
			// Set dimensions
			textureWidth = newSurface->w;
			textureHeight = newSurface->h;
		}

		// Free surface
		SDL_FreeSurface(newSurface);
	}

	gTexture = newTexture;

	numFrames = frames;
	numRow = rows;
	numCol = cols;

	return gTexture != NULL;
}

// Free texture
void Texture::free() {
	// Free if texture
	if (gTexture != NULL) {
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
		textureWidth = 0;
		textureHeight = 0;
	}
}

// Render texture at specified location
void Texture::render(int x, int y, SDL_Rect* clip, SDL_Rect* dest, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad;
	if (dest == NULL) {
		renderQuad = {x, y, textureWidth, textureHeight};

		if (clip != NULL) {
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}
	}
	else {
		renderQuad = *dest;
	}

	SDL_RenderCopyEx(gRenderer, gTexture, clip, &renderQuad, angle, center, flip);
}

// Get dimensions of texture
int Texture::getWidth() {
	return textureWidth;
}
int Texture::getHeight() {
	return textureHeight;
}

// Get sprite information
int Texture::getFrames() {
	return numFrames;
}
int Texture::getRow() {
	return numRow;
}
int Texture::getCol() {
	return numCol;
}