#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <Windows.h>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <ctime>
#include <cstdlib> 
#include "DirectXMath.h"
#include <vector>

const int SCREEN_WIDTH = 1640;
const int SCREEN_HEIGHT = 1020;

SDL_Texture* RenderText(std::string message, std::string fontFile,
		SDL_Color color, int fontSize, SDL_Renderer* renderer);

void renderTexture(SDL_Texture *texture, SDL_Renderer *ren, int x, int y);

#endif
