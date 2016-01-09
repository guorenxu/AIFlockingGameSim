#include "BigStates.h"

#define FLEETHRESHOLD 7

ChaseAll* ChaseAll::Instance()
{
	static ChaseAll instance;
	
	return &instance;
}

void ChaseAll::Enter(Big* big)
{
}

void ChaseAll::Execute(Big* big)
{  
	big->UpdateChaseAll();

	int fleethreshold = FLEETHRESHOLD;

	if (big->MyTeam->CurrentState->StateCode == OFFENSIVE)
	{
		fleethreshold++;
	}

	if (big->NumSmallsFollowing >= fleethreshold)
	{
		if (big->MyMessageBox.TypeID == TARGETED && !big->MyMessageBox.IsRead)
		{
			big->ChangeState(AvoidStealer::Instance());
			big->StealerID = big->MyMessageBox.Content;
			big->MyMessageBox.IsRead = true;
		}
		else
		{
			big->ChangeState(Flee::Instance());
		}
	}
	if (!StealSet)
	{
		int graycount = 0;

		for (int i = 0; i < big->SmallVector->size(); i++)
		{
			if (big->SmallVector->at(i)->TeamID == NONE)
			{
				graycount++;
			}
		}

		if (graycount <= 4)
		{
			if (big->Role == STEALER)
			{
				StealSet = true;

				big->ChangeState(Steal::Instance());
			}
		}
	}
}

void ChaseAll::Exit(Big* big)
{
}

Flee* Flee::Instance()
{
	static Flee instance;
	
	return &instance;
}

void Flee::Enter(Big* big)
{
}

void Flee::Execute(Big* big)
{  
	if (big->MyMessageBox.TypeID == TARGETED && !big->MyMessageBox.IsRead)
	{
		big->ChangeState(AvoidStealer::Instance());
		big->StealerID = big->MyMessageBox.Content;
		big->MyMessageBox.IsRead = true;
	}

	int fleethreshold = FLEETHRESHOLD;

	if (big->MyTeam->CurrentState->StateCode == OFFENSIVE)
	{
		fleethreshold++;
	}

	if (big->NumSmallsFollowing < fleethreshold)
	{
		if (big->Role == CHASER)
		{
			big->ChangeState(ChaseAll::Instance());
		}
		else //STEALER
		{
			big->ChangeState(Steal::Instance());
		}
	}

	big->UpdateFlee();
}

void Flee::Exit(Big* big)
{
}

Steal* Steal::Instance()
{
	static Steal instance;
	
	return &instance;
}

void Steal::Enter(Big* big)
{
	XMMATRIX rotationmatrix;
	XMVECTOR closestflockmatedifference = {-1000.0f, -1000.0f, 0, 0};

	int greatestnumfollowers = 0;

	for (int i = 0; i < big->OtherTeamVector->size(); i++)
	{
		XMVECTOR tempvector = {XMVectorGetX(big->OtherTeamVector->at(i)->Location), XMVectorGetY(big->OtherTeamVector->at(i)->Location), 0, 0};
		XMVECTOR tempdifference = big->Location - tempvector;

		if (greatestnumfollowers < big->OtherTeamVector->at(i)->NumSmallsFollowing)
		{
			greatestnumfollowers = big->OtherTeamVector->at(i)->NumSmallsFollowing;

			big->StealTarget = big->OtherTeamVector->at(i);
		}
	}

	big->StealTarget->GiveMessage(Message(TARGETED, big->ID));
}

void Steal::Execute(Big* big)
{  
	int fleethreshold = FLEETHRESHOLD;

	if (big->MyTeam->CurrentState->StateCode == OFFENSIVE)
	{
		fleethreshold++;
	}

	if (big->NumSmallsFollowing >= fleethreshold)
	{
		if (big->MyMessageBox.TypeID == TARGETED && !big->MyMessageBox.IsRead)
		{
			big->ChangeState(AvoidStealer::Instance());
			big->StealerID = big->MyMessageBox.Content;
			big->MyMessageBox.IsRead = true;
		}
		else
		{
			big->ChangeState(Flee::Instance());
		}
	}

	if (big->StealTarget->NumSmallsFollowing <= 3)
	{
		big->ChangeState(Steal::Instance());
	}

	big->UpdateSteal();
}

void Steal::Exit(Big* big)
{
	big->StealTarget->GiveMessage(Message(UNTARGETED, big->ID));
}

AvoidStealer* AvoidStealer::Instance()
{
	static AvoidStealer instance;
	
	return &instance;
}

void AvoidStealer::Enter(Big* big)
{
}

void AvoidStealer::Execute(Big* big)
{  
	if (big->MyMessageBox.TypeID == UNTARGETED && !big->MyMessageBox.IsRead)
	{
		big->ChangeState(Flee::Instance());
		big->MyMessageBox.IsRead = true;
	}

	int fleethreshold = FLEETHRESHOLD;

	if (big->MyTeam->CurrentState->StateCode == OFFENSIVE)
	{
		fleethreshold++;
	}

	if (big->NumSmallsFollowing < fleethreshold)
	{
		if (big->Role == CHASER)
		{
			big->ChangeState(ChaseAll::Instance());
		}
		else //STEALER
		{
			big->ChangeState(Steal::Instance());
		}
	}

	big->UpdateAvoidStealer();
}

void AvoidStealer::Exit(Big* big)
{
}