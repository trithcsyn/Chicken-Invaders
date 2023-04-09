#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED


#include"PlayerShip.h"
#include"../Manager/game_constans.h"
#include"../Manager/SDL_utils.h"
class Bullet{
public:
    SDL_Texture* bulletIMG[3];


    std::vector<SDL_Rect> bullet1;
    std::vector<SDL_Rect> bullet2;
    std::vector<SDL_Rect> bullet3;

    bool adding;
    int level;

    void init(SDL_Renderer* renderer);
    void add(PlayerShip &player);
    void render(SDL_Renderer* renderer);
};
#endif
