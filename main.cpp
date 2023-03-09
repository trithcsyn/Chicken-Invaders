#include <iostream>
#include <SDL.h>

#include "SDL_utils.h"
#include"game_constans.h"
#include"game_object.h"
using namespace std;

//**************************************************************

SDL_Window* window;
SDL_Renderer* renderer;


int main(int argc, char* argv[])
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, "Chicken Invaders");
    PlayerShip player(renderer, SCREEN_WIDTH/2 - 74/2, SCREEN_HEIGHT/2 - 84/2, 5);
    Background background(renderer);
    Bullet bullets(renderer);
    Chicken chickens(renderer);
    SDL_Event e;
    while(true){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT) return 0;
            if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
                bullets.addBullet(player.pos.x, player.pos.y);
            }
        }
        background.renderBackground(renderer);
        player.renderPlayer(renderer);
        bullets.renderBullet(renderer);
        chickens.renderChicken(renderer);

        player.updatePositionPlayer();
        SDL_RenderPresent(renderer);
    }
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
