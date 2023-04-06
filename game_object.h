#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED
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

class RectEgg{
public:
    SDL_Rect hitBox;
    int vY;

};

class PlayerShip{
public:
    SDL_Texture* smallExplosion[2];
    SDL_Texture* explosionIMG[5];
    SDL_Texture* playerIMG[5];
    SDL_Rect ship;
    SDL_Rect hitBox;
    int hp;
    bool alive;

    PlayerShip(SDL_Renderer* renderer, int x_, int y_, int hp_);
    void renderPlayer(SDL_Renderer* renderer);
    void updatePositionPlayer();
    bool renderPlayerGetDame(SDL_Renderer *renderer);
    bool renderDeadPlayer(SDL_Renderer* renderer);
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
    SDL_Texture* bulletIMG[3];


    vector<SDL_Rect> bullet1;
    vector<SDL_Rect> bullet2;
    vector<SDL_Rect> bullet3;

    bool add;
    int level;

    Bullet(SDL_Renderer* renderer);
    void addBullet(PlayerShip &player);
    void renderBullet(SDL_Renderer* renderer);
};

class Chicken{
public:
    SDL_Texture* chickenIMG[10];
    SDL_Texture* chickenExIMG[3];
    vector<RectChicken> chicken;
    vector<RectChicken> deadChicken;
    const int w = 104, h = 82;

    int hp, vx;
    int adding;


    Chicken(SDL_Renderer* renderer);
    void renderChicken(SDL_Renderer* renderer, vector<SDL_Rect> &gifts);
    void renderDeadChicken(SDL_Renderer* renderer);
    bool checkCollision(Bullet &bullets);

};

class Egg{
public:
    SDL_Texture* eggIMG;
    vector<RectEgg> eggs;

    Egg(SDL_Renderer* renderer);
    void addEgg(const vector<RectChicken> &chicken);
    void renderEgg(SDL_Renderer* renderer);
    bool checkCollision(PlayerShip &player, int &level);
};

class startMenu{
public:
    SDL_Texture* startMenuIMG;
    SDL_Rect play, options, quit;
    startMenu(SDL_Renderer* renderer);

    void renderMenu(SDL_Renderer *renderer);
};

class Gift{
public:
    SDL_Texture* giftIMG;
    vector<SDL_Rect> gifts;

    Gift(SDL_Renderer* Renderer);
    void renderGift(SDL_Renderer* Renderer);
    void checkCollision(PlayerShip &player, int &level);

};

//**********************************************

PlayerShip::PlayerShip(SDL_Renderer* renderer, int x_, int y_, int hp_){
    hitBox.x = x_ + 21;
    hitBox.y = y_ + 10;
    hitBox.w = 33;
    hitBox.h = 56;
    ship.x = x_;
    ship.y = y_;
    ship.w = 74;
    ship.h = 84;
    hp = hp_;
    alive = true;
    playerIMG[PLAYER_MID] = loadTexture("imagesource/player_ship.png", renderer);
    playerIMG[PLAYER_LEFT] = loadTexture("imagesource/player_ship_left.png", renderer);
    playerIMG[PLAYER_RIGHT] = loadTexture("imagesource/player_ship_right.png", renderer);
    playerIMG[PLAYER_LEFTMID] = loadTexture("imagesource/player_ship_leftmid.png", renderer);
    playerIMG[PLAYER_RIGHTMID] = loadTexture("imagesource/player_ship_rightmid.png", renderer);
    explosionIMG[0] = loadTexture("imagesource/Explosion/explosion-1.png", renderer);
    explosionIMG[1] = loadTexture("imagesource/Explosion/explosion-2.png", renderer);
    explosionIMG[2] = loadTexture("imagesource/Explosion/explosion-3.png", renderer);
    explosionIMG[3] = loadTexture("imagesource/Explosion/explosion-4.png", renderer);
    explosionIMG[4] = loadTexture("imagesource/Explosion/explosion-5.png", renderer);
    smallExplosion[0] =loadTexture("imagesource/Explosion/smallExplosion-1.png", renderer);
    smallExplosion[1] = loadTexture("imagesource/Explosion/smallExplosion-2.png", renderer);
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

    hitBox.x = ship.x + 21;
    hitBox.y = ship.y + 10;
}

bool PlayerShip::renderDeadPlayer(SDL_Renderer* renderer){
    static int ani = 0;
    if(ani == 30) return true;
    SDL_RenderCopy(renderer, explosionIMG[ani/6], NULL, &ship);
    ani++;
    return false;
}

