#include "SDL_utils.h"
#include"game_constans.h"
#include"game_object.h"
//**************************************************************

SDL_Window* window;
SDL_Renderer* renderer;

int main(int argc, char* argv[])
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, "Chicken Invaders");
    startMenu sMenu(renderer);

    PlayerShip player(renderer, SCREEN_WIDTH/2 - 74/2, SCREEN_HEIGHT/2 - 84/2, 5);
    Background background(renderer);
    Bullet bullets(renderer);
    Chicken chickens(renderer);
    Egg eggs(renderer);
    Gift giftt(renderer);
    SDL_Event e;
    bool play = false, checksMenu = true;
    while(true){
        while(checksMenu){
            sMenu.renderMenu(renderer);
            while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT) return 0;
                if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
                    SDL_Point click = {e.motion.x, e.motion.y};
                    if(SDL_PointInRect(&click, &sMenu.play)){
                        play = true;
                        checksMenu = false;
                    }
                    if(SDL_PointInRect(&click, &sMenu.quit)) return 0;
                }
            }
            SDL_RenderPresent(renderer);
        }
        while(play){
            background.renderBackground(renderer);
            while(SDL_PollEvent(&e) != 0 ){
                if(e.type == SDL_QUIT) return 0;
                if(player.hp > 0 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
                    bullets.add = true;
                }
                if(player.hp > 0 && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT){
                    bullets.add = false;
                }
            }
            if(player.hp > 0){
                bullets.addBullet(player);
                player.renderPlayer(renderer);
                if(eggs.checkCollision(player, bullets.level)) player.alive = false;
                if(!player.alive){
                    if(player.renderPlayerGetDame(renderer)){
                        player.alive = true;
                    }
                }
            }
            if(player.hp <= 0){
                if(player.renderDeadPlayer(renderer)){

                }
            }
            giftt.renderGift(renderer);
            giftt.checkCollision(player, bullets.level);
            bullets.renderBullet(renderer);
            eggs.addEgg(chickens.chicken);
            eggs.renderEgg(renderer);

            chickens.renderChicken(renderer, giftt.gifts);
            chickens.renderDeadChicken(renderer);
            if(chickens.checkCollision(bullets)){
                chickens.adding = 1;
                chickens.hp++;
            }

            player.updatePositionPlayer();
            SDL_RenderPresent(renderer);
        }
    }
    quitSDL(window, renderer);
    return 0;
}
