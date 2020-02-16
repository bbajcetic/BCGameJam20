#include "player.h"

Player::Player() {
    playerTexture = NULL;

    deltaVel = PLAYER_VELOCITY;

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
            case SDLK_w:
                yVel -= deltaVel;
                break;
            case SDLK_s:
                yVel += deltaVel;
                break;
            case SDLK_a:
                xVel -= deltaVel;
                break;
            case SDLK_d:
                xVel += deltaVel;
                break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch( e.key.keysym.sym )
        {
            case SDLK_w:
                yVel += deltaVel;
                break;
            case SDLK_s:
                yVel -= deltaVel;
                break;
            case SDLK_a:
                xVel += deltaVel;
                break;
            case SDLK_d:
                xVel -= deltaVel;
                break;
        }
    }

}

// Maybe check here for invalid movements?
void Player::updatePosition(Map* currentMap) {
    SDL_Rect playerPositionBox;
    SDL_Rect mapTileBox;

    xPos += xVel;
    // Check screen boundaries
    if (xPos + playerWidth > SCREEN_WIDTH) {
        xPos = SCREEN_WIDTH - playerWidth;
    }
    if (xPos < 0) {
        xPos = 0;
    }

    if (currentMap != NULL) {
        playerPositionBox.x = xPos;
        playerPositionBox.y = yPos;
        playerPositionBox.w = playerWidth;
        playerPositionBox.h = playerHeight;
        if (!currentMap->clearPath(playerPositionBox)) {
            mapTileBox = currentMap->getTileRect(currentMap->getTilePos(xPos, yPos));
            xPos -= xVel;
        }
    }

    yPos += yVel;
    // Check screen boundaries
    if (yPos + playerHeight > SCREEN_HEIGHT) {
        yPos = SCREEN_HEIGHT - playerHeight;
    }
    if (yPos < 0) {
        yPos = 0;
    }
    if (currentMap != NULL) {
        playerPositionBox.x = xPos;
        playerPositionBox.y = yPos;
        playerPositionBox.w = playerWidth;
        playerPositionBox.h = playerHeight;
        if (!currentMap->clearPath(playerPositionBox)) {
            yPos -= yVel;
        }
    }

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