#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include"../Manager/game_constans.h"
#include"../Manager/SDL_utils.h"
class Background{
public:
    SDL_Texture* backgroundIMG;
    SDL_Rect clipBackground;

    void init(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
};

#endif
