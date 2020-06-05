#include "MovingObject.h"
#include "GameEngine.h"

MovingObject::MovingObject(GameEngine* pGameEngine, GameTileManager* pGameTileManager, int xStart, int yStart)
	: GameObject(pGameEngine, xStart, yStart)
	, pGameTileManager(pGameTileManager)
{
}

MovingObject::~MovingObject()
{
	delete pMovingController;
}

void MovingObject::loadMovingImages()
{
	pMovingController->loadMovingImages();
}
