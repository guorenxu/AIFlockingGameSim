#include "Enemy.h"

Enemy::Enemy(float locationx, float locationy, float directionx, float directiony, int id, SDL_Texture* playertex, SDL_Texture* pointingtex, SDL_Renderer* renderer, vector<Enemy>* groupvector)
{
	XMVECTOR location = {locationx, locationy};
	XMVECTOR direction = {directionx, directiony};

	Location = location;
	Direction = direction;

	Direction = XMVector2Normalize(Direction);

	PointingOneLocation = Location + (Direction * 70.0f);
	PointingTwoLocation = Location + (Direction * 37.0f);

	ID = id;

	Renderer = renderer;

	PlayerTex = playertex;
	PointingTex = pointingtex;

	GroupVector = groupvector;
}

void Enemy::Cohesion(float weight)
{
	XMMATRIX rotationmatrix;
	XMVECTOR flocktotal = {0, 0, 0, 0};

	for (int i = 0; i < GroupVector->size(); i++)
	{
		if (GroupVector->at(i).ID != this->ID)
		{
			flocktotal += GroupVector->at(i).Location;
		}
	}

	XMVECTOR flockaverage = flocktotal / GroupVector->size();

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

void Enemy::Alignment(float weight)
{
	XMMATRIX rotationmatrix;
	XMVECTOR flockalignmenttotal = {0, 0, 0, 0};

	for (int i = 0; i < GroupVector->size(); i++)
	{
		if (GroupVector->at(i).ID != this->ID)
		{
			flockalignmenttotal += GroupVector->at(i).Direction;
		}
	}

	XMVECTOR flockalignmentaverage = flockalignmenttotal / GroupVector->size();

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

void Enemy::Separation(float weight)
{
	XMMATRIX rotationmatrix;
	XMVECTOR closestflockmatedifference = {-1000.0f, -1000.0f, 0, 0};

	for (int i = 0; i < GroupVector->size(); i++)
	{
		if (GroupVector->at(i).ID != this->ID)
		{
			XMVECTOR tempvector = {XMVectorGetX(GroupVector->at(i).Location), XMVectorGetY(GroupVector->at(i).Location), 0, 0};
			XMVECTOR tempdifference = Location - tempvector;

			if (XMVectorGetX(XMVector2Length(tempdifference)) < XMVectorGetX(XMVector2Length(closestflockmatedifference)))
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

void Enemy::Chase(float playerx, float playery, float weight)
{
	XMMATRIX rotationmatrix;
	XMVECTOR playerlocation = {playerx, playery, 0, 0};

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

void Enemy::Update(float playerx, float playery)
{
	XMVECTOR playerlocation = {playerx, playery, 0, 0};

	float displacement = XMVectorGetX(XMVector2Length(playerlocation - Location));

	if (displacement <= 130.0f)
	{
		Separation(0.000f);
		Cohesion(0.000f);
		Alignment(0.0f);
		Chase(playerx, playery, 0.03f);
	}
	else
	{
		Separation(0.030f);
		Cohesion(0.02f);
		Alignment(0.008f);
		Chase(playerx, playery, 0.023f);
	}


	Location += (Direction * 4.0f);

	PointingOneLocation = Location + (Direction * 70.0f);
	PointingTwoLocation = Location + (Direction * 37.0f);
}

void Enemy::Draw()
{
	renderTexture(PlayerTex, Renderer, (XMVectorGetX(Location) - 16.0f), (XMVectorGetY(Location) - 16.0f));
	//renderTexture(PointingTex, Renderer, (XMVectorGetX(PointingOneLocation) - 8.0f), (XMVectorGetY(PointingOneLocation) - 8.0f));
	renderTexture(PointingTex, Renderer, (XMVectorGetX(PointingTwoLocation) - 8.0f), (XMVectorGetY(PointingTwoLocation) - 8.0f));
}

void Enemy::SetSprites()
{
}

void Enemy::renderTexture(SDL_Texture *texture, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, texture, NULL, &dst);
}

Enemy::~Enemy()
{
}