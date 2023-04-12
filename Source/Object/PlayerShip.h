#ifndef PLAYERSHIP_H_INCLUDED
#define PLAYERSHIP_H_INCLUDED

#include"../Manager/SDL_utils.h"
#include"../Manager/game_constans.h"
#include"../Menu/menu.h"
class PlayerShip{
public:
    SDL_Texture* smallExplosion[2];
    SDL_Texture* explosionIMG[5];
    SDL_Texture* playerIMG[5];
    SDL_Rect ship;
    SDL_Rect hitBox;
    int hp;
    bool getdame;

    void init(SDL_Renderer* renderer, int x_, int y_, int hp_);
    void render(SDL_Renderer* renderer);
    void updatePos();
    bool renderGetDame(SDL_Renderer *renderer);
    bool renderDead(SDL_Renderer* renderer, Interface &itf, SDL_Event &e);
};

#endif // PLAYERSHIP_H_INCLUDED
