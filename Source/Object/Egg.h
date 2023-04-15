#ifndef EGG_H_INCLUDED
#define EGG_H_INCLUDED

#include"Chicken.h"
#include"PlayerShip.h"

class RectEgg{
public:
    SDL_Rect hitBox;
    int vY;

};

class Egg{
public:
    SDL_Texture* eggIMG;
    vector<RectEgg> eggs;

    void init(SDL_Renderer* renderer);
    void add(const std::vector<RectChicken> &chicken);
    void render(SDL_Renderer* renderer);
    bool checkCollision(PlayerShip &player, int &level);
    void add(const BigChicken &boss);
};

#endif // EGG_H