bool PlayerShip:: renderPlayerGetDame(SDL_Renderer *renderer){
    static int ani = 0;
    if(ani == 12) {
        ani = 0;
        return true;
    }
    SDL_RenderCopy(renderer, smallExplosion[ani/6], NULL, &ship);
    ani++;
    return false;

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
    bulletIMG[0] = loadTexture("imagesource/bullet1.png", renderer);
    bulletIMG[1] = loadTexture("imagesource/bullet2.png", renderer);
    bulletIMG[2]= loadTexture("imagesource/bullet3.png", renderer);

    add = false;
    level = 1;
}

void Bullet ::addBullet(PlayerShip &player){
    static Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    if(add && (currentTime - lastTime >= DELAY_BULLET || currentTime == lastTime) ){
        if(level == 1){
            bullet1.push_back({player.ship.x + 30, player.ship.y - 20, 14, 84});
        }
        if(level == 2){
            bullet1.push_back( {player.ship.x, player.ship.y - 20, 14 ,84});
            bullet1.push_back( {player.ship.x + 60, player.ship.y -20 , 14, 84});
        }
        if(level == 3){
            bullet1.push_back( {player.ship.x + 14, player.ship.y - 20, 14 ,84});
            bullet1.push_back( {player.ship.x + 46, player.ship.y - 20, 14, 84});
            bullet2.push_back( {player.ship.x + 29, player.ship.y - 40, 17 , 99});
        }
        if(level == 4){
            bullet2.push_back( {player.ship.x + 12, player.ship.y - 20, 17, 99});
            bullet2.push_back( {player.ship.x + 29, player.ship.y - 40, 17, 99});
            bullet2.push_back( {player.ship.x + 46, player.ship.y - 20, 17, 99});
        }
        if(level == 5){
            bullet2.push_back( {player.ship.x + 8, player.ship.y - 20, 17, 99});
            bullet3.push_back( {player.ship.x + 25, player.ship.y - 40, 25, 108});
            bullet2.push_back( {player.ship.x + 50, player.ship.y - 20, 17 ,99});
        }
        if(level == 6){
            bullet2.push_back( {player.ship.x - 9, player.ship.y, 17 , 99});
            bullet2.push_back( {player.ship.x + 8, player.ship.y - 20, 17, 99});
            bullet3.push_back( {player.ship.x + 25, player.ship.y - 40, 25, 108});
            bullet2.push_back( {player.ship.x + 50, player.ship.y - 20, 17 ,99});
            bullet2.push_back( {player.ship.x + 67, player.ship.y , 17, 99});
        }
//        if(level == 7){
//            bullet3.push_back( {player.ship.x - 25, player.ship.y - 5, 25, 108});
//            bullet3.push_back( {player.ship.x, player.ship.y - 20, 25, 108});
//            bullet3.push_back( {player.ship.x + 25, player.ship.y - 40, 25, 108});
//            bullet3.push_back( {player.ship.x + 50, player.ship.y - 20, 25, 108});
//            bullet3.push_back( {player.ship.x + 75, player.ship.y - 5, 25, 108});
//        }
        lastTime = currentTime;
    }
}

