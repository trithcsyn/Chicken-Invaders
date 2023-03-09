#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED
#include<vector>
#include<ctime>
#include"game_constans.h"
#include"SDL_utils.h"
using namespace std;

//*********************************************

class Position{
public:
    int x, y;
};

class PosChicken{
public:
    int x, y, ani, hp;
};

class PlayerShip{
public:
    SDL_Texture* playerIMG[5];
    Position pos;
    int hp;
    const int w = 74, h = 84;
    PlayerShip(SDL_Renderer* renderer, int x_, int y_, int hp_);
    void renderPlayer(SDL_Renderer* renderer);
    void updatePositionPlayer();
};

class Background{
public:
    SDL_Texture* backgroundIMG;
    SDL_Rect clipBackground;

    Background(SDL_Renderer* renderer);
    void renderBackground(SDL_Renderer* renderer);
};

class Bullet{
public:
    SDL_Texture* bulletIMG;
    vector<Position> pos;

    Bullet(SDL_Renderer* renderer);
    void addBullet(const int &posPlayerX, const int &posPlayerY);
    void renderBullet(SDL_Renderer* renderer);
};

class Chicken{
public:
    SDL_Texture* chickenIMG[10];
    vector<PosChicken> pos;
    const int w = 104, h = 82;
    int vx;

    Chicken(SDL_Renderer* renderer);
    void renderChicken(SDL_Renderer* renderer);
};

//**********************************************

PlayerShip::PlayerShip(SDL_Renderer* renderer, int x_, int y_, int hp_){
    pos.x = x_;
    pos.y = y_;
    hp = hp_;
    playerIMG[PLAYER_MID] = loadTexture("imagesource/player_ship.png", renderer);
    playerIMG[PLAYER_LEFT] = loadTexture("imagesource/player_ship_left.png", renderer);
    playerIMG[PLAYER_RIGHT] = loadTexture("imagesource/player_ship_right.png", renderer);
    playerIMG[PLAYER_LEFTMID] = loadTexture("imagesource/player_ship_leftmid.png", renderer);
    playerIMG[PLAYER_RIGHTMID] = loadTexture("imagesource/player_ship_rightmid.png", renderer);
    for(int i = 0; i < 5; i++){
        if(playerIMG[i] == nullptr){
            logSDLError(std :: cout, "loadPlayerShip", true);
            break;
        }
    }
}

void PlayerShip::renderPlayer(SDL_Renderer* renderer){
        static int preMove = -1;
        if(preMove == -1) renderTexture(playerIMG[PLAYER_MID], renderer, pos.x, pos.y);
        else{
        if(pos.x - preMove > 30) renderTexture(playerIMG[PLAYER_RIGHT],renderer, pos.x, pos.y);
        if(preMove - pos.x > 30) renderTexture(playerIMG[PLAYER_LEFT], renderer, pos.x, pos.y);
        if(pos.x - preMove <= 30 && pos.x > preMove) renderTexture(playerIMG[PLAYER_RIGHTMID], renderer, pos.x, pos.y);
        if(preMove - pos.x <= 30 && preMove > pos.x) renderTexture(playerIMG[PLAYER_LEFTMID], renderer, pos.x, pos.y);
        if(preMove == pos.x) renderTexture(playerIMG[PLAYER_MID], renderer, pos.x, pos.y);
    }
    preMove = pos.x;
}

void PlayerShip::updatePositionPlayer(){
    SDL_GetMouseState(&pos.x, &pos.y);
    pos.x -= 37;
    pos.y -= 84;
}

Background::Background(SDL_Renderer* renderer){
    backgroundIMG = loadTexture("imagesource/background.png", renderer);
    clipBackground.x = 0;
    clipBackground.y = 1200;
    clipBackground.w = SCREEN_WIDTH;
    clipBackground.h = SCREEN_HEIGHT;
}

void Background::renderBackground(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, backgroundIMG, &clipBackground, NULL);
    clipBackground.y = (clipBackground.y - SPEED_OF_BACKGROUND + 1200)% 1200;
}

Bullet::Bullet(SDL_Renderer* renderer){
    bulletIMG = loadTexture("imagesource/bullet.png", renderer);
    if(bulletIMG == nullptr) logSDLError(std :: cout, "loadBullet");
}

void Bullet ::addBullet(const int &posPlayerX, const int &posPlayerY){
    static Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    if(currentTime - lastTime >= DELAY_BULLET || currentTime == lastTime){
        pos.push_back({posPlayerX + 32, posPlayerY - 37});
        lastTime = currentTime;
    }
}

void Bullet:: renderBullet(SDL_Renderer* renderer){
    for(int i = 0; i < (int)pos.size(); i++){
        if(pos[i].y > 0){
            renderTexture(bulletIMG, renderer, pos[i].x, pos[i].y);
            pos[i].y -= SPEED_OF_BULLET;
        }
        else{
            pos.erase(pos.begin() + i);
            i--;
        }
    }
}

Chicken::Chicken(SDL_Renderer* renderer){
    chickenIMG[0] = loadTexture("imagesource/Chicken/ChickenImg-1.png", renderer);
    chickenIMG[1] = loadTexture("imagesource/Chicken/ChickenImg-2.png", renderer);
    chickenIMG[2] = loadTexture("imagesource/Chicken/ChickenImg-3.png", renderer);
    chickenIMG[3] = loadTexture("imagesource/Chicken/ChickenImg-4.png", renderer);
    chickenIMG[4] = loadTexture("imagesource/Chicken/ChickenImg-5.png", renderer);
    chickenIMG[5] = loadTexture("imagesource/Chicken/ChickenImg-6.png", renderer);
    chickenIMG[6] = loadTexture("imagesource/Chicken/ChickenImg-7.png", renderer);
    chickenIMG[7] = loadTexture("imagesource/Chicken/ChickenImg-8.png", renderer);
    chickenIMG[8] = loadTexture("imagesource/Chicken/ChickenImg-9.png", renderer);
    chickenIMG[9] = loadTexture("imagesource/Chicken/ChickenImg-10.png", renderer);

    for(int i = 0;i < 10; i++){
        if(chickenIMG[i] == nullptr){
            logSDLError(std::cout, "LoadChicken", true);
            break;
        }
    }
    srand(time(0));
    for(int j = 0; j < 6; j++){
        for(int i = 0; i < 4; i++){
            pos.push_back({LEFT_EDGE + w * j, TOP_EDGE + h * i , (rand() % 10) * 4 , 1});
        }
    }
    vx = 1;
}

void Chicken::renderChicken(SDL_Renderer* renderer){
    bool checkEdge = false;
    for(int i = 0; i < (int)pos.size(); i++){
        renderTexture(chickenIMG[ pos[i].ani/4 ], renderer, pos[i].x, pos[i].y, w, h);
        pos[i].ani = (pos[i].ani + 1) % 40;
        pos[i].x += vx;
        if(!checkEdge)
        if(pos[i].x <= LEFT_EDGE || pos[i].x >= RIGHT_EDGE - w){
            checkEdge = true;
        }
    }
    if(checkEdge){
        vx = -vx;
    }

}




#endif // GAME_OBJECT_H_INCLUDED
