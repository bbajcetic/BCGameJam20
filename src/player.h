#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "texture.h"
#include "constants.h"
#include "map.h"

class Player {
public:
	Player();
	~Player();

	void loadTexture(std::string texturePath, int frames, int rows, int cols);
	void free();

	void changePosition(int x, int y);
    void updateVelocity(SDL_Event& e);
    void updatePosition(Map* currentMap);

	void renderPlayer();

	int getMoveSpeed();
	int getPlayerDireciton();


private:
	Texture* playerTexture;

	int deltaVel;

	int playerWidth;
	int playerHeight;

	int xPos;
	int yPos;

    int xVel;
    int yVel;
};

#endif