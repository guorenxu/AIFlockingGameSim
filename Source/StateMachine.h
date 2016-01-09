#ifndef STATEMACHINE_H
#define STATEMACHINE_H

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
#include "Team.h"

class StateMachine
{
private :

public:
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
	vector<Big*> BlueList;
	vector<Big*> RedList;

	SDL_Renderer* Renderer;

	Team* RedTeam;
	Team* BlueTeam;

	int redscore;
	int bluescore;

	StateMachine(SDL_Renderer* renderer);
	~StateMachine();

	void renderTexture(SDL_Texture *texture, SDL_Renderer *ren, int x, int y);

	void Init();

	void Run();			
};

#endif