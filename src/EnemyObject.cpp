#include "EnemyObject.h"
#include "GameEngine.h"

EnemyObject::EnemyObject(GameEngine* pGameEngine, GameTileManager* pGameTileManager, int xStart, int yStart, MovingObject* pPlayerObject)
	: MovingObject(pGameEngine, pGameTileManager, xStart, yStart)
	, pPlayerObject(pPlayerObject)
{
	setShouldDeleteOnRemoval(true);
	virtInitializeUncrossable();
	virtInitializeAttackable();
}

EnemyObject::~EnemyObject()
{
}

void EnemyObject::virtDraw()
{
	pMovingController->drawMovingImages();
}

void EnemyObject::virtDoUpdate(int iCurrentTime)
{
	if (!pGameEngine->isPaused())
	{
		pMovingController->handleMovement(iCurrentTime);

		redrawDisplay();
	}
}

void EnemyObject::virtInitializeUncrossable()
{
// 1. wall
// 2. floor
// 3. unlocked door
// 4. locked door
// 5. trap
// 6. fountain
// 7. bucket
// 8. key
// 9. hp
// 0. mp
// 10. noOpenedDoor
	uncrossable.push_back(1);
	uncrossable.push_back(4);
	uncrossable.push_back(5);
	uncrossable.push_back(6);
	uncrossable.push_back(7);
	uncrossable.push_back(10);
}

void EnemyObject::virtInitializeAttackable()
{
// 1. wall
// 2. floor
// 3. unlocked door
// 4. locked door
// 5. trap
// 6. fountain
// 7. bucket
// 8. key
// 9. hp
// 0. mp
// 10. noOpenedDoor
	unattackble.push_back(1);
	unattackble.push_back(4);
	unattackble.push_back(5);
	unattackble.push_back(6);
	unattackble.push_back(7);
	uncrossable.push_back(10);
}