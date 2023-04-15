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
    status = ADD;
//    status = DEAD;
    vx = 1;
    hp = 1;
    chicken.resize(0);
    this -> add();
}


void Chicken::render(SDL_Renderer* renderer, vector<SDL_Rect> &gifts, Interface &itf){
    if(status == WAIT) return;
    bool checkEdge = false;
        for(int i = 0; i < (int)chicken.size(); i++){
            if(chicken[i].hp <= 0){
                itf.score += 500 * hp;
                if(chicken[i].ani % 10 == 0) gifts.push_back({chicken[i].hitBox.x - 31 , chicken[i].hitBox.y , 25 , 30});
                deadChicken.push_back({{chicken[i].hitBox.x - 31, chicken[i].hitBox.y, 104, 82}, 0, 0});
                chicken.erase(chicken.begin() + i);
                i--;
                continue;
            }
            renderTexture(chickenIMG[ (chicken[i].ani)/4 ], renderer, chicken[i].hitBox.x - 31, chicken[i].hitBox.y, w, h);
            chicken[i].ani = (chicken[i].ani + 1) % 40;
            chicken[i].hitBox.x += vx;
            if(!checkEdge && !(status == ADD))
            if(chicken[i].hitBox.x - 31 < LEFT_EDGE || chicken[i].hitBox.x - 31 > RIGHT_EDGE - w){
                checkEdge = true;
            }
        }
        if(status == ADD){
                if(countAdd <= 100){
                    itf.text.render(renderer, "Get Ready!", 320, 400, 0.75, false );
                    string temp = "Wave " + to_string(itf.wave);
                    itf.text.render(renderer,temp , 370, 450, 0.5 ,false);
                }
                countAdd++;
                if(countAdd == 200) {
                    status = ALIVE;
                    vx = 1;
                }
            }
        if(checkEdge){
            vx = -vx;
        }
}

