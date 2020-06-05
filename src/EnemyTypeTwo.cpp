#include "EnemyTypeTwo.h"
#include "GameEngine.h"

EnemyTypeTwo::EnemyTypeTwo(GameEngine* pGameEngine, GameTileManager* pGameTileManager, int xStart, int yStart, MovingObject* pPlayerObject)
	: EnemyObject(pGameEngine, pGameTileManager, xStart, yStart, pPlayerObject)
{
	this->pMovingController = new EnemyMovingController(this, pPlayerObject);
	this->typeName = "enemy_two";
	this->actual_height = 48;
	this->actual_width = 44;

	loadImage();
	loadMovingImages();
}

EnemyTypeTwo::~EnemyTypeTwo()
{
}
