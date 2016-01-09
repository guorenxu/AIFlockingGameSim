#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib> 
#include "DirectXMath.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include <vector>
#include "Message.h"
#include "Big.h"
#include "Small.h"
#include "TeamStates.h"
#include "State.h"

using namespace std;
using namespace DirectX;

template <class entity_type> class State; 

class Team
{

public:
	int TeamID;

	Team(int teamid, vector<Big*>* myteamvector, vector<Big*>* otherteamvector, vector<Small*>* smallvector)
	{
		TeamID = teamid;

		MyTeamVector = myteamvector;
		OtherTeamVector = otherteamvector;
		SmallVector = smallvector;

		OurScore = 0;
		TheirScore = 0;
	}

	~Team(){}

	void Draw();

	State<Team>* CurrentState;

	void ExecuteCurrentState();

	void ChangeState(State<Team>* NewState);

	void UpdateScore(int us, int them);

	vector<Big*>* MyTeamVector;
	vector<Big*>* OtherTeamVector;
	vector<Small*>* SmallVector;

	int OurScore;
	int TheirScore;
};



#endif