#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include "../Manager/SDL_utils.h"
#include"../Manager/game_constans.h"
#include"../Manager/Font.h"

#include"../Menu/menu.h"
#include"../Object/PlayerShip.h"
#include"../Object/BackGround.h"
#include"../Object/Bullet.h"
#include"../Object/Chicken.h"
#include"../Object/Egg.h"
#include"../Object/Gift.h"

class Core{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    startMenu sMenu;
    Interface itf;

    PlayerShip player;
    Background background;
    Bullet bullets;
    Chicken chickens;
    Egg eggs;
    Gift giftt;
    SDL_Event e;

    void init();
    int runGame();
};
#endif // CORE_H_INCLUDED
