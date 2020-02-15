#include "player.h"

Player::Player() {
    playerTexture = NULL;

    moveSpeed = PLAYER_MOVESPEED;

    playerWidth = 0;
    playerHeight = 0;

    xPos = 0;
    yPos = 0;
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

void Player::movePlayer() {

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