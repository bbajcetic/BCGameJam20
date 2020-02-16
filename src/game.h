#ifndef GAME_H
#define GAME_H

// Globals
extern SDL_Renderer* gRenderer;
extern SDL_Texture* gCurrentTexture;
extern bool running;

bool runGame();
void networkUpdate(char* send_buf, char* recv_buf, int recv_size);
void updateOpponentState();

#endif
