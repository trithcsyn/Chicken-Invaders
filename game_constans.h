#ifndef GAME_CONSTANS_H_INCLUDED
#define GAME_CONSTANS_H_INCLUDED

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const char WINDOW_TITLE[] = "Chicken";
//background
const int SPEED_OF_BACKGROUND = 1;
//bullet
const int SPEED_OF_BULLET = 7;
const Uint32 DELAY_BULLET = 200;

//player ship image
const int PLAYER_MID = 0;
const int PLAYER_LEFT = 1;
const int PLAYER_RIGHT = 2;
const int PLAYER_LEFTMID = 3;
const int PLAYER_RIGHTMID = 4;


const int LEFT_EDGE = 36;
const int RIGHT_EDGE = 764;
const int TOP_EDGE = 30;

//Color:
const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};
//default color:
const SDL_Color DEFAULT_COLOR = BLACK_COLOR;

#endif // GAME_CONSTANS_H_INCLUDED
