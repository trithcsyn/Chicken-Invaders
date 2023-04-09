#include"menu.h"




void startMenu::init(SDL_Renderer* renderer){
    ButtonIMG[0] = loadTexture("Source/ASsets/image/menu1.png", renderer);
    ButtonIMG[1] = loadTexture("Source/ASsets/image/menu2.png", renderer);
    ButtonIMG[2] = loadTexture("Source/ASsets/image/menu3.png", renderer);
    earthIMG = loadTexture("Source/ASsets/image/earth.png", renderer);
    logoIMG = loadTexture("Source/Assets/image/logo.png", renderer);
    highlightIMG = loadTexture("Source/ASsets/image/highlight.png", renderer);
    play = {18, 630, 255, 165};
    options = {278, 630, 255, 165};
    quit = {538, 630, 255, 165};
    status = true;
}

void startMenu::render(SDL_Renderer *renderer){
    renderTexture(earthIMG, renderer, 150, 118, 500, 500);
    renderTexture(logoIMG, renderer, 100, 180, 600, 276);
    SDL_RenderCopy(renderer, ButtonIMG[0], NULL, &play);
    SDL_RenderCopy(renderer, ButtonIMG[1], NULL, &options);
    SDL_RenderCopy(renderer, ButtonIMG[2], NULL, &quit);
}

void startMenu::getHighLight(SDL_Renderer* renderer){
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mouse;
    mouse.x = x;
    mouse.y = y;
    if(SDL_PointInRect(&mouse, &play)){
        SDL_RenderCopy(renderer, highlightIMG, NULL, &play);
    }
    if(SDL_PointInRect(&mouse, &options)){
        SDL_RenderCopy(renderer, highlightIMG, NULL, &options);
    }
    if(SDL_PointInRect(&mouse, &quit)){
        SDL_RenderCopy(renderer, highlightIMG, NULL, &quit);
    }
}


void Interface::init(SDL_Renderer* renderer){
        heart = loadTexture("Source/Assets/Image/heart.png", renderer);
        text.init(renderer);
        score = 0;
    }
void Interface::renderScore(SDL_Renderer* renderer){
    static int tempScore = 0;
    if(score > tempScore){
        text.texts[to_string(tempScore)] = nullptr;
        text.texts.erase(to_string(tempScore));
        text.render(renderer, to_string(tempScore += 100), LEFT_EDGE + 115 , 750, 0.5, false);
    }
    else text.render(renderer, to_string(score), LEFT_EDGE + 115 , 750, 0.5, false);
}
void Interface::renderHeart(SDL_Renderer* renderer,const int &hp){
    for(int i = 0; i < hp; i++){
        renderTexture(heart, renderer, LEFT_EDGE + i * 20, SCREEN_HEIGHT - 50, 20, 20);
    }
}
