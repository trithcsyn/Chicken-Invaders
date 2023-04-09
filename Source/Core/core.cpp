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
    bool play = false;
    while(true){
        while(sMenu.status){
            background.render(renderer);
            sMenu.render(renderer);
            sMenu.getHighLight(renderer);
            while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT) return 0;
                if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
                    SDL_Point click = {e.motion.x, e.motion.y};
                    if(SDL_PointInRect(&click, &sMenu.play)){
                        play = true;
                        sMenu.status = false;
                    }
                    if(SDL_PointInRect(&click, &sMenu.quit)) return 0;
                }
            }
            SDL_RenderPresent(renderer);
        }
        while(play){
            background.render(renderer);
            while(SDL_PollEvent(&e) != 0 ){
                if(e.type == SDL_QUIT) return 0;
                if(player.hp > 0 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
                    bullets.adding = true;
                }
                if(player.hp > 0 && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT){
                    bullets.adding = false;
                }
            }
            if(player.hp > 0){
                bullets.add(player);
                player.render(renderer);
                if(eggs.checkCollision(player, bullets.level) || chickens.checkCollision(player)) player.getdame = true;
                if(player.getdame){
                    if(player.renderGetDame(renderer)){
                        player.getdame =false;
                    }
                }
            }
            if(player.hp <= 0)
            if(player.renderDead(renderer)){}
            giftt.render(renderer);
            giftt.checkCollision(player, bullets.level);
            bullets.render(renderer);
            eggs.add(chickens.chicken);
            eggs.render(renderer);

            chickens.render(renderer, giftt.gifts, itf);
            chickens.renderDead(renderer);
            if(chickens.checkCollision(bullets)){
                chickens.hp++;
                chickens.add();
                chickens.adding = 1;
            }
            itf.renderScore(renderer);
            itf.renderHeart(renderer, player.hp);
            player.updatePos();
            SDL_RenderPresent(renderer);
        }
    }
    quitSDL(window, renderer);
    return 0;
}
