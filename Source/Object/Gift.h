#ifndef GIFT_H_INCLUDED
#define GIFT_H_INCLUDED

#include"PlayerShip.h"

class Gift{
public:
    SDL_Texture* giftIMG;
    std::vector<SDL_Rect> gifts;

    void init(SDL_Renderer* Renderer);
    void render(SDL_Renderer* Renderer);
    void checkCollision(PlayerShip &player, int &level);
};
#endif // GIFT_H
