#include "EnemyTypeOneMovingController.h"
#include "GameEngine.h"

EnemyTypeOneMovingController::EnemyTypeOneMovingController(MovingObject* pMovingObject, MovingObject* pPlayerObject)
	: EnemyMovingController(pMovingObject, pPlayerObject)
{
	// anticlockwise
	// Randomly set a start direction
	toward = rand() % 4 + 1;
	coolingTime = 600;
}

EnemyTypeOneMovingController::~EnemyTypeOneMovingController()
{
}


void EnemyTypeOneMovingController::handleMovement(int iCurrentTime)
{
	if (!isAttacking)
	{
		if (isPlayerVisiable())
		{
			chasePlayer(iCurrentTime);
		}
		else
		{
			anticlockwiseMovement(iCurrentTime);
		}
	}

	if (isPlayerAttackable() && (iCurrentTime - attackTimer >= coolingTime) || isAttacking)
	{
		attack(iCurrentTime);
	}

	if (isUnderAttack && (iCurrentTime - underAttackTimer >= underAttackCoolingTime))
	{
		underAttack(iCurrentTime);
	}

	if (isUnderFire)
	{
		underFire(iCurrentTime);
	}
	
}

void EnemyTypeOneMovingController::anticlockwiseMovement(int iCurrentTime)
{
	// anticlockwise
	switch (toward)
	{
	case 0:
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, 1, -walkingDistance))
		{
			toward = 1;
		}
		else if (pMovingObject->pGameTileManager->validateTile(pMovingObject, 2, +walkingDistance))
		{
			toward = 2;
		}
		else if (pMovingObject->pGameTileManager->validateTile(pMovingObject, 3, -walkingDistance))
		{
			toward = 3;
		}
		else if (pMovingObject->pGameTileManager->validateTile(pMovingObject, 4, +walkingDistance))
		{
			toward = 4;
		}
		break;
	case 1:
		// Moving up
		if (iCurrentTime - walkingUpTimer >= walkingInterval)
		{
			if (walkingUpImageIndex == 2)
			{
				walkingUpImageIndex = 0;
			}
			walkingUpTimer = iCurrentTime;
			walkingUpImageIndex += 1;
		}
		// validate borders
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, toward, -walkingDistance))
		{
			pMovingObject->moveCurrentScreenY(-walkingDistance);
		}
		else
		{
			toward = 3;
		}
		break;
	case 2:
		// Moving down
		if (iCurrentTime - walkingDownTimer >= walkingInterval)
		{
			if (walkingDownImageIndex == 2)
			{
				walkingDownImageIndex = 0;
			}
			walkingDownTimer = iCurrentTime;
			walkingDownImageIndex += 1;
		}
		// validate borders
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, toward, +walkingDistance))
		{
			pMovingObject->moveCurrentScreenY(+walkingDistance);
		}
		else
		{
			toward = 4;
		}
		break;
	case 3:
		// Moving left
		if (iCurrentTime - walkingLeftTimer >= walkingInterval)
		{
			if (walkingLeftImageIndex == 2)
			{
				walkingLeftImageIndex = 0;
			}
			walkingLeftTimer = iCurrentTime;
			walkingLeftImageIndex += 1;
		}
		// validate borders
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, toward, -walkingDistance))
		{
			pMovingObject->moveCurrentScreenX(-walkingDistance);
		}
		else
		{
			toward = 2;
		}
		break;
	case 4:
		// Moving right
		if (iCurrentTime - walkingRightTimer >= walkingInterval)
		{
			if (walkingRightImageIndex == 2)
			{
				walkingRightImageIndex = 0;
			}
			walkingRightTimer = iCurrentTime;
			walkingRightImageIndex += 1;
		}
		// validate borders
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, toward, +walkingDistance))
		{
			pMovingObject->moveCurrentScreenX(+walkingDistance);
		}
		else
		{
			toward = 1;
		}
		break;
	default:
		break;
	}
}

