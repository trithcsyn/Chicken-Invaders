#include"Egg.h"

void Egg::init(SDL_Renderer* renderer){
    eggIMG = loadTexture("Source/Assets/Image/EggIMG.png", renderer);
}

void Egg::add(const vector<RectChicken> &chicken){
    for(int i = 0; i < (int)chicken.size(); i++){
        if(rand() % 300 == 0) eggs.push_back({{chicken[i].hitBox.x + 8, chicken[i].hitBox.y + 50, 26, 32}, rand() % 2 + 2 });
    }
}

void Egg::render(SDL_Renderer* renderer){
    for(int i = 0; i < (int)eggs.size(); i++){
        SDL_RenderCopy(renderer, eggIMG, NULL, &eggs[i].hitBox);
        eggs[i].hitBox.y += eggs[i].vY;
        if(eggs[i].hitBox.y >= 800) {
            eggs.erase(eggs.begin() + i);
            i--;
        }
    }
}

bool Egg::checkCollision(PlayerShip &player, int &level){
    bool check = false;
    for(int i = 0; i < (int)eggs.size(); i++){
        if(SDL_HasIntersection(&eggs[i].hitBox, &player.hitBox)){
            player.getdame = true;
            eggs.erase(eggs.begin() + i);
            i--;
            player.hp--;
            level--;
            if(level == 0) level = 1;
            check = true;
        }
    }
    return check;
}