void Bullet:: renderBullet(SDL_Renderer* renderer){
    for(int i = 0; i < (int)bullet1.size(); i++){
            if(bullet1[i].y > 0){
                SDL_RenderCopy(renderer, bulletIMG[0], NULL, &bullet1[i]);
                bullet1[i].y -= SPEED_OF_BULLET;
            }
            else{
                bullet1.erase(bullet1.begin() + i);
                i--;
            }
        }
    for(int i = 0; i < (int)bullet2.size(); i++){
            if(bullet2[i].y > 0){
                SDL_RenderCopy(renderer, bulletIMG[1], NULL, &bullet2[i]);
                bullet2[i].y -= SPEED_OF_BULLET;
            }
            else{
                bullet2.erase(bullet2.begin() + i);
                i--;
            }
        }
    for(int i = 0; i < (int)bullet3.size(); i++){
            if(bullet3[i].y > 0){
                SDL_RenderCopy(renderer, bulletIMG[2], NULL, &bullet3[i]);
                bullet3[i].y -= SPEED_OF_BULLET;
            }
            else{
                bullet3.erase(bullet3.begin() + i);
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

    chickenExIMG[0] = loadTexture("imagesource/Chicken/Explosion/chickenExplosion1.png", renderer);
    chickenExIMG[1] = loadTexture("imagesource/Chicken/Explosion/chickenExplosion2.png", renderer);
    chickenExIMG[2] = loadTexture("imagesource/Chicken/Explosion/chickenExplosion3.png", renderer);
    srand(time(0));
    adding = 1;
    vx = 1;
    hp = 1;
}

void Chicken::renderChicken(SDL_Renderer* renderer, vector<SDL_Rect> &gifts){
    bool checkEdge = false;
    if(adding){
        if((int)chicken.size() == 0) chicken.push_back({{LEFT_EDGE + 31 , TOP_EDGE, 42, 82},(rand() % 10) * 4, hp});
        if(adding % 6 == 0)chicken.push_back({{chicken[0].hitBox.x, chicken.back().hitBox.y + h, 42, 82},(rand() % 10) * 4, hp });
        else chicken.push_back({{chicken.back().hitBox.x + w, chicken.back().hitBox.y, 42, 82},(rand() % 10) * 4, hp});
        adding++;
    }
    if(adding == 24) {
        adding = 0;
        }

    for(int i = 0; i < (int)chicken.size(); i++){
        if(chicken[i].hp <= 0){
            if(chicken[i].ani % 11 == 0) gifts.push_back({chicken[i].hitBox.x - 31 , chicken[i].hitBox.y , 25 , 30});
            deadChicken.push_back({{chicken[i].hitBox.x - 31, chicken[i].hitBox.y, 104, 82}, 0, 0});
            chicken.erase(chicken.begin() + i);
            i--;
            continue;
        }
        renderTexture(chickenIMG[ (chicken[i].ani)/4 ], renderer, chicken[i].hitBox.x - 31, chicken[i].hitBox.y, w, h);
        chicken[i].ani = (chicken[i].ani + 1) % 40;
        chicken[i].hitBox.x += vx;
        if(!checkEdge)
        if(chicken[i].hitBox.x - 31 < LEFT_EDGE || chicken[i].hitBox.x - 31 > RIGHT_EDGE - w){
            checkEdge = true;
        }
    }
    if(checkEdge){
        vx = -vx;
    }
}

void Chicken::renderDeadChicken(SDL_Renderer* renderer){
    for(int i = 0; i < (int)deadChicken.size(); i++){
        SDL_RenderCopy(renderer, chickenExIMG[deadChicken[i].ani / 5], NULL, &deadChicken[i].hitBox);
        deadChicken[i].ani++;
        if(deadChicken[i].ani == 15){
        deadChicken.erase(deadChicken.begin() + i);
        i--;
        }
    }
}

bool Chicken::checkCollision(Bullet &bullets){
    if(chicken.size() == 0) return true;
    for(int i = 0; i < (int)chicken.size(); i++){
         for(int k = 0; k < (int)bullets.bullet1.size(); k++){
            if(SDL_HasIntersection(&chicken[i].hitBox, &bullets.bullet1[k])){
                    chicken[i].hp--;
                    bullets.bullet1.erase(bullets.bullet1.begin() + k);
                    k--;
                    continue;
            }
        }
        for(int k = 0; k < (int)bullets.bullet2.size(); k++){
            if(SDL_HasIntersection(&chicken[i].hitBox, &bullets.bullet2[k])){
                    chicken[i].hp -= 2;
                    bullets.bullet2.erase(bullets.bullet2.begin() + k);
                    k--;
                    continue;
            }
        }
        for(int k = 0; k < (int)bullets.bullet3.size(); k++){
            if(SDL_HasIntersection(&chicken[i].hitBox, &bullets.bullet3[k])){
                    chicken[i].hp -= 3;
                    bullets.bullet3.erase(bullets.bullet3.begin() + k);
                    k--;
                    continue;
            }
        }
    }
    return false;
}



startMenu::startMenu(SDL_Renderer* renderer){
    startMenuIMG = loadTexture("imagesource/Menu/startMenu.png", renderer);
    play = {26, 635, 238, 150};
    options = {286, 635, 238, 150};
    quit = {545, 635, 238, 150};

}

void startMenu::renderMenu(SDL_Renderer *renderer){
    renderTexture(startMenuIMG, renderer, 0, 0);
}



Egg::Egg(SDL_Renderer* renderer){
    eggIMG = loadTexture("imagesource/EggIMG.png", renderer);
}

void Egg::addEgg(const vector<RectChicken> &chicken){
    for(int i = 0; i < (int)chicken.size(); i++){
        if(rand() % 300 == 0) eggs.push_back({{chicken[i].hitBox.x + 8, chicken[i].hitBox.y + 50, 26, 32}, rand() % 2 + 2 });
    }
}

void Egg::renderEgg(SDL_Renderer* renderer){
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



Gift::Gift(SDL_Renderer* renderer){
    giftIMG = loadTexture("imagesource/gift.png", renderer);
}

void Gift :: renderGift(SDL_Renderer* renderer){
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
            if(level == 7) level = 6;
            continue;
        }
    }
}
#endif // GAME_OBJECT_H_INCLUDED
