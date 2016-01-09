#include "Big.h"
#include "Small.h"

void Big::Update(int mousex, int mousey)
{
	XMVECTOR MousePosition = {mousex, mousey, 0.0f, 0.0f};

	XMMATRIX rotationmatrix;
	XMVECTOR playerlocation = MousePosition;

	XMVECTOR leftvector = {0, 0, 0, 0};
	XMVECTOR rightvector = {0, 0, 0, 0};

	XMMATRIX rotationmatrixleft = XMMatrixRotationZ(float(M_PI)/2.0f);
	XMMATRIX rotationmatrixright = XMMatrixRotationZ(float(M_PI)/-2.0f);

	leftvector = XMVector3Transform(Direction, rotationmatrixleft);
	rightvector = XMVector3Transform(Direction, rotationmatrixright);

	Direction = XMVector2Normalize(Direction);

	XMVECTOR differencevector = playerlocation - Location;

	differencevector = XMVector2Normalize(differencevector);

	float radiandifference = XMVectorGetX(XMVector2AngleBetweenNormals(leftvector, differencevector));
	float epsilon = XMVectorGetX(XMVector2AngleBetweenNormals(Direction, differencevector));

	if (radiandifference <= float(M_PI/2.0f)) 
	{
		rotationmatrix = XMMatrixRotationZ(0.03f);

		if (epsilon <= (1.25f * 0.03f))
		{
			Direction = differencevector;
			Direction = XMVector2Normalize(Direction);

		}
		else
		{
			Direction = XMVector3Transform(Direction, rotationmatrix);
			Direction = XMVector2Normalize(Direction);
		}
	}
	else if (radiandifference > float(M_PI/2.0f)) 
	{
		rotationmatrix = XMMatrixRotationZ(-0.03f);

		if (epsilon <= (1.25f * 0.03f))
		{
			Direction = differencevector;
			Direction = XMVector2Normalize(Direction);

		}
		else
		{
			Direction = XMVector3Transform(Direction, rotationmatrix);
			Direction = XMVector2Normalize(Direction);
		}
	}

	Location += (Direction * 3.0f);

	PointingTwoLocation = Location + (Direction * 20.0f);
}

void Big::UpdateChaseAll()
{
	ChaseAll();

	BorderRestrict();

	Location += (Direction * 3.0f);

	PointingTwoLocation = Location + (Direction * 20.0f);
}

void Big::UpdateFlee()
{
	Flee();

	BorderRestrict();

	Location += (Direction * 3.0f);

	PointingTwoLocation = Location + (Direction * 20.0f);
}

void Big::UpdateSteal()
{
	Steal();

	BorderRestrict();

	Location += (Direction * 3.0f);

	PointingTwoLocation = Location + (Direction * 20.0f);
}

void Big::UpdateAvoidStealer()
{
	AvoidStealer();

	BorderRestrict();

	Location += (Direction * 3.0f);

	PointingTwoLocation = Location + (Direction * 20.0f);
}

void Big::ChaseAll()
{
	XMMATRIX rotationmatrix;
	XMVECTOR closestflockmatedifference = {-1000.0f, -1000.0f, 0, 0};

	for (int i = 0; i < SmallVector->size(); i++)
	{
		XMVECTOR tempvector = {XMVectorGetX(SmallVector->at(i)->Location), XMVectorGetY(SmallVector->at(i)->Location), 0, 0};
		XMVECTOR tempdifference = tempvector - Location;

		if (XMVectorGetX(XMVector2Length(tempdifference)) < XMVectorGetX(XMVector2Length(closestflockmatedifference)))
		{
			if (SmallVector->at(i)->TeamID != TeamID)
			{
				closestflockmatedifference = tempdifference;
			}
		}
	}

	XMVECTOR leftvector = {0, 0, 0, 0};
	XMVECTOR rightvector = {0, 0, 0, 0};

	XMMATRIX rotationmatrixleft = XMMatrixRotationZ(float(M_PI)/2.0f);
	XMMATRIX rotationmatrixright = XMMatrixRotationZ(float(M_PI)/-2.0f);

	leftvector = XMVector3Transform(Direction, rotationmatrixleft);
	rightvector = XMVector3Transform(Direction, rotationmatrixright);

	Direction = XMVector2Normalize(Direction);

	XMVECTOR differencevector = closestflockmatedifference;

	differencevector = XMVector2Normalize(differencevector);

	float radiandifference = XMVectorGetX(XMVector2AngleBetweenNormals(leftvector, differencevector));
	float epsilon = XMVectorGetX(XMVector2AngleBetweenNormals(Direction, differencevector));

	if (radiandifference <= float(M_PI/2.0f)) 
	{
		rotationmatrix = XMMatrixRotationZ(0.04);

		if (epsilon <= (1.25f * 0.04))
		{
			Direction = differencevector;
			Direction = XMVector2Normalize(Direction);

		}
		else
		{
			Direction = XMVector3Transform(Direction, rotationmatrix);
			Direction = XMVector2Normalize(Direction);
		}
		}
		else if (radiandifference > float(M_PI/2.0f)) 
		{
		rotationmatrix = XMMatrixRotationZ(-0.04);

		if (epsilon <= (1.25f * 0.04))
		{
			Direction = differencevector;
			Direction = XMVector2Normalize(Direction);

		}
		else
		{
			Direction = XMVector3Transform(Direction, rotationmatrix);
			Direction = XMVector2Normalize(Direction);
		}
	}
}

