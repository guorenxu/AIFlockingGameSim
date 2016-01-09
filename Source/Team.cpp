#include "Team.h"

void Team::ExecuteCurrentState()
{
	CurrentState->Execute(this);
}

void Team::Draw()
{
	for (int i = 0; i < MyTeamVector->size(); i++)
	{
		MyTeamVector->at(i)->Draw();
	}
}

void Team::ChangeState(State<Team>* NewState)
{
	//Exit current state
	CurrentState->Exit(this);

	//Change state to the new state
	CurrentState = NewState;

	//Call Enter for new state
	CurrentState->Enter(this);
}

void Team::UpdateScore(int us, int them)
{
	OurScore = us;
	TheirScore = them;
}