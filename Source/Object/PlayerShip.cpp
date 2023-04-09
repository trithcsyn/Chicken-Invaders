#include"PlayerShip.h"

void PlayerShip::init(SDL_Renderer* renderer, int x_, int y_, int hp_){
    hitBox.x = x_ + 21;
    hitBox.y = y_ + 10;
    hitBox.w = 33;
    hitBox.h = 56;
    ship.x = x_;
    ship.y = y_;
    ship.w = 74;
    ship.h = 84;
    hp = hp_;
    getdame = false;
    playerIMG[PLAYER_MID] = loadTexture("Source/Assets/Image/player_ship.png", renderer);
    playerIMG[PLAYER_LEFT] = loadTexture("Source/Assets/Image/player_ship_left.png", renderer);
    playerIMG[PLAYER_RIGHT] = loadTexture("Source/Assets/Image/player_ship_right.png", renderer);
    playerIMG[PLAYER_LEFTMID] = loadTexture("Source/Assets/Image/player_ship_leftmid.png", renderer);
    playerIMG[PLAYER_RIGHTMID] = loadTexture("Source/Assets/Image/player_ship_rightmid.png", renderer);
    explosionIMG[0] = loadTexture("Source/Assets/Image/explosion-1.png", renderer);
    explosionIMG[1] = loadTexture("Source/Assets/Image/explosion-2.png", renderer);
    explosionIMG[2] = loadTexture("Source/Assets/Image/explosion-3.png", renderer);
    explosionIMG[3] = loadTexture("Source/Assets/Image/explosion-4.png", renderer);
    explosionIMG[4] = loadTexture("Source/Assets/Image/explosion-5.png", renderer);
    smallExplosion[0] =loadTexture("Source/Assets/Image/smallExplosion-1.png", renderer);
    smallExplosion[1] = loadTexture("Source/Assets/Image/smallExplosion-2.png", renderer);
}

void PlayerShip::render(SDL_Renderer* renderer){
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

void PlayerShip::updatePos(){
    SDL_GetMouseState(&ship.x, &ship.y);
    ship.x -= 37;
    ship.y -= 84;

    hitBox.x = ship.x + 21;
    hitBox.y = ship.y + 10;
}

bool PlayerShip::renderDead(SDL_Renderer* renderer){
    static int ani = 0;
    if(ani == 30) return true;
    SDL_RenderCopy(renderer, explosionIMG[ani/6], NULL, &ship);
    ani++;
    return false;
}

bool PlayerShip:: renderGetDame(SDL_Renderer *renderer){
    static int ani = 0;
    if(ani == 12) {
        ani = 0;
        return true;
    }
    SDL_RenderCopy(renderer, smallExplosion[ani/6], NULL, &ship);
    ani++;
    return false;

}
