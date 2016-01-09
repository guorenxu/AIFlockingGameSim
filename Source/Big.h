#ifndef BIG_H
#define BIG_H

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib> 
#include "DirectXMath.h"
#include "SDL.h"
#include <vector>
#include "Entity.h"
#include "BigStates.h"
#include "State.h"
#include <SDL_ttf.h>
#include "Util.h"
#include <sstream>
#include "Team.h"

template <class entity_type> class State; 

class Small;
class Team;

using namespace std;
using namespace DirectX;

class Big : public Entity
{
private :

public:
	Big(int id, int teamID, int role, float locationx, float locationy, float directionx, float directiony, SDL_Texture* playertex, SDL_Texture* pointingtex, SDL_Renderer* renderer, vector<Small*>* smallvector, vector<Big*>* myteamvector, vector<Big*>* otherteamvector, Team* myteam, int sw, int sh) :
	Entity(id, locationx, locationy, directionx, directiony, playertex, pointingtex, renderer, sw, sh)
	{
		TeamID = teamID;

		MyTeam = myteam;

		SmallVector = smallvector;

		MyTeamVector = myteamvector;

		OtherTeamVector = otherteamvector;

		Role = role;

		NumSmallsFollowing = 0;

		StealerID = -1;

		SDL_Color colorone = { 255, 255, 0 };
		SDL_Color colortwo = { 0, 255, 255 };
		SDL_Color colorthree = { 255, 0, 255 };
		SDL_Color colorfour = { 255, 255, 255 };
		SDL_Color colorfive = { 125, 255, 125 };

		ChaseTextTex = RenderText("ChaseAll", "arial.ttf", colorone, 20, Renderer);

		FleeTextTex = RenderText("Flee", "arial.ttf", colortwo, 20, Renderer);

		StealTextTex = RenderText("Steal", "arial.ttf", colorthree, 20, Renderer);

		NumberTextTex = RenderText("0", "arial.ttf", colorfour, 20, Renderer);

		AvoidStealerTextTex = RenderText("AvoidStealer", "arial.ttf", colorfive, 20, Renderer);
	}

	~Big()
	{
		SDL_DestroyTexture(ChaseTextTex);
		SDL_DestroyTexture(FleeTextTex);
		SDL_DestroyTexture(StealTextTex);
		SDL_DestroyTexture(NumberTextTex);
		SDL_DestroyTexture(AvoidStealerTextTex);
	}


//	vector<Enemy>* GroupVector;

//	int ID;

	vector<Small*>* SmallVector;
	vector<Big*>* MyTeamVector;
	vector<Big*>* OtherTeamVector;

	Team* MyTeam;

	int TeamID;

	int Role;

	int NumSmallsFollowing;

	int StealerID;

	Big* StealTarget;

	SDL_Texture* ChaseTextTex;
	SDL_Texture* FleeTextTex;
	SDL_Texture* StealTextTex;
	SDL_Texture* AvoidStealerTextTex;

	SDL_Texture* NumberTextTex;

	void ChaseAll();
	void Flee();
	void Steal();
	void AvoidStealer();

	void Update(int mousex, int mousey);
	void UpdateChaseAll();
	void UpdateFlee();
	void UpdateSteal();
	void UpdateAvoidStealer();

	void Draw();

	void DrawNumFollowingText();
	void DrawStateText();

	State<Big>* CurrentState;

	void ExecuteCurrentState();

	void ChangeState(State<Big>* NewState);

	void renderTexture(SDL_Texture *texture, SDL_Renderer *ren, int x, int y);
};

#endif