#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "texture.h"
#include "constants.h"
#include "map.h"
#include "SDL_shapes.h"

class Player {
public:
	Player();
	~Player();

	void loadTexture(std::string texturePath, int frames, int rows, int cols);
	void free();

    // Setters for position and angle
	void changePosition(float x, float y);
    void changeAngle(double a);

    void updateVelocity(SDL_Event& e);

    // Update the position based on velocity and check
    // for invalid moves like walls and borders
    void updatePosition(Map* currentMap);

	void renderPlayer();

	int getMoveSpeed();
	int getPlayerDireciton();

    // Increment current frame
    void incFrame();

    void turn(int x, int y);

    // Update hitbox based on x, y, width, and height
    // Change probably since we want it smaller then sprite size
    void updateHitbox();

    float getxPos() {return xPos;}
    float getyPos() {return yPos;}
    double getAngle() {return angle;}

    // Get center values
    float getCenterX() {return float(xPos) + float(playerWidth)/2.0;}
    float getCenterY() {return float(yPos) + float(playerHeight)/2.0;}

    bool getIsMoving() {return isMoving;}

    SDL_FCircle getPlayerHitbox() {return playerHitbox;}


private:
	Texture* playerTexture;

	float deltaVel;

	int playerWidth;
	int playerHeight;

    SDL_FCircle playerHitbox;

	float xPos;
	float yPos;

    double angle;

    float xVel;
    float yVel;

    bool isMoving;

    // Used to determine which frame in the animation to render
    int tickCount;
    int currentFrame;
};

#endif