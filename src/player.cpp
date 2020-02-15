#include "player.h"

Player::Player() {
    playerTexture = NULL;

    velocity = PLAYER_VELOCITY;

    playerWidth = 0;
    playerHeight = 0;

    xPos = 0;
    yPos = 0;

    xVel = 0;
    yVel = 0;
}

Player::~Player() {
	free();
}

void Player::loadTexture(std::string texturePath, int frames, int rows, int cols) {
	playerTexture = new Texture();
	playerTexture->loadTexture(texturePath, frames, rows, cols);

	playerWidth = playerTexture->getWidth() / playerTexture->getRow();
	playerHeight = playerTexture->getHeight() / playerTexture->getCol();
}

void Player::free() {
    playerTexture->free();
    playerTexture = NULL;
}

void Player::changePosition(int x, int y) {
	xPos = x;
	yPos = y;
}

void Player::updateVelocity(SDL_Event& e) {
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {

        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                yVel -= velocity;
                break;
            case SDLK_DOWN:
                yVel += velocity;
                break;
            case SDLK_LEFT:
                xVel -= velocity;
                break;
            case SDLK_RIGHT:
                xVel += velocity;
                break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                yVel += velocity;
                break;
            case SDLK_DOWN:
                yVel -= velocity;
                break;
            case SDLK_LEFT:
                xVel += velocity;
                break;
            case SDLK_RIGHT:
                xVel -= velocity;
                break;
        }
    }

}

// Maybe check here for invalid movements?
void Player::updatePosition() {
    xPos += xVel;
    yPos += yVel;
}


// Render player, update to render a specific clip of the player sprite
void Player::renderPlayer() {
	SDL_Rect spriteQuad;

	spriteQuad.w = playerWidth;
	spriteQuad.h = playerHeight;
    spriteQuad.x = 0;
	spriteQuad.y = 0;

	playerTexture->render(xPos, yPos, &spriteQuad);
}