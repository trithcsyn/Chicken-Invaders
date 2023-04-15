#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include"../Manager/Font.h"

class startMenu{
public:
    SDL_Texture *ButtonIMG[3], *highlightIMG, *earthIMG, *logoIMG;
    SDL_Rect play, options, quit;

    void init(SDL_Renderer* renderer);
    void render(SDL_Renderer *renderer);
    void getHighLight(SDL_Renderer* renderer);
    void check(SDL_Event &e, bool &play, bool &startMenu, bool &quit);
};


class Interface{
public:
    SDL_Texture* heart;
    int score;
    Text text;
    int highScore;
    int wave;

    void init(SDL_Renderer* renderer);
    void renderScore(SDL_Renderer* renderer);
    void renderHeart(SDL_Renderer* renderer,const int &hp);
    void saveScore();
    void renderHighScore(SDL_Renderer *renderer);
};
#endif // MENU_H_INCLUDED
