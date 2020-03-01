#include "player.h"
#include "custom.h"

Player::Player() {
    playerTexture = NULL;

    deltaVel = PLAYER_BASE_VELOCITY;

    playerWidth = 0;
    playerHeight = 0;

    xPos = 0.0;
    yPos = 0.0;

    updateHitbox();

    angle = 0.0;

    xVel = 0.0;
    yVel = 0.0;

    isMoving = false;

    tickCount = 0;
    currentFrame = 0;
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

void Player::changePosition(float x, float y) {
	xPos = x;
	yPos = y;

    updateHitbox();
}

void Player::changeAngle(double a) {
    angle = a;
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
        //isMoving = false;
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
    // Check if any move key pressed, set to moving
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_s ||
            e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_d) {
            isMoving = true;
        }
    }

    // Check if no moving keys are pressed
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if ((!state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S] &&
          !state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D])) {
        isMoving = false;
        currentFrame = 0;
    }
}

// Maybe check here for invalid movements?
void Player::updatePosition(Map* currentMap) {
    xPos += xVel;
    updateHitbox();

    // Check screen boundaries
    if ((playerHitbox.x - playerHitbox.r < 0) ||
        (playerHitbox.x + playerHitbox.r > SCREEN_WIDTH)) {
        xPos -= xVel;
        updateHitbox();
    }

    if (currentMap != NULL) {
        if (!currentMap->clearPath(playerHitbox)) {
            xPos -= xVel;
            updateHitbox();
        }
    }

    yPos += yVel;
    updateHitbox();
    
    // Check screen boundaries
    if ((playerHitbox.y - playerHitbox.r < 0) ||
        (playerHitbox.y + playerHitbox.r > SCREEN_HEIGHT)) {
        yPos -= yVel;
        updateHitbox();
    }

    if (currentMap != NULL) {
        if (!currentMap->clearPath(playerHitbox)) {
            yPos -= yVel;
            updateHitbox();
        }
    }


    updateHitbox();

}


// Render player, update to render a specific clip of the player sprite
void Player::renderPlayer() {
	SDL_Rect spriteQuad;
    
	spriteQuad.w = playerWidth;
	spriteQuad.h = playerHeight;

    spriteQuad.x = (currentFrame % playerTexture->getRow()) * playerWidth;
	spriteQuad.y = (currentFrame / playerTexture->getCol()) * playerHeight;

	playerTexture->render(xPos, yPos, &spriteQuad, NULL, angle);

    // Extra, maybe change this
    // Draw Hitbox
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawCircle(gRenderer, playerHitbox);
}

// Increment the frame for which frame to render
void Player::incFrame() {
    tickCount++;
    if (tickCount > 6) {
        currentFrame++;
        if (currentFrame >= playerTexture->getFrames()) {
            currentFrame = 0;
        }
		tickCount = 0;
	}
    
}

void Player::turn(int x, int y) {

    //printf("mouse at %d, %d\n", x, y);
    //printf("player center at %f, %f\n", getCenterX(), getCenterY());
    float to_x = x - getCenterX();
    float to_y = y - getCenterY();

    float new_angle = findAngle(to_x, to_y);

    angle = double(new_angle * 180.0/PI) + 270.0;
    //printf("%f\n", angle);
}

void Player::updateHitbox() {
    playerHitbox.x = xPos + playerWidth/2;
    playerHitbox.y = yPos + playerHeight/2;
    playerHitbox.r = PLAYER_SIZE/2;
}

