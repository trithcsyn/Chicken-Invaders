#include "SDL_utils.h"


//*****************************************************
// Struct
struct Position{
    int x, y, w, h;

    Position(int x, int y, int w = 0, int h = 0){
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

};

//*****************************************************
//Variable
SDL_Window* window;
SDL_Renderer* renderer;

SDL_Texture* backGround;
SDL_Rect clipBackground;

SDL_Texture* playerIMG[5];
Position player(SCREEN_WIDTH/2 - 84/2, SCREEN_HEIGHT - 90, 74 , 84);
int preMove = -1;

SDL_Texture* bulletIMG;
vector<Position> bullet;



//*****************************************************
// Các hàm chung về khởi tạo và huỷ SDL

void updateBullet(){
    bullet.push_back({player.x + 32, player.y + -37});
}

void renderBullet(){
    for(int i = 0; i < (int)bullet.size(); i++){
        if(bullet[i].y > 0){
        renderTexture(bulletIMG, bullet[i].x, bullet[i].y);
        bullet[i].y -= 5;
        }
        else {
                bullet.erase(bullet.begin() + i);
                i--;
        }
    }
}


void renderPlayer(){
    if(preMove == -1) renderTexture(playerIMG[PLAYER_MID], player.x, player.y);
        else{
            if(player.x - preMove > 30) renderTexture(playerIMG[PLAYER_RIGHT], player.x, player.y);
            if(preMove - player.x > 30) renderTexture(playerIMG[PLAYER_LEFT], player.x, player.y);
            if(player.x - preMove <= 30 && player.x > preMove) renderTexture(playerIMG[PLAYER_RIGHTMID], player.x, player.y);
            if(preMove - player.x <= 30 && preMove > player.x) renderTexture(playerIMG[PLAYER_LEFTMID], player.x, player.y);
            if(preMove == player.x) renderTexture(playerIMG[PLAYER_MID], player.x, player.y);
        }
}

void updatePositionPlayer(){
    preMove = player.x;
    SDL_GetMouseState(&player.x, &player.y);
    player.x -= 37;
    player.y -= 84;
}

void renderScreen(){
    SDL_RenderPresent(renderer);
}

void load_SDL_IMG(){
    initSDL( SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    bulletIMG = loadTexture("imagesource/bullet.png");
    if(bulletIMG == nullptr) logSDLError(std :: cout, "loadBullet");

    clipBackground.x = 0;
    clipBackground.y = 1200;
    clipBackground.w = SCREEN_WIDTH;
    clipBackground.h = SCREEN_HEIGHT;

    backGround = loadTexture("imagesource/background.png");
    if(backGround == nullptr) logSDLError(std::cout,"loadBackground", true );
    else{
        playerIMG[PLAYER_MID] = loadTexture("imagesource/player_ship.png");
        playerIMG[PLAYER_LEFT] = loadTexture("imagesource/player_ship_left.png");
        playerIMG[PLAYER_RIGHT] = loadTexture("imagesource/player_ship_right.png");
        playerIMG[PLAYER_LEFTMID] = loadTexture("imagesource/player_ship_leftmid.png");
        playerIMG[PLAYER_RIGHTMID] = loadTexture("imagesource/player_ship_rightmid.png");
        for(int i = 0; i < 5; i++){
            if(playerIMG[i] == nullptr){
                logSDLError(std :: cout, "loadPlayerShip", true);
                break;
            }
        }
    }
}

void renderBackground(){
    SDL_RenderCopy(renderer, backGround, &clipBackground, NULL);
    clipBackground.y = (clipBackground.y - 1 + 1200)% 1200;
}

void initSDL(int screenWidth, int screenHeight, const char* windowTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //   SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
//    renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
}

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}


void quitSDL()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

/**
* Nạp một ảnh bitmap (BMP) vào một texture trên thiết bị hiện thị (rendering device)
* @param file: đường dẫn và tên file ảnh BMP
* @param ren: renderer để nạp texture lên
* @return trả về texture đã nạp, hoặc nullptr nếu có lỗi.
*/
SDL_Texture* loadTexture(const std::string &file)
{
	//Khởi tạo là nullptr để tránh lỗi 'dangling pointer'
	SDL_Texture *texture = nullptr;
	//Nạp ảnh từ tên file (với đường dẫn)
	SDL_Surface *loadedImage = IMG_Load(file.c_str());
	//Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Đảm bảo việc chuyển đổi không có lỗi
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), trong khi
* giữ nguyên chiều rộng và cao của ảnh
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
*/
void renderTexture(SDL_Texture *tex, int x, int y)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), với
* chiều rộng và cao mới
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
* @param w: chiều rộng (mới)
* @param h: độ cao (mới)
*/
void renderTexture(SDL_Texture *tex, int x, int y, int w, int h)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}
