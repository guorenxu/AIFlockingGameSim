#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib> 
#include "DirectXMath.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include <vector>

using namespace std;
using namespace DirectX;


class Message
{
public:
	Message(int typeID, int content)
	{
		TypeID = typeID;
		Content = content;

		IsRead = false;
	};

	Message()
	{
		TypeID = 10000;
		Content = 10000;

		IsRead = true;
	};

	void Init(int ti, int c);

	int TypeID;
	int Content;
	bool IsRead;
};

#endif