#ifndef SMALL_H
#define SMALL_H

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib> 
#include "DirectXMath.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include <vector>
#include "Entity.h"
//#include "Big.h"
#include "StateCodes.h"

class Big;

using namespace std;
using namespace DirectX;

class Small : public Entity
{
private :

public:
	Small(int id, float locationx, float locationy, float directionx, float directiony, SDL_Texture* playertex, SDL_Texture* redtex, SDL_Texture* bluetex, SDL_Texture* pointingtex, 
		SDL_Renderer* renderer, vector<Small*>* smallvector, vector<Big*>* bluelist, vector<Big*>* redlist, int sw, int sh) :
	Entity(id, locationx, locationy, directionx, directiony, playertex, pointingtex, renderer, sw, sh)
	{
		Chasing = false;
		Flocking = false;
		TeamID = NONE;
		SmallVector = smallvector;
		RedTex = redtex;
		BlueTex = bluetex;
		RedList = redlist;
		BlueList = bluelist;
	}

	~Small(){}

	vector<Small*>* SmallVector;

	Big* Target;

	SDL_Texture* RedTex;
	SDL_Texture* BlueTex;

	vector<Big*>* RedList;
	vector<Big*>* BlueList;

	int TeamID;

	bool Chasing;
	bool Flocking;

	void Update(int mousex, int mousey);

	void Draw();

	void Cohesion(float weight);
	void Alignment(float weight);
	void Separation(float weight);
	void Chase(float weight);

	void BigDetect();

	void SetChaseTarget(Big* target);

	void renderTexture(SDL_Texture *texture, SDL_Renderer *ren, int x, int y);
};

#endif