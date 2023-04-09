#ifndef CHICKEN_H_INCLUDED
#define CHICKEN_H_INCLUDED

#include"../Menu/menu.h"
#include"PlayerShip.h"
#include"Bullet.h"


class RectChicken{
public:
    SDL_Rect hitBox;
    int ani;
    int hp;
};

class Chicken{
public:
    SDL_Texture* chickenIMG[10];
    SDL_Texture* chickenExIMG[3];
    std::vector<RectChicken> chicken;
    std::vector<RectChicken> deadChicken;
    const int w = 104, h = 82;

    int hp, vx;
    int adding;


    void init(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, std::vector<SDL_Rect> &gifts, Interface &Itf);
    void renderDead(SDL_Renderer* renderer);
    bool checkCollision(Bullet &bullets);
    bool checkCollision(PlayerShip &player);
    void add();

};
#endif // CHICKEN_H