void Chicken::add(){
    if(status == WAIT) return;
    for(int j = 0; j < 4; j++){
            for(int i = 0; i < 6; i++){
                chicken.push_back( {{LEFT_EDGE + 31 + i * w + 800, TOP_EDGE + j * h, 42 ,82}, (rand() % 10) * 4, hp});
            }
    }
    vx = -4;
    countAdd = 1;
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

void Chicken::checkCollision(Bullet &bullets){
    if(status == WAIT) return;
    if(chicken.size() == 0){
        status = DEAD;
    }
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
}

bool Chicken::checkCollision(PlayerShip &player){
    if(status == WAIT) return false;
    for(int i = 0; i < (int)chicken.size(); i++){
        if(SDL_HasIntersection(&chicken[i].hitBox, &player.hitBox)){
            player.hp = 0;
            return true;
        }
    }
    return false;
}




void BigChicken :: init(SDL_Renderer* renderer){
    bigChickenIMG[0] = loadTexture("Source/Assets/Image/Bigchicken1.png", renderer);
    bigChickenIMG[1] = loadTexture("Source/Assets/Image/Bigchicken2.png", renderer);
    bigChickenIMG[2] = loadTexture("Source/Assets/Image/Bigchicken3.png", renderer);
    bigChickenIMG[3] = loadTexture("Source/Assets/Image/Bigchicken4.png", renderer);
    bigChickenIMG[4] = loadTexture("Source/Assets/Image/Bigchicken5.png", renderer);
    bigChickenIMG[5] = loadTexture("Source/Assets/Image/Bigchicken6.png", renderer);
    bigChickenIMG[6] = loadTexture("Source/Assets/Image/Bigchicken7.png", renderer);
    bigChickenIMG[7] = loadTexture("Source/Assets/Image/Bigchicken8.png", renderer);
    bigChickenIMG[8] = loadTexture("Source/Assets/Image/Bigchicken9.png", renderer);
    bigChickenIMG[9] = loadTexture("Source/Assets/Image/Bigchicken10.png", renderer);
    bigChickenIMG[10] = loadTexture("Source/Assets/Image/Bigchicken11.png", renderer);
    bigChickenIMG[11] = loadTexture("Source/Assets/Image/Bigchicken12.png", renderer);
    bigChickenIMG[12] = loadTexture("Source/Assets/Image/Bigchicken13.png", renderer);
    bigChickenIMG[13] = loadTexture("Source/Assets/Image/Bigchicken14.png", renderer);
    bigChickenIMG[14] = loadTexture("Source/Assets/Image/Bigchicken15.png", renderer);
    bigChickenIMG[15] = loadTexture("Source/Assets/Image/Bigchicken16.png", renderer);
    bigChickenIMG[16] = loadTexture("Source/Assets/Image/Bigchicken17.png", renderer);
    bigChickenIMG[17] = loadTexture("Source/Assets/Image/Bigchicken18.png", renderer);

    explosion[0] = loadTexture("Source/Assets/Image/BE1.png", renderer, true);
    explosion[1] = loadTexture("Source/Assets/Image/BE2.png", renderer, true);
    explosion[2] = loadTexture("Source/Assets/Image/BE3.png", renderer, true);
    explosion[3] = loadTexture("Source/Assets/Image/BE4.png", renderer, true);
    explosion[4] = loadTexture("Source/Assets/Image/BE5.png", renderer, true);
    explosion[5] = loadTexture("Source/Assets/Image/BE6.png", renderer, true);
    explosion[6] = loadTexture("Source/Assets/Image/BE7.png", renderer, true);
    explosion[7] = loadTexture("Source/Assets/Image/BE8.png", renderer, true);
    explosion[8] = loadTexture("Source/Assets/Image/BE9.png", renderer, true);
    hitBox.x = 800;
    hitBox.y = 150;
    hitBox.w = 240;
    hitBox.h = 200;
    hp = 100;
    phi = M_PI;
    status = WAIT;
}
void BigChicken :: add(Interface &itf){
    hp = 100 * itf.wave;
    hitBox.x = 800;
    hitBox.y = 150;
    hitBox.w = 240;
    hitBox.h = 200;
    phi = M_PI;
}
void BigChicken :: generatePos(){
    phi = (phi + M_PI/180);
    hitBox.x = 280 + (double)244 * cos(phi);
    hitBox.y = 150 + (double)170 * sin(phi);
    if(phi == 2*M_PI) phi = 0;
}
void BigChicken :: render(SDL_Renderer *renderer, Interface &itf){
    if(status == WAIT || status == DEAD) return;
    if(status == ADD){
        itf.text.render(renderer, "Boss Is Coming!", 300, 400, 0.75, true);
        if(hitBox.x == 36) status = ALIVE;
        else {
            hitBox.x -= 4;
        }
    }
    if(status == ALIVE ){
        generatePos();
    }
    static int ani = 0;
    SDL_RenderCopy(renderer, bigChickenIMG[ani++ / 4], NULL, &hitBox);
    ani = ani % 72;
}
void BigChicken :: checkCollision(Bullet &bullets, PlayerShip &player, Interface &itf){
    if(status == WAIT || status == DEAD) return;
    SDL_Rect RHB = hitBox;
    RHB.x += 40;
    RHB.h = 150;
    RHB.w = 160;
    for(int k = 0; k < (int)bullets.bullet1.size(); k++){
        if(SDL_HasIntersection(&RHB, &bullets.bullet1[k])){
            hp--;
            bullets.bullet1.erase(bullets.bullet1.begin() + k);
            k--;
            continue;
        }
     }
    for(int k = 0; k < (int)bullets.bullet2.size(); k++){
        if(SDL_HasIntersection(&RHB, &bullets.bullet2[k])){
            hp -= 2;
            bullets.bullet2.erase(bullets.bullet2.begin() + k);
            k--;
            continue;
        }
    }
    for(int k = 0; k < (int)bullets.bullet3.size(); k++){
        if(SDL_HasIntersection(&RHB, &bullets.bullet3[k])){
            hp -= 3;
            bullets.bullet3.erase(bullets.bullet3.begin() + k);
            k--;
            continue;
        }
    }
    if(SDL_HasIntersection(&RHB, &player.hitBox)){
        player.hp = 0;
    }
    cout << hp << endl;
    if(hp <= 0) {
        itf.score += itf.wave * 3000;
        status = DEAD;
    }
}
bool BigChicken :: renderDead(SDL_Renderer *renderer){
    static int ani = 0;
    if(status == DEAD){
        SDL_RenderCopy(renderer, explosion[ani++ / 6], NULL, &hitBox);
        if(ani == 53){
            ani = 0;
            return true;
        }
    }
    return false;
}











