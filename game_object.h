#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED
#include<vector>
#include<ctime>
#include"game_constans.h"
#include"SDL_utils.h"
using namespace std;

//*********************************************


class RectChicken{
public:
    SDL_Rect hitBox;
    int ani;
    int hp;
};

class PlayerShip{
public:
    SDL_Texture* explosionIMG[5];
    SDL_Texture* playerIMG[5];
    SDL_Rect ship;
    int hp;
    PlayerShip(SDL_Renderer* renderer, int x_, int y_, int hp_);
    void renderPlayer(SDL_Renderer* renderer);
    void updatePositionPlayer();
    void renderDeadPlayer(SDL_Renderer *renderer);
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
    vector<SDL_Rect> bullet;
    Bullet(SDL_Renderer* renderer);
    void addBullet(const int &posPlayerX, const int &posPlayerY);
    void renderBullet(SDL_Renderer* renderer);
};

class Chicken{
public:
    SDL_Texture* chickenIMG[10];
    SDL_Texture* chickenExIMG[3];
    vector<vector<RectChicken>> chicken;
    vector<RectChicken> deadChicken;
    const int w = 104, h = 82;
    int vx;


    Chicken(SDL_Renderer* renderer);
    void renderChicken(SDL_Renderer* renderer);
    void renderDeadChicken(SDL_Renderer* renderer);
    void checkCollision(vector<SDL_Rect> &bullet);

};

//**********************************************

PlayerShip::PlayerShip(SDL_Renderer* renderer, int x_, int y_, int hp_){
    ship.x = x_;
    ship.y = y_;
    ship.w = 74;
    ship.h = 84;
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
    explosionIMG[0] = loadTexture("imagesource/Explosion/explosion-1.png", renderer);
    explosionIMG[1] = loadTexture("imagesource/Explosion/explosion-2.png", renderer);
    explosionIMG[2] = loadTexture("imagesource/Explosion/explosion-3.png", renderer);
    explosionIMG[3] = loadTexture("imagesource/Explosion/explosion-4.png", renderer);
    explosionIMG[4] = loadTexture("imagesource/Explosion/explosion-5.png", renderer);
    for(int i = 0; i < 5; i++){
        if(explosionIMG[i] == nullptr){
            logSDLError(cout, "loadExplosion", true);
            break;
        }
    }
}

void PlayerShip::renderPlayer(SDL_Renderer* renderer){
        static int preMove = -1;
        if(preMove == -1) SDL_RenderCopy(renderer, playerIMG[PLAYER_MID], NULL, &ship);
        else{
        if(ship.x - preMove > 30) SDL_RenderCopy(renderer, playerIMG[PLAYER_RIGHT], NULL, &ship);
        if(preMove - ship.x > 30) SDL_RenderCopy(renderer, playerIMG[PLAYER_LEFT], NULL, &ship);
        if(ship.x - preMove <= 30 && ship.x > preMove) SDL_RenderCopy(renderer, playerIMG[PLAYER_RIGHTMID], NULL, &ship);
        if(preMove - ship.x <= 30 && preMove > ship.x) SDL_RenderCopy(renderer, playerIMG[PLAYER_LEFTMID], NULL, &ship);
        if(preMove == ship.x) SDL_RenderCopy(renderer, playerIMG[PLAYER_MID], NULL, &ship);
    }
    preMove = ship.x;
}

void PlayerShip::updatePositionPlayer(){
    SDL_GetMouseState(&ship.x, &ship.y);
    ship.x -= 37;
    ship.y -= 84;
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
        bullet.push_back({posPlayerX + 32, posPlayerY - 37, 10, 37});
        lastTime = currentTime;
    }
}

void Bullet:: renderBullet(SDL_Renderer* renderer){
    for(int i = 0; i < (int)bullet.size(); i++){
        if(bullet[i].y > 0){
            SDL_RenderCopy(renderer, bulletIMG, NULL, &bullet[i]);
            bullet[i].y -= SPEED_OF_BULLET;
        }
        else{
            bullet.erase(bullet.begin() + i);
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
    chickenExIMG[0] = loadTexture("imagesource/Chicken/Explosion/chickenExplosion1.png", renderer);
    chickenExIMG[1] = loadTexture("imagesource/Chicken/Explosion/chickenExplosion2.png", renderer);
    chickenExIMG[2] = loadTexture("imagesource/Chicken/Explosion/chickenExplosion3.png", renderer);
    srand(time(0));
    chicken.resize(6);
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            SDL_Rect temp;
            temp.x = LEFT_EDGE + w * i + 31;
            temp.y = TOP_EDGE + h * j ;
            temp.w = 42;
            temp.h = 82;
            chicken[i].push_back({temp, (rand() % 10) * 4, 1});
        }
    }
    vx = 1;
}

void Chicken::renderChicken(SDL_Renderer* renderer){
    bool checkEdge = false;
    for(int i = 0; i < (int)chicken.size(); i++)
    for(int j = 0; j < (int)chicken[i].size(); j++){
        if(chicken[i][j].hp == 0){
            deadChicken.push_back({{chicken[i][j].hitBox.x - 31, chicken[i][j].hitBox.y, 104, 82}, 0, 0});
            chicken[i].erase(chicken[i].begin() + j);
        }
        renderTexture(chickenIMG[ (chicken[i][j].ani)/4 ], renderer, chicken[i][j].hitBox.x - 31, chicken[i][j].hitBox.y, w, h);
        chicken[i][j].ani = (chicken[i][j].ani + 1) % 40;
        chicken[i][j].hitBox.x += vx;
        if(!checkEdge)
        if(chicken[i][j].hitBox.x - 31 <= LEFT_EDGE || chicken[i][j].hitBox.x - 31 >= RIGHT_EDGE - w){
            checkEdge = true;
        }
    }
    if(checkEdge){
        vx = -vx;
    }
}

void Chicken::renderDeadChicken(SDL_Renderer* renderer){
    for(int i = 0; i < (int)deadChicken.size(); i++){
        if(deadChicken[i].ani == 12){
        deadChicken.erase(deadChicken.begin() + i);
        }
        SDL_RenderCopy(renderer, chickenExIMG[deadChicken[i].ani / 4], NULL, &deadChicken[i].hitBox);
        deadChicken[i].ani++;
    }
}

void Chicken::checkCollision(vector<SDL_Rect> &bullet){
    for(int i = 0; i < (int)chicken.size(); i++){
        for(int j = chicken[i].size() - 1; j >= 0; j--){
             for(int k = 0; k < (int)bullet.size(); k++){
                if(SDL_HasIntersection(&chicken[i][j].hitBox, &bullet[k])){
                        chicken[i][j].hp--;
                        bullet.erase(bullet.begin() + k);
                        break;
                   }
             }
        }
    }
}

void PlayerShip:: renderDeadPlayer(SDL_Renderer *renderer){
    static int ani = 0;
    if(ani == 25) hp = -1;
    SDL_RenderCopy(renderer, explosionIMG[ani/5], NULL, &ship);
    ani++;
}

#endif // GAME_OBJECT_H_INCLUDED
