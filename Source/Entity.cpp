#include "Entity.h"

void Entity::BorderRestrict()
{
	if (XMVectorGetX(Location) < 0.0f)
	{
		//New Direction = Returned value of SetX(OldDirection, reversed X of Old Direction);
		Direction = XMVectorSetX(Direction, -(XMVectorGetX(Direction)));

		Location = XMVectorSetX(Location, 1.0f);
	}

	if (XMVectorGetX(Location) > float(ScreenWidth) - 100)
	{
		//New Direction = Returned value of SetX(OldDirection, reversed X of Old Direction);
		Direction = XMVectorSetX(Direction, -(XMVectorGetX(Direction)));

		Location = XMVectorSetX(Location, ScreenWidth - 101.0f);
	}

	if (XMVectorGetY(Location) < 40.0f)
	{
		Direction = XMVectorSetY(Direction, -(XMVectorGetY(Direction)));

		Location = XMVectorSetY(Location, 41.0f);
	}

	if (XMVectorGetY(Location) > float(ScreenHeight))
	{
		Direction = XMVectorSetY(Direction, -(XMVectorGetY(Direction)));

		Location = XMVectorSetY(Location, ScreenHeight - 1);
	}
}

void Entity::GiveMessage(Message NewMessage)
{
	MyMessageBox = NewMessage;
}