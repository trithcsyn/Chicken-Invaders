#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include"SDL_ttf.h"
#include"game_constans.h"
#include"SDL_utils.h"
#include<map>

class Text{
    public:
    TTF_Font *font;
    map<string, SDL_Texture*> texts;

    SDL_Texture* getTexture(const string &textLine, SDL_Renderer* renderer );
    void init(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, string textLine ,const int &x,const int &y,const double &k, bool flash);
};


#endif // FONT_H_INCLUDED
