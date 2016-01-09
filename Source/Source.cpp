#include <iostream>
#include <Windows.h>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Big.h"
#include "Small.h"
#include <ctime>
#include <cstdlib> 
#include "DirectXMath.h"
#include <vector>
#include "Util.h"
#include "StateMachine.h"

using namespace std;
using namespace DirectX;

int bluescore = 0;
int redscore = 0;

SDL_Texture* BigRedTex;
SDL_Texture* BigBlueTex;
SDL_Texture* SmallGrayTex;
SDL_Texture* SmallRedTex;
SDL_Texture* SmallBlueTex;
SDL_Texture* SmallPointTex;
SDL_Texture* BigPointTex;

SDL_Texture* BlueScoreTex;
SDL_Texture* RedScoreTex;

vector<Small*> FlockerVector;

StateMachine* GameStateMachine;

long int start = GetTickCount();
int DeltaTime = 0;

void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg.c_str() << " error: " << SDL_GetError() << std::endl;
}

int main(int argc, char **argv)
{
	srand (time(NULL));

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	if (TTF_Init() == -1){
		std::cout << TTF_GetError() << std::endl;
		return 2;
	}

	//if (IMG_Init(IMG_INIT_PNG) != 0)
	//{
	//	logSDLError(std::cout, "SDL_Init");
	//	return 1;
	//}


	SDL_Window *win = SDL_CreateWindow("Midterm Project", 100, 100, 
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		logSDLError(std::cout, "CreateWindow");
		return 2;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr)
	{
		logSDLError(std::cout, "CreateRenderer");
		return 3;
	}

	GameStateMachine = new StateMachine(renderer);

	GameStateMachine->Init();

	SDL_Event* event;

	bool gameover = false;

	while (!gameover)
	{
		if (GetTickCount() - 15 >= start)
		{
			DeltaTime = GetTickCount() - start;
			start = GetTickCount();

			const Uint8 *state = SDL_GetKeyboardState(NULL);
		
			int* mouseposx = new int;
			int* mouseposy = new int;

			SDL_GetMouseState(mouseposx, mouseposy);

			XMVECTOR MousePosition = {*mouseposx, *mouseposy, 0.0f, 0.0f};

			SDL_PumpEvents();

			if (state[SDL_SCANCODE_ESCAPE]) 
			{
				gameover = true;
			}

			GameStateMachine->Run();

			SDL_RenderPresent(renderer);
		}
	}

	SDL_DestroyTexture(BigRedTex);
	SDL_DestroyTexture(BigBlueTex);
	SDL_DestroyTexture(SmallGrayTex);
	SDL_DestroyTexture(SmallRedTex);
	SDL_DestroyTexture(SmallBlueTex);
	SDL_DestroyTexture(SmallPointTex);
	SDL_DestroyTexture(SmallPointTex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}