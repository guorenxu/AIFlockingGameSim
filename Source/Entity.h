#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib> 
#include "DirectXMath.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include <vector>
#include "Message.h"

using namespace std;
using namespace DirectX;


class Entity
{

public:
	XMVECTOR Location;
	XMVECTOR PointingOneLocation;
	XMVECTOR PointingTwoLocation;
	XMVECTOR Direction;

	SDL_Renderer* Renderer;

	SDL_Texture* PlayerTex;
	SDL_Texture* PointingTex;

	Message MyMessageBox;

	int ScreenWidth;
	int ScreenHeight;

	int ID;

	Entity(int id, float locationx, float locationy, float directionx, float directiony, SDL_Texture* playertex, SDL_Texture* pointingtex, SDL_Renderer* renderer, int screenwidth, int screenheight)
	{
		ID = id;

		XMVECTOR location = {locationx, locationy};
		XMVECTOR direction = {directionx, directiony};

		Location = location;
		Direction = direction;

		Direction = XMVector2Normalize(Direction);

		PointingOneLocation = Location + (Direction * 70.0f);
		PointingTwoLocation = Location + (Direction * 37.0f);

		Renderer = renderer;

		PlayerTex = playertex;
		PointingTex = pointingtex;

		ScreenWidth = screenwidth;
		ScreenHeight = screenheight;
	}

	virtual ~Entity(){}

	//all entities must implement an update function
	virtual void Update(int mousex, int mousey)=0;

	void BorderRestrict();

	int GetID()const{return ID;}  

	void GiveMessage(Message NewMessage);
};



#endif