#include "Small.h"
#include "Big.h"

void Small::Draw()
{
	if (TeamID == NONE)
	{
		renderTexture(PlayerTex, Renderer, (XMVectorGetX(Location) - 4.0f), (XMVectorGetY(Location) - 4.0f));
	}
	else if (TeamID == RED)
	{
		renderTexture(RedTex, Renderer, (XMVectorGetX(Location) - 4.0f), (XMVectorGetY(Location) - 4.0f));
	}
	else //(TeamID == BLUE)
	{
		renderTexture(BlueTex, Renderer, (XMVectorGetX(Location) - 4.0f), (XMVectorGetY(Location) - 4.0f));
	}

	//renderTexture(PointingTex, Renderer, (XMVectorGetX(PointingOneLocation) - 8.0f), (XMVectorGetY(PointingOneLocation) - 8.0f));
	if (TeamID != NONE)
	{
		renderTexture(PointingTex, Renderer, (XMVectorGetX(PointingTwoLocation) - 2.0f), (XMVectorGetY(PointingTwoLocation) - 2.0f));
	}
}


void Small::renderTexture(SDL_Texture *texture, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, texture, NULL, &dst);
}

void Small::Cohesion(float weight)
{
	XMMATRIX rotationmatrix;
	XMVECTOR flocktotal = {0, 0, 0, 0};

	bool isalone = true;

	for (int i = 0; i < SmallVector->size(); i++)
	{
		if (SmallVector->at(i)->ID != this->ID)
		{
			if (SmallVector->at(i)->Chasing)
			{
				if (Target->ID == SmallVector->at(i)->Target->ID)
				{
					flocktotal += SmallVector->at(i)->Location;
					isalone = false;
				}
			}
		}
	}

	if (!isalone)
	{
		XMVECTOR flockaverage = flocktotal / SmallVector->size();

		XMVECTOR leftvector = {0, 0, 0, 0};
		XMVECTOR rightvector = {0, 0, 0, 0};

		XMMATRIX rotationmatrixleft = XMMatrixRotationZ(float(M_PI)/2.0f);
		XMMATRIX rotationmatrixright = XMMatrixRotationZ(float(M_PI)/-2.0f);

		leftvector = XMVector3Transform(Direction, rotationmatrixleft);
		rightvector = XMVector3Transform(Direction, rotationmatrixright);

		Direction = XMVector2Normalize(Direction);

		XMVECTOR differencevector = flockaverage - Location;

		differencevector = XMVector2Normalize(differencevector);

		float radiandifference = XMVectorGetX(XMVector2AngleBetweenNormals(leftvector, differencevector));
		float epsilon = XMVectorGetX(XMVector2AngleBetweenNormals(Direction, differencevector));

		if (radiandifference <= float(M_PI/2.0f)) 
		{
			rotationmatrix = XMMatrixRotationZ(weight);

			if (epsilon <= (1.25f * weight))
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
			rotationmatrix = XMMatrixRotationZ(-weight);

			if (epsilon <= (1.25f * weight))
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
}

void Small::Alignment(float weight)
{
	XMMATRIX rotationmatrix;
	XMVECTOR flockalignmenttotal = {0, 0, 0, 0};

	bool isalone = true;

	for (int i = 0; i < SmallVector->size(); i++)
	{
		if (SmallVector->at(i)->ID != this->ID)
		{
			if (SmallVector->at(i)->Chasing)
			{
				if (Target->ID == SmallVector->at(i)->Target->ID)
				{
					flockalignmenttotal += SmallVector->at(i)->Direction;
					isalone = false;
				}
			}
		}
	}

	if (!isalone)
	{
		XMVECTOR flockalignmentaverage = flockalignmenttotal / SmallVector->size();

		XMVECTOR leftvector = {0, 0, 0, 0};
		XMVECTOR rightvector = {0, 0, 0, 0};

		XMMATRIX rotationmatrixleft = XMMatrixRotationZ(float(M_PI)/2.0f);
		XMMATRIX rotationmatrixright = XMMatrixRotationZ(float(M_PI)/-2.0f);

		leftvector = XMVector3Transform(Direction, rotationmatrixleft);
		rightvector = XMVector3Transform(Direction, rotationmatrixright);

		Direction = XMVector2Normalize(Direction);

		XMVECTOR differencevector = flockalignmentaverage;

		differencevector = XMVector2Normalize(differencevector);

		float radiandifference = XMVectorGetX(XMVector2AngleBetweenNormals(leftvector, differencevector));
		float epsilon = XMVectorGetX(XMVector2AngleBetweenNormals(Direction, differencevector));

		if (radiandifference <= float(M_PI/2.0f)) 
		{
			rotationmatrix = XMMatrixRotationZ(weight);

			if (epsilon <= (1.25f * weight))
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
			rotationmatrix = XMMatrixRotationZ(-weight);

			if (epsilon <= (1.25f * weight))
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
}

void Small::Separation(float weight)
{
	XMMATRIX rotationmatrix;
	XMVECTOR closestflockmatedifference = {-1000.0f, -1000.0f, 0, 0};

	bool isalone = true;

	for (int i = 0; i < SmallVector->size(); i++)
	{
		if (SmallVector->at(i)->ID != this->ID)
		{
			if (SmallVector->at(i)->Chasing)
			{
				if (Target->ID == SmallVector->at(i)->Target->ID)
				{
					XMVECTOR tempvector = {XMVectorGetX(SmallVector->at(i)->Location), XMVectorGetY(SmallVector->at(i)->Location), 0, 0};
					XMVECTOR tempdifference = Location - tempvector;

					if (XMVectorGetX(XMVector2Length(tempdifference)) < XMVectorGetX(XMVector2Length(closestflockmatedifference)))
					{
						closestflockmatedifference = tempdifference;
						isalone = false;
					}
				}
			}
		}
	}

	if (!isalone)
	{
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
			rotationmatrix = XMMatrixRotationZ(weight);

			if (epsilon <= (1.25f * weight))
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
			rotationmatrix = XMMatrixRotationZ(-weight);

			if (epsilon <= (1.25f * weight))
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
}

void Small::Chase(float weight)
{
	XMMATRIX rotationmatrix;
	XMVECTOR playerlocation = Target->Location;

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
		rotationmatrix = XMMatrixRotationZ(weight);

		if (epsilon <= (1.25f * weight))
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
		rotationmatrix = XMMatrixRotationZ(-weight);

		if (epsilon <= (1.25f * weight))
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

void Small::Update(int mousex, int mousey)
{
	//XMVECTOR playerlocation = {playerx, playery, 0, 0};

	//float displacement = XMVectorGetX(XMVector2Length(playerlocation - Location));

	//if (displacement <= 130.0f)
	//{
		//Separation(0.000f);
		//Cohesion(0.000f);
		//Alignment(0.0f);
		//Chase(0.03f);
	//}
	//else
	//{
	if (Flocking)
	{
		Separation(0.04f);
		Cohesion(0.01f);
		Alignment(0.01f);
	}
	else
	{
		//Wander
	}

	if (Chasing)
	{
		Chase(0.05f);
	}

	BorderRestrict();

	if (Chasing)
	{	
		Location += (Direction * 3.3f);
	}

	PointingTwoLocation = Location + (Direction * 10.0f);
}

void Small::SetChaseTarget(Big* target)
{
	if (TeamID != NONE)
	{
		//Old target loses one "follower"
		Target->NumSmallsFollowing--;
	}

	//Set new target
	Target = target;

	//New target gains one "follower"
	Target->NumSmallsFollowing++;
}

void Small::BigDetect()
{
	if (TeamID != RED)
	{
		for (int i = 0; i < RedList->size(); i++)
		{
			XMVECTOR tempvector = {XMVectorGetX(RedList->at(i)->Location), XMVectorGetY(RedList->at(i)->Location), 0, 0};
			XMVECTOR tempdifference = Location - tempvector;

			if (XMVectorGetX(XMVector2Length(tempdifference)) < 40)
			{
				SetChaseTarget(RedList->at(i));
				TeamID = Target->TeamID;
				Chasing = true;
				Flocking = true;
			}
		}
	}

	if (TeamID != BLUE)
	{
		for (int i = 0; i < BlueList->size(); i++)
		{
			XMVECTOR tempvector = {XMVectorGetX(BlueList->at(i)->Location), XMVectorGetY(BlueList->at(i)->Location), 0, 0};
			XMVECTOR tempdifference = Location - tempvector;

			if (XMVectorGetX(XMVector2Length(tempdifference)) < 40)
			{
				SetChaseTarget(BlueList->at(i));
				TeamID = Target->TeamID;
				Chasing = true;
				Flocking = true;
			}
		}
	}
}