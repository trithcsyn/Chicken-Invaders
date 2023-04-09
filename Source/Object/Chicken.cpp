#include"Chicken.h"
void Chicken::init(SDL_Renderer* renderer){
    chickenIMG[0] = loadTexture("Source/Assets/Image/ChickenImg-1.png", renderer);
    chickenIMG[1] = loadTexture("Source/Assets/Image/ChickenImg-2.png", renderer);
    chickenIMG[2] = loadTexture("Source/Assets/Image/ChickenImg-3.png", renderer);
    chickenIMG[3] = loadTexture("Source/Assets/Image/ChickenImg-4.png", renderer);
    chickenIMG[4] = loadTexture("Source/Assets/Image/ChickenImg-5.png", renderer);
    chickenIMG[5] = loadTexture("Source/Assets/Image/ChickenImg-6.png", renderer);
    chickenIMG[6] = loadTexture("Source/Assets/Image/ChickenImg-7.png", renderer);
    chickenIMG[7] = loadTexture("Source/Assets/Image/ChickenImg-8.png", renderer);
    chickenIMG[8] = loadTexture("Source/Assets/Image/ChickenImg-9.png", renderer);
    chickenIMG[9] = loadTexture("Source/Assets/Image/ChickenImg-10.png", renderer);

    chickenExIMG[0] = loadTexture("Source/Assets/Image/chickenExplosion1.png", renderer);
    chickenExIMG[1] = loadTexture("Source/Assets/Image/chickenExplosion2.png", renderer);
    chickenExIMG[2] = loadTexture("Source/Assets/Image/chickenExplosion3.png", renderer);
    srand(time(0));
    adding = 1;
    vx = 1;
    hp = 0;
    chicken.resize(0);
    adding = 0;
}

void Chicken::render(SDL_Renderer* renderer, vector<SDL_Rect> &gifts, Interface &itf){
    bool checkEdge = false;
        for(int i = 0; i < (int)chicken.size(); i++){
            if(chicken[i].hp <= 0){
                itf.score += 500 * hp;
                if(chicken[i].ani  == 11) gifts.push_back({chicken[i].hitBox.x - 31 , chicken[i].hitBox.y , 25 , 30});
                deadChicken.push_back({{chicken[i].hitBox.x - 31, chicken[i].hitBox.y, 104, 82}, 0, 0});
                chicken.erase(chicken.begin() + i);
                i--;
                continue;
            }
            renderTexture(chickenIMG[ (chicken[i].ani)/4 ], renderer, chicken[i].hitBox.x - 31, chicken[i].hitBox.y, w, h);
            chicken[i].ani = (chicken[i].ani + 1) % 40;
            chicken[i].hitBox.x += vx;
            if(!checkEdge && !adding)
            if(chicken[i].hitBox.x - 31 < LEFT_EDGE || chicken[i].hitBox.x - 31 > RIGHT_EDGE - w){
                checkEdge = true;
            }
        }
        if(adding){
                if(adding <= 100){
                    itf.text.render(renderer, "Get Ready!", 320, 400, 0.75, false );
                    string temp = "Wave " + to_string(hp);
                    itf.text.render(renderer,temp , 370, 450, 0.5 ,false);
                }
                adding++;
                if(adding == 200) {
                    adding = 0;
                    vx = 1;
                }
            }
        if(checkEdge){
            vx = -vx;
        }
}

void Chicken::add(){
    for(int j = 0; j < 4; j++){
            for(int i = 0; i < 6; i++){
                chicken.push_back( {{LEFT_EDGE + 31 + i * w + 800, TOP_EDGE + j * h, 42 ,82}, (rand() % 10) * 4, hp});
            }
    }
    vx = -4;
}

void Chicken::renderDead(SDL_Renderer* renderer){
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

bool Chicken::checkCollision(PlayerShip &player){
    for(int i = 0; i < (int)chicken.size(); i++){
        if(SDL_HasIntersection(&chicken[i].hitBox, &player.hitBox)){
            player.hp--;
            return true;
        }
    }
    return false;
}

