#include"Font.h"

SDL_Texture* Text::getTexture(const string &textLine, SDL_Renderer* renderer ){
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, textLine.c_str(), WHITE_COLOR);
        SDL_Texture* pTex = SDL_CreateTextureFromSurface(renderer, textSurface);
        textSurface = NULL;
        delete textSurface;
        return pTex;
    }

void Text::init(SDL_Renderer* renderer){
        TTF_Init();
        font = TTF_OpenFont("Source/Assets/font/.ttf", 50);

    }

void Text::render(SDL_Renderer* renderer, string textLine ,const int &x,const int &y,const double &k, bool flash){
    if(texts.find(textLine) == texts.end()){
         texts.insert( make_pair(textLine, getTexture(textLine, renderer)) );
    }
    static int fl = 0;
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texts[textLine], NULL, NULL, &dst.w, &dst.h);
    dst.w *= k;
    dst.h *= k;
    if(flash){
        if( (fl++)%30 >= 15 ){
            SDL_RenderCopy(renderer, texts[textLine], NULL, &dst);
        }
    }
    else SDL_RenderCopy(renderer, texts[textLine], NULL, &dst);
}

