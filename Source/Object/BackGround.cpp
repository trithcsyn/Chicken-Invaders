#include"BackGround.h"

void Background ::init(SDL_Renderer* renderer){
    backgroundIMG = loadTexture("Source/Assets/Image/background.png", renderer);
    clipBackground.x = 0;
    clipBackground.y = 1200;
    clipBackground.w = SCREEN_WIDTH;
    clipBackground.h = SCREEN_HEIGHT;
}

void Background::render(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, backgroundIMG, &clipBackground, NULL);
    clipBackground.y = (clipBackground.y - SPEED_OF_BACKGROUND + 1200)% 1200;
}
