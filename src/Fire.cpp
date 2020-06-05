#include "Fire.h"
#include "GameEngine.h"

Fire::Fire(GameEngine* pGameEngine, GameTileManager* pGameTileManager, int xStart, int yStart, int toward, int totalDistance)
	: MovingObject(pGameEngine, pGameTileManager, xStart, yStart)
{
	actual_height = 30;
	actual_width = 30;
	typeName = "fire";
	pMovingController = new FireMovingController(this, totalDistance);
	pMovingController->toward = toward;
	virtInitializeUncrossable();
}

Fire::~Fire()
{
}

void Fire::virtDraw()
{
	pMovingController->drawMovingImages();
}

void Fire::virtDoUpdate(int iCurrentTime)
{
	if (!pGameEngine->isPaused())
	{
		pMovingController->handleMovement(iCurrentTime);

		redrawDisplay();
	}
}

void Fire::virtInitializeUncrossable()
{
	uncrossable.push_back(1);
	uncrossable.push_back(4);
	uncrossable.push_back(6);
	uncrossable.push_back(7);
}
