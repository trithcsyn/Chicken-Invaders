#include <iostream>
#include <SDL.h>

#include "SDL_utils.h"
#include"game_constans.h"

using namespace std;

//**************************************************************

int main(int argc, char* argv[])
{
    load_SDL_IMG();
    SDL_Event e;
    while(true){
        while(SDL_PollEvent(&e) != 0){
                if(e.type == SDL_QUIT) return 0;
                if(e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN){
                    if( (e.button.button == SDL_BUTTON_LEFT) || (e.key.keysym.sym == SDLK_SPACE) ){
                    updateBullet();
                    }
                }

        }
        renderBackground();
        renderPlayer();
        renderBullet();

        updatePositionPlayer();
        renderScreen();
    }
    waitUntilKeyPressed();
    quitSDL();
}