void Big::Flee()
{
	XMMATRIX rotationmatrix;
	XMVECTOR closestflockmatedifference = {-1000.0f, -1000.0f, 0, 0};

	for (int i = 0; i < OtherTeamVector->size(); i++)
	{
		XMVECTOR tempvector = {XMVectorGetX(OtherTeamVector->at(i)->Location), XMVectorGetY(OtherTeamVector->at(i)->Location), 0, 0};
		XMVECTOR tempdifference = Location - tempvector;

		if (XMVectorGetX(XMVector2Length(tempdifference)) < XMVectorGetX(XMVector2Length(closestflockmatedifference)))
		{
			if (OtherTeamVector->at(i)->TeamID != TeamID)
			{
				closestflockmatedifference = tempdifference;
			}
		}
	}

	XMVECTOR leftvector = {0, 0, 0, 0};
	XMVECTOR rightvector = {0, 0, 0, 0};

	XMMATRIX rotationmatrixleft = XMMatrixRotationZ(float(M_PI)/2.0f);
	XMMATRIX rotationmatrixright = XMMatrixRotationZ(float(M_PI)/-2.0f);

	leftvector = XMVector3Transform(Direction, rotationmatrixleft);
	rightvector = XMVector3Transform(Direction, rotationmatrixright);

	Direction = XMVector2Normalize(Direction);

	XMVECTOR differencevector = closestflockmatedifference;

	differencevector = XMVector2Normalize(differencevector);

	float radiandifference = XMVectorGetX(XMVector2AngleBetweenNormals(leftvector, differencevector));
	float epsilon = XMVectorGetX(XMVector2AngleBetweenNormals(Direction, differencevector));

	if (radiandifference <= float(M_PI/2.0f)) 
	{
		rotationmatrix = XMMatrixRotationZ(0.04);

		if (epsilon <= (1.25f * 0.04))
		{
			Direction = differencevector;
			Direction = XMVector2Normalize(Direction);

		}
		else
		{
			Direction = XMVector3Transform(Direction, rotationmatrix);
			Direction = XMVector2Normalize(Direction);
		}
		}
		else if (radiandifference > float(M_PI/2.0f)) 
		{
		rotationmatrix = XMMatrixRotationZ(-0.04);

		if (epsilon <= (1.25f * 0.04))
		{
			Direction = differencevector;
			Direction = XMVector2Normalize(Direction);

		}
		else
		{
			Direction = XMVector3Transform(Direction, rotationmatrix);
			Direction = XMVector2Normalize(Direction);
		}
	}
}

void Big::AvoidStealer()
{
	XMMATRIX rotationmatrix;
	XMVECTOR closestflockmatedifference = {-1000.0f, -1000.0f, 0, 0};

	for (int i = 0; i < OtherTeamVector->size(); i++)
	{
		XMVECTOR tempvector = {XMVectorGetX(OtherTeamVector->at(i)->Location), XMVectorGetY(OtherTeamVector->at(i)->Location), 0, 0};
		XMVECTOR tempdifference = Location - tempvector;

		if (OtherTeamVector->at(i)->ID == StealerID)
		{
			closestflockmatedifference = tempdifference;
		}
	}

	XMVECTOR leftvector = {0, 0, 0, 0};
	XMVECTOR rightvector = {0, 0, 0, 0};

	XMMATRIX rotationmatrixleft = XMMatrixRotationZ(float(M_PI)/2.0f);
	XMMATRIX rotationmatrixright = XMMatrixRotationZ(float(M_PI)/-2.0f);

	leftvector = XMVector3Transform(Direction, rotationmatrixleft);
	rightvector = XMVector3Transform(Direction, rotationmatrixright);

	Direction = XMVector2Normalize(Direction);

	XMVECTOR differencevector = closestflockmatedifference;

	differencevector = XMVector2Normalize(differencevector);

	float radiandifference = XMVectorGetX(XMVector2AngleBetweenNormals(leftvector, differencevector));
	float epsilon = XMVectorGetX(XMVector2AngleBetweenNormals(Direction, differencevector));

	if (radiandifference <= float(M_PI/2.0f)) 
	{
		rotationmatrix = XMMatrixRotationZ(0.04);

		if (epsilon <= (1.25f * 0.04))
		{
			Direction = differencevector;
			Direction = XMVector2Normalize(Direction);

		}
		else
		{
			Direction = XMVector3Transform(Direction, rotationmatrix);
			Direction = XMVector2Normalize(Direction);
		}
		}
		else if (radiandifference > float(M_PI/2.0f)) 
		{
		rotationmatrix = XMMatrixRotationZ(-0.04);

		if (epsilon <= (1.25f * 0.04))
		{
			Direction = differencevector;
			Direction = XMVector2Normalize(Direction);

		}
		else
		{
			Direction = XMVector3Transform(Direction, rotationmatrix);
			Direction = XMVector2Normalize(Direction);
		}
	}
}

void Big::Steal()
{
	XMMATRIX rotationmatrix;
	XMVECTOR closestflockmatedifference = {-1000.0f, -1000.0f, 0, 0};

	for (int i = 0; i < SmallVector->size(); i++)
	{
		if (SmallVector->at(i)->TeamID != NONE)
		{
			if (SmallVector->at(i)->Target->ID == StealTarget->ID)
			{
				XMVECTOR tempvector = {XMVectorGetX(SmallVector->at(i)->Location), XMVectorGetY(SmallVector->at(i)->Location), 0, 0};
				XMVECTOR tempdifference = tempvector - Location;

				if (XMVectorGetX(XMVector2Length(tempdifference)) < XMVectorGetX(XMVector2Length(closestflockmatedifference)))
				{
					if (SmallVector->at(i)->TeamID != TeamID)
					{
						closestflockmatedifference = tempdifference;
					}
				}
			}
		}
	}

	XMVECTOR leftvector = {0, 0, 0, 0};
	XMVECTOR rightvector = {0, 0, 0, 0};

	XMMATRIX rotationmatrixleft = XMMatrixRotationZ(float(M_PI)/2.0f);
	XMMATRIX rotationmatrixright = XMMatrixRotationZ(float(M_PI)/-2.0f);

	leftvector = XMVector3Transform(Direction, rotationmatrixleft);
	rightvector = XMVector3Transform(Direction, rotationmatrixright);

	Direction = XMVector2Normalize(Direction);

	XMVECTOR differencevector = closestflockmatedifference;

	differencevector = XMVector2Normalize(differencevector);

	float radiandifference = XMVectorGetX(XMVector2AngleBetweenNormals(leftvector, differencevector));
	float epsilon = XMVectorGetX(XMVector2AngleBetweenNormals(Direction, differencevector));

	if (radiandifference <= float(M_PI/2.0f)) 
	{
		rotationmatrix = XMMatrixRotationZ(0.04);

		if (epsilon <= (1.25f * 0.04))
		{
			Direction = differencevector;
			Direction = XMVector2Normalize(Direction);

		}
		else
		{
			Direction = XMVector3Transform(Direction, rotationmatrix);
			Direction = XMVector2Normalize(Direction);
		}
		}
		else if (radiandifference > float(M_PI/2.0f)) 
		{
		rotationmatrix = XMMatrixRotationZ(-0.04);

		if (epsilon <= (1.25f * 0.04))
		{
			Direction = differencevector;
			Direction = XMVector2Normalize(Direction);

		}
		else
		{
			Direction = XMVector3Transform(Direction, rotationmatrix);
			Direction = XMVector2Normalize(Direction);
		}
	}
}

void Big::ExecuteCurrentState()
{
	CurrentState->Execute(this);
}

void Big::ChangeState(State<Big>* NewState)
{
		//Exit current state
		CurrentState->Exit(this);

		//Change state to the new state
		CurrentState = NewState;

		//Call Enter for new state
		CurrentState->Enter(this);
}


void Big::Draw()
{
	DrawNumFollowingText();
	DrawStateText();

	renderTexture(PlayerTex, Renderer, (XMVectorGetX(Location) - 8.0f), (XMVectorGetY(Location) - 8.0f));
	//renderTexture(PointingTex, Renderer, (XMVectorGetX(PointingOneLocation) - 8.0f), (XMVectorGetY(PointingOneLocation) - 8.0f));
	renderTexture(PointingTex, Renderer, (XMVectorGetX(PointingTwoLocation) - 4.0f), (XMVectorGetY(PointingTwoLocation) - 4.0f));
}

void Big::DrawNumFollowingText()
{
	int a = NumSmallsFollowing;
	stringstream ss;
	ss << a;
	string str = ss.str();

	SDL_Color color = { 255, 255, 255 };

	SDL_DestroyTexture(NumberTextTex);

	NumberTextTex = RenderText(str, "arial.ttf", color, 20, Renderer);

	renderTexture(NumberTextTex, Renderer, (XMVectorGetX(Location)) - 5, (XMVectorGetY(Location) - 35.0f));
}

void Big::DrawStateText()
{
	SDL_Texture* texttex;

	if (CurrentState->StateCode == CHASEALL)
	{
		texttex = ChaseTextTex;
	}
	else if(CurrentState->StateCode == FLEE)
	{
		texttex = FleeTextTex;
	}
	else if(CurrentState->StateCode == STEAL)
	{
		texttex = StealTextTex;
	}
	else // AVOIDSTEALER
	{
		texttex = AvoidStealerTextTex;
	}

	renderTexture(texttex, Renderer, (XMVectorGetX(Location)) + 20, (XMVectorGetY(Location) - 35.0f));
}


void Big::renderTexture(SDL_Texture *texture, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, texture, NULL, &dst);
}