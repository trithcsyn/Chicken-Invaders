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
    int status;
    int countAdd;


    void init(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, std::vector<SDL_Rect> &gifts, Interface &Itf);
    void renderDead(SDL_Renderer* renderer);
    void checkCollision(Bullet &bullets);
    bool checkCollision(PlayerShip &player);
    void add();

};

class BigChicken{
public:
    SDL_Texture* bigChickenIMG[18];
    SDL_Texture* explosion[9];
    int hp;
    SDL_Rect hitBox;
    int status;
    double phi;

    void init(SDL_Renderer* renderer);
    void add(Interface &itf);
    void generatePos();
    void render(SDL_Renderer *renderer, Interface &itf);
    void checkCollision(Bullet &bullets, PlayerShip &player, Interface &itf);
    bool renderDead(SDL_Renderer *renderer);


};
#endif // CHICKEN_H
