#include "StateMachine.h"

StateMachine::StateMachine(SDL_Renderer* renderer)
{
	Renderer = renderer;

	bluescore = 0;
	redscore = 0;
}

StateMachine::~StateMachine()
{
}

void StateMachine::Init()
{
	RedTeam = new Team(REDTEAM, &RedList, &BlueList, &FlockerVector);
	BlueTeam = new Team(BLUETEAM, &BlueList, &RedList, &FlockerVector);

	RedTeam->CurrentState = Defensive::Instance();
	BlueTeam->CurrentState = Defensive::Instance();

	BigRedTex = IMG_LoadTexture(Renderer, "art/BigR.png");
	BigBlueTex = IMG_LoadTexture(Renderer, "art/BigB.png");
	SmallGrayTex = IMG_LoadTexture(Renderer, "art/smallG.png");
	SmallRedTex = IMG_LoadTexture(Renderer, "art/smallR.png");
	SmallBlueTex = IMG_LoadTexture(Renderer, "art/smallB.png");
	SmallPointTex = IMG_LoadTexture(Renderer, "art/Spoint.png");
	BigPointTex = IMG_LoadTexture(Renderer, "art/Bpoint.png");

	int numiterations = 6;

	for (int i = 0; i < numiterations; i++)
	{
		if (i == 0 || i == 1)
		{
			BlueList.push_back(new Big(i, BLUE, STEALER, 100.0f, 100 + (((SCREEN_HEIGHT - 200) / numiterations) * i) , 1.0f, 0.0f, BigBlueTex, BigPointTex, Renderer, &FlockerVector, &BlueList, &RedList, BlueTeam, SCREEN_WIDTH, SCREEN_HEIGHT));
		}
		else
		{
			BlueList.push_back(new Big(i, BLUE, CHASER, 100.0f, 100 + (((SCREEN_HEIGHT - 200) / numiterations) * i) , 1.0f, 0.0f, BigBlueTex, BigPointTex, Renderer, &FlockerVector, &BlueList, &RedList, BlueTeam, SCREEN_WIDTH, SCREEN_HEIGHT));
		}

		BlueList[i]->CurrentState = ChaseAll::Instance();
	}

	for (int i = 0; i < numiterations; i++)
	{
		if (i == 0 || i == 1)
		{
			RedList.push_back(new Big(i + numiterations, RED, STEALER, (SCREEN_WIDTH - 100), 100 + (((SCREEN_HEIGHT - 200) / numiterations) * i) , -1.0f, 0.0f, BigRedTex, BigPointTex, Renderer, &FlockerVector, &RedList, &BlueList, RedTeam, SCREEN_WIDTH, SCREEN_HEIGHT));
		}
		else
		{
			RedList.push_back(new Big(i + numiterations, RED, CHASER, (SCREEN_WIDTH - 100), 100 + (((SCREEN_HEIGHT - 200) / numiterations) * i) , -1.0f, 0.0f, BigRedTex, BigPointTex, Renderer, &FlockerVector, &RedList, &BlueList, RedTeam, SCREEN_WIDTH, SCREEN_HEIGHT));
		}

		RedList[i]->CurrentState = ChaseAll::Instance();
	}

	for (int i = 0; i < 80; i++)
	{
		FlockerVector.push_back(new Small(i, rand()%(SCREEN_WIDTH - 120) + 60, rand()%(SCREEN_HEIGHT - 120) + 60, (float(rand()%201 - 100) / 100.0f), (float(rand()%201 - 100) / 100.0f), 
			SmallGrayTex, SmallRedTex, SmallBlueTex, SmallPointTex, Renderer, &FlockerVector, &BlueList, &RedList, SCREEN_WIDTH, SCREEN_HEIGHT));
	}
}

void StateMachine::Run()
{
	BlueTeam->ExecuteCurrentState();

	RedTeam->ExecuteCurrentState();


	for (int i = 0; i < FlockerVector.size(); i++)
	{
		FlockerVector[i]->Update(0,0);
		FlockerVector[i]->BigDetect();
	}

	SDL_RenderClear(Renderer);

	BlueTeam->Draw();

	RedTeam->Draw();

	for (int i = 0; i < FlockerVector.size(); i++)
	{
		FlockerVector[i]->Draw();
	}

	redscore = 0;
	bluescore = 0;

	for (int i = 0; i < FlockerVector.size(); i++)
	{
		if (FlockerVector[i]->TeamID == BLUE)
		{
			bluescore++;
		}
		else if (FlockerVector[i]->TeamID == RED)
		{
			redscore++;
		}
	}

	stringstream ss;
	ss << bluescore;
	string str = ss.str();

	SDL_Color color = { 0, 0, 255 };

	if (BlueTeam->CurrentState->StateCode == DEFENSIVE)
	{
		color.r = 200;
		color.g = 200;
	}

	SDL_DestroyTexture(BlueScoreTex);

	BlueScoreTex = RenderText(str, "arial.ttf", color, 70, Renderer);

	renderTexture(BlueScoreTex, Renderer, 100, 70);

	stringstream sss;
	sss << redscore;
	string strs = sss.str();

	SDL_Color colortwo = { 255, 0, 0 };

	if (RedTeam->CurrentState->StateCode == DEFENSIVE)
	{
		colortwo.b = 200;
		colortwo.g = 200;
	}

	SDL_DestroyTexture(RedScoreTex);

	RedScoreTex = RenderText(strs, "arial.ttf", colortwo, 70, Renderer);

	renderTexture(RedScoreTex, Renderer, 1000, 70);

	BlueTeam->UpdateScore(bluescore, redscore);
	RedTeam->UpdateScore(redscore, bluescore);
}

void StateMachine::renderTexture(SDL_Texture *texture, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, texture, NULL, &dst);
}