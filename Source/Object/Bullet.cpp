#include"Bullet.h"
void Bullet::init(SDL_Renderer* renderer){
    bulletIMG[0] = loadTexture("Source/Assets/Image/B1.png", renderer, true);
    bulletIMG[1] = loadTexture("Source/Assets/Image/B2.png", renderer, true);
    bulletIMG[2]= loadTexture("Source/Assets/Image/B3.png", renderer, true);

    adding = false;
    level = 1;
}

void Bullet ::add(PlayerShip &player){
    static Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    if(adding && (currentTime - lastTime >= DELAY_BULLET || currentTime == lastTime) ){
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

void Bullet:: render(SDL_Renderer* renderer){
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
