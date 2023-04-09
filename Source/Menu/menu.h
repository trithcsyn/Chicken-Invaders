#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include"../Manager/Font.h"

class startMenu{
public:
    SDL_Texture *ButtonIMG[3], *highlightIMG, *earthIMG, *logoIMG;
    SDL_Rect play, options, quit;
    bool status;

    void init(SDL_Renderer* renderer);
    void render(SDL_Renderer *renderer);
    void getHighLight(SDL_Renderer* renderer);
};


class Interface{
public:
    SDL_Texture* heart;
    string name;
    int score;
    Text text;
    map<string, int> HighScore;

    void init(SDL_Renderer* renderer);
    void renderScore(SDL_Renderer* renderer);
    void renderHeart(SDL_Renderer* renderer,const int &hp);
};
#endif // MENU_H_INCLUDED
