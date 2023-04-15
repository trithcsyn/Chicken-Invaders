#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include<vector>
#include<ctime>
#include<iostream>
#include <SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>
#include<fstream>
#include<cmath>
using namespace std;


void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren, bool check = false);


void renderTexture(SDL_Texture *tex, SDL_Renderer *ren,const int &x,const int &y);


void renderTexture(SDL_Texture *tex, SDL_Renderer *ren,const int &x, const int &y,const int &w,const int &h);

#endif // SDL_UTILS_H
