#include "PropsObject.h"
#include "GameEngine.h"

PropsObject::PropsObject(GameEngine* pGameEngine, int xStart, int yStart, PlayerObject* pPlayerObject)
	: GameObject(pGameEngine, xStart, yStart)
	, pPlayerObject(pPlayerObject)
{
}

PropsObject::~PropsObject()
{
}

bool PropsObject::isPlayerCollided()
{
	bool isCollided = false;
	if (pPlayerObject->getDrawingRegionTop() >= getDrawingRegionTop() && pPlayerObject->getDrawingRegionTop() <= getDrawingRegionBottom()
	|| pPlayerObject->getDrawingRegionBottom() >= getDrawingRegionTop() && pPlayerObject->getDrawingRegionBottom() <= getDrawingRegionBottom())
	{
		if (pPlayerObject->getDrawingRegionRight() >= getDrawingRegionLeft() && pPlayerObject->getDrawingRegionRight() <= getDrawingRegionRight()
		||  pPlayerObject->getDrawingRegionLeft() >= getDrawingRegionLeft() && pPlayerObject->getDrawingRegionLeft() <= getDrawingRegionRight())
		{
			isCollided = true;
		}
	}
	return isCollided;
}
