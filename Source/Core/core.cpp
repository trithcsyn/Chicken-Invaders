#include"core.h"


void Core::init(){
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, "Chicken Invaders");
    sMenu.init(renderer);
    player.init(renderer, SCREEN_WIDTH/2 - 74/2, SCREEN_HEIGHT/2 - 84/2, 5);
    background.init(renderer);
    bullets.init(renderer);
    chickens.init(renderer);
    eggs.init(renderer);
    giftt.init(renderer);
    itf.init(renderer);


}

int Core::runGame(){
    bool play = false, startMenu = true, quit = false;
    while(true){
        while(startMenu){
            while(SDL_PollEvent(&e)){
                if(e.type == SDL_QUIT) return 0;
                break;
            }
            background.render(renderer);
            sMenu.render(renderer);
            sMenu.getHighLight(renderer);
            sMenu.check(e, play, startMenu, quit);
            SDL_RenderPresent(renderer);
        }
        while(play){
            SDL_Event e;
            background.render(renderer);
            while(SDL_PollEvent(&e)){
                if(e.type == SDL_QUIT){
                    quit = true;
                    play = false;
                }
                if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){
                     if(player.hp <= 0)
                        if(player.renderDead(renderer, itf, e)){
                            bullets.level = 1;
                            player.hp = 5;
                            chickens.chicken.clear();
                            chickens.hp = 0;
                            itf.saveScore();
                        }
                }
                if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
                    bullets.adding = true;
                }
                if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT){
                    bullets.adding = false;
                }
            }
            if(player.hp > 0){
                itf.renderScore(renderer);
                bullets.add(player);
                player.render(renderer);
                eggs.checkCollision(player, bullets.level);
                chickens.checkCollision(player);
                if(player.getdame){
                    if(player.renderGetDame(renderer)){
                        player.getdame = false;
                    }
                }
                eggs.add(chickens.chicken);
            }
            giftt.render(renderer);
            giftt.checkCollision(player, bullets.level);
            bullets.render(renderer);
            eggs.render(renderer);
            chickens.render(renderer, giftt.gifts, itf);
            chickens.renderDead(renderer);
            if(chickens.checkCollision(bullets)){
                chickens.hp++;
                chickens.add();
                chickens.adding = 1;
            }
            itf.renderHighScore(renderer);
            itf.renderHeart(renderer, player.hp);
            if(player.hp <= 0) player.renderDead(renderer, itf, e);
            player.updatePos();
            SDL_RenderPresent(renderer);
        }
        if(quit){
            return 0;
        }
    }
    return 0;
}

