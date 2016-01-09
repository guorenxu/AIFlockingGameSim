#include "TeamStates.h"

Offensive* Offensive::Instance()
{
	static Offensive instance;
	
	return &instance;
}

void Offensive::Enter(Team* team)
{
}

void Offensive::Execute(Team* team)
{
	if (team->TheirScore - team->OurScore < 5)
	{
		team->ChangeState(Defensive::Instance());
	}

	for (int i = 0; i < team->MyTeamVector->size(); i++)
	{
		team->MyTeamVector->at(i)->ExecuteCurrentState();
	}
}

void Offensive::Exit(Team* team)
{
}

Defensive* Defensive::Instance()
{
	static Defensive instance;
	
	return &instance;
}

void Defensive::Enter(Team* team)
{
}

void Defensive::Execute(Team* team)
{
	if (team->TheirScore - team->OurScore >5)
	{
		team->ChangeState(Offensive::Instance());
	}

	for (int i = 0; i < team->MyTeamVector->size(); i++)
	{
		team->MyTeamVector->at(i)->ExecuteCurrentState();
	}
}

void Defensive::Exit(Team* team)
{
}