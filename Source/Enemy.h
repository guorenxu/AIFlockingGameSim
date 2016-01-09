#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib> 
#include "DirectXMath.h"
#include "SDL.h"
#include <vector>

using namespace std;
using namespace DirectX;

class Enemy
{
private :

public:
	Enemy(float locationx, float locationy, float directionx, float directiony, int id, SDL_Texture* playertex, SDL_Texture* pointingtex, SDL_Renderer* renderer, vector<Enemy>* groupvector);
	~Enemy();

	XMVECTOR Location;
	XMVECTOR PointingOneLocation;
	XMVECTOR PointingTwoLocation;
	XMVECTOR Direction;

	SDL_Renderer* Renderer;

	SDL_Texture* PlayerTex;
	SDL_Texture* PointingTex;

	vector<Enemy>* GroupVector;

	int ID;

	void Update(float playerx, float playery);

	void SetSprites();

	void Draw();

	void Cohesion(float weight);
	void Alignment(float weight);
	void Separation(float weight);
	void Chase(float playerx, float playery, float weight);

	void renderTexture(SDL_Texture *texture, SDL_Renderer *ren, int x, int y);
};

#endif