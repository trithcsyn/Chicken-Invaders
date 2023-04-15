#include"Gift.h"

void Gift::init(SDL_Renderer* renderer){
    giftIMG = loadTexture("Source/Assets/Image/gift.png", renderer);
}

void Gift :: render(SDL_Renderer* renderer){
    for(int i = 0; i < (int)gifts.size(); i++){
        if(gifts[i].y >= 800){
            gifts.erase(gifts.begin() + i);
            i--;
            continue;
        }
        SDL_RenderCopy(renderer, giftIMG, NULL, &gifts[i]);
        gifts[i].y += 1;
    }
}

void Gift ::checkCollision(PlayerShip &player, int &level){
    for(int i = 0; i < (int)gifts.size(); i++){
        if(SDL_HasIntersection(&gifts[i], &player.hitBox)){
            gifts.erase(gifts.begin() + i);
            i--;
            level++;
            if(level == 8) level = 7;
            continue;
        }
    }
}
