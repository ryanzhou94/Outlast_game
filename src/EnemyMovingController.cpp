#include "EnemyMovingController.h"
#include "GameEngine.h"

EnemyMovingController::EnemyMovingController(MovingObject* pMovingObject, MovingObject* pPlayerObject)
	: MovingController(pMovingObject)
	, pPlayerObject(pPlayerObject)
{
	toward = rand() % 4 + 1;
	coolingTime = 600;
	attackDamage = 35;
}

EnemyMovingController::~EnemyMovingController()
{
}

bool EnemyMovingController::isPlayerVisiable()
{
	return getDistance() <= 4 * pMovingObject->pGameTileManager->getTileWidth();
}

double EnemyMovingController::getDistance()
{
	double sum = (pMovingObject->getXCentre() - pPlayerObject->getXCentre()) * (pMovingObject->getXCentre() - pPlayerObject->getXCentre()) + (pMovingObject->getYCentre() - pPlayerObject->getYCentre()) * (pMovingObject->getYCentre() - pPlayerObject->getYCentre());
	return sqrt(sum);
}

// 1.up	2.down	3. left	4.right
int EnemyMovingController::getChasingPlayerDirection(int iCurrentTime)
{
	int xDelt = pPlayerObject->getXCentre() - pMovingObject->getXCentre();
	int yDelt = pPlayerObject->getYCentre() - pMovingObject->getYCentre();
	int xToward = 0;
	int yToward = 0;
	int toward = 0;
	// if xDelt > 0, the player is on the right of the enemy, else on the left
	// if yDelt > 0, the player is on the downside of the enemy, else on the top
	if (xDelt > 0)
	{
		xToward = 4;
	}
	else if (xDelt < 0)
	{
		xToward = 3;
	}

	if (yDelt > 0)
	{
		yToward = 2;
	}
	else if (yDelt < 0)
	{
		yToward = 1;
	}

	if (yToward == 1 && pMovingObject->pGameTileManager->validateTile(pMovingObject, yToward, -walkingDistance))
	{
		toward = yToward;
	}
	else if (yToward == 2 && pMovingObject->pGameTileManager->validateTile(pMovingObject, yToward, +walkingDistance))
	{
		toward = yToward;
	}
	else if (xToward == 3 && pMovingObject->pGameTileManager->validateTile(pMovingObject, xToward, -walkingDistance))
	{
		toward = xToward;
	}
	else if (xToward == 4 && pMovingObject->pGameTileManager->validateTile(pMovingObject, xToward, +walkingDistance))
	{
		toward = xToward;
	}
	return toward;
}

void EnemyMovingController::chasePlayer(int iCurrentTime)
{
	toward = getChasingPlayerDirection(iCurrentTime);

	switch (toward)
	{
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
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, toward, -walkingDistance) && isPositionValid(walkingDistance))
		{
			pMovingObject->moveCurrentScreenY(-walkingDistance);
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
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, toward, walkingDistance) && isPositionValid(walkingDistance))
		{
			pMovingObject->moveCurrentScreenY(+walkingDistance);
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
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, toward, -walkingDistance) && isPositionValid(walkingDistance))
		{
			pMovingObject->moveCurrentScreenX(-walkingDistance);
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
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, toward, walkingDistance) && isPositionValid(walkingDistance))
		{
			pMovingObject->moveCurrentScreenX(+walkingDistance);
		}
		break;
	default:
		break;
	}
}

// Enemy only attacks when he can reach the enemy
bool EnemyMovingController::isPlayerAttackable()
{
	bool isAttackable = false;

	switch (toward)
	{
	case 1:
		if (pMovingObject->getDrawingRegionLeft() <= pPlayerObject->getDrawingRegionRight() &&
			pMovingObject->getDrawingRegionRight() >= pPlayerObject->getDrawingRegionLeft())
		{
			if (pMovingObject->getDrawingRegionTop() - attackDistance / 2 < pPlayerObject->getDrawingRegionBottom() &&
				pMovingObject->getDrawingRegionTop() - attackDistance / 2 > pPlayerObject->getDrawingRegionTop())
			{
				isAttackable = true;
			}
		}
		break;
	case 2:
		if (pMovingObject->getDrawingRegionLeft() <= pPlayerObject->getDrawingRegionRight() &&
			pMovingObject->getDrawingRegionRight() >= pPlayerObject->getDrawingRegionLeft())
		{
			if (pMovingObject->getDrawingRegionBottom() + attackDistance / 2 < pPlayerObject->getDrawingRegionBottom() &&
				pMovingObject->getDrawingRegionBottom() + attackDistance / 2 > pPlayerObject->getDrawingRegionTop())
			{
				isAttackable = true;
			}
		}
		break;
	case 3:
		if (pMovingObject->getDrawingRegionTop() <= pPlayerObject->getDrawingRegionBottom() &&
			pMovingObject->getDrawingRegionBottom() >= pPlayerObject->getDrawingRegionTop())
		{
			if (pMovingObject->getDrawingRegionLeft() - attackDistance / 2 > pPlayerObject->getDrawingRegionLeft() &&
				pMovingObject->getDrawingRegionLeft() - attackDistance / 2 < pPlayerObject->getDrawingRegionRight())
			{
				isAttackable = true;
			}
		}
		break;
	case 4:
		if (pMovingObject->getDrawingRegionTop() <= pPlayerObject->getDrawingRegionBottom() &&
			pMovingObject->getDrawingRegionBottom() >= pPlayerObject->getDrawingRegionTop())
		{
			if (pMovingObject->getDrawingRegionRight() + attackDistance / 2 > pPlayerObject->getDrawingRegionLeft() &&
				pMovingObject->getDrawingRegionRight() + attackDistance / 2 < pPlayerObject->getDrawingRegionRight())
			{
				isAttackable = true;
			}
		}
		break;
	default:
		break;
	}
	return isAttackable;
}

bool EnemyMovingController::checkEnemyStop(int iCurrentTime)
{
	if (!isAttacking)
	{
		if (isChecking)
		{
			lastX = pMovingObject->getXCentre();
			lastY = pMovingObject->getYCentre();
			isChecking = false;
		}
		else
		{
			// isChecking == false
			if (iCurrentTime - stopTimer >= stopInterval)
			{
				if (lastX == pMovingObject->getXCentre() && lastY == pMovingObject->getYCentre())
				{
					isStop = true;
					isSearching = false;
				}
				else
				{
					isStop = false;
				}
				stopTimer = iCurrentTime;
				isChecking = true;
			}
		}
	}
	else
	{
		isStop = false;
	}
	//std::cout << "is stop:" << isStop << std::endl;
	return isStop;
	//std::cout << "is Stop: " << isStop << std::endl;
	//if (!isAttacking)
	//{
	//	if (iCurrentTime - stopTimer < stopInterval && isChecking)
	//	{
	//		lastX = pMovingObject->getXCentre();
	//		lastY = pMovingObject->getYCentre();
	//		updateTimer = iCurrentTime;
	//		isChecking = false;
	//	}

	//	if (iCurrentTime - updateTimer >= stopInterval)
	//	{
	//		if (lastX == pMovingObject->getXCentre() && lastY == pMovingObject->getYCentre()/* && lastX == pPlayerObject->getXCentre() && lastY == pPlayerObject->getYCentre()*/)
	//		{
	//			isStop = true;
	//		}
	//		else
	//		{
	//			isStop = false;
	//		}
	//		stopTimer = iCurrentTime;
	//		isChecking = true;
	//	}
	//	return isStop;
	//}
	//else
	//{
	//	isStop = false;
	//	return false;
	//}
}

void EnemyMovingController::setRealToward()
{
	if (pPlayerObject->getXCentre() - pMovingObject->getXCentre() <= 2 && pPlayerObject->getXCentre() - pMovingObject->getXCentre() >= -2)
	{
		if (pPlayerObject->getYCentre() > pMovingObject->getYCentre())
		{
			realToward = 2;
		}
		else
		{
			realToward = 1;
		}
	}
	else
	{
		if (pPlayerObject->getYCentre() - pMovingObject->getYCentre() <= 2 && pPlayerObject->getYCentre() - pMovingObject->getYCentre() >= -2)
		{
			if (pPlayerObject->getXCentre() > pMovingObject->getXCentre())
			{
				realToward = 4;
			}
			else
			{
				realToward = 3;
			}
		}
	}
	//std::cout << "real toward : " << realToward << std::endl;
}

bool EnemyMovingController::isUpLeftMovable()
{
	bool isMovable = false;
	int X = pMovingObject->pGameTileManager->getMapXForScreenX(pMovingObject->getXCentre());
	int Y = pMovingObject->pGameTileManager->getMapYForScreenY(pMovingObject->getYCentre()) - 1;
	for (int x = X ; x >= 0 && X - x <= 5 ; x--)
	{
		if (pMovingObject->pGameTileManager->isOneTileCrossable(pMovingObject, x, Y))
		{
			isMovable = true;
			break;
		}
	}
	return isMovable;
}

bool EnemyMovingController::isUpRightMovable()
{
	bool isMovable = false;
	int X = pMovingObject->pGameTileManager->getMapXForScreenX(pMovingObject->getXCentre());
	int Y = pMovingObject->pGameTileManager->getMapYForScreenY(pMovingObject->getYCentre()) - 1;
	for (int x = X; x < pMovingObject->pGameTileManager->getMapWidth() && x - X <= 5; x++)
	{
		if (pMovingObject->pGameTileManager->isOneTileCrossable(pMovingObject, x, Y))
		{
			isMovable = true;
			break;
		}
	}
	return isMovable;
}

bool EnemyMovingController::isDownLeftMovable()
{
	bool isMovable = false;
	int X = pMovingObject->pGameTileManager->getMapXForScreenX(pMovingObject->getXCentre());
	int Y = pMovingObject->pGameTileManager->getMapYForScreenY(pMovingObject->getYCentre()) + 1;
	for (int x = X; x >= 0 && X - x <= 5; x--)
	{
		if (pMovingObject->pGameTileManager->isOneTileCrossable(pMovingObject, x, Y))
		{
			isMovable = true;
			break;
		}
	}
	return isMovable;
}

bool EnemyMovingController::isDownRightMovable()
{
	bool isMovable = false;
	int X = pMovingObject->pGameTileManager->getMapXForScreenX(pMovingObject->getXCentre());
	int Y = pMovingObject->pGameTileManager->getMapYForScreenY(pMovingObject->getYCentre()) + 1;
	for (int x = X; x < pMovingObject->pGameTileManager->getMapWidth() && x - X <= 5; x++)
	{
		if (pMovingObject->pGameTileManager->isOneTileCrossable(pMovingObject, x, Y))
		{
			isMovable = true;
			break;
		}
	}
	return isMovable; return false;
}

bool EnemyMovingController::isLeftUpMovable()
{
	bool isMovable = false;
	int X = pMovingObject->pGameTileManager->getMapXForScreenX(pMovingObject->getXCentre()) - 1;
	int Y = pMovingObject->pGameTileManager->getMapYForScreenY(pMovingObject->getYCentre());
	for (int y = Y; y >= 0 && Y - y <= 5; y--)
	{
		if (pMovingObject->pGameTileManager->isOneTileCrossable(pMovingObject, X, y))
		{
			isMovable = true;
			break;
		}
	}
	return isMovable;
}

bool EnemyMovingController::isLeftDownMovable()
{
	bool isMovable = false;
	int X = pMovingObject->pGameTileManager->getMapXForScreenX(pMovingObject->getXCentre()) - 1;
	int Y = pMovingObject->pGameTileManager->getMapYForScreenY(pMovingObject->getYCentre());
	for (int y = Y; y < pMovingObject->pGameTileManager->getMapHeight() && y - Y <= 5; y++)
	{
		if (pMovingObject->pGameTileManager->isOneTileCrossable(pMovingObject, X, y))
		{
			isMovable = true;
			break;
		}
	}
	return isMovable;
}

bool EnemyMovingController::isRightUpMovable()
{
	bool isMovable = false;
	int X = pMovingObject->pGameTileManager->getMapXForScreenX(pMovingObject->getXCentre()) + 1;
	int Y = pMovingObject->pGameTileManager->getMapYForScreenY(pMovingObject->getYCentre());
	for (int y = Y; y >= 0 && Y - y <= 5; y--)
	{
		if (pMovingObject->pGameTileManager->isOneTileCrossable(pMovingObject, X, y))
		{
			isMovable = true;
			break;
		}
	}
	return isMovable;
}

bool EnemyMovingController::isRightDownMovable()
{
	bool isMovable = false;
	int X = pMovingObject->pGameTileManager->getMapXForScreenX(pMovingObject->getXCentre()) + 1;
	int Y = pMovingObject->pGameTileManager->getMapYForScreenY(pMovingObject->getYCentre());
	for (int y = Y; y < pMovingObject->pGameTileManager->getMapHeight() && y - Y <= 5; y++)
	{
		if (pMovingObject->pGameTileManager->isOneTileCrossable(pMovingObject, X, y))
		{
			isMovable = true;
			break;
		}
	}
	return isMovable;
}

void EnemyMovingController::handleMovement(int iCurrentTime)
{


	if (pMovingObject->HP > 0)
	{
		if (!isAttacking)
		{
			if (isPlayerVisiable())
			{
				checkEnemyStop(iCurrentTime);
				chasePlayer(iCurrentTime);
			}
			else
			{
				anticlockwiseMovement(iCurrentTime);
			}
		}

		if (isUnderAttack && (iCurrentTime - underAttackTimer >= underAttackCoolingTime))
		{
			underAttack(iCurrentTime);
		}

		if (isPlayerAttackable() && (iCurrentTime - attackTimer >= coolingTime) || isAttacking)
		{
			attack(iCurrentTime);
		}

		if (isUnderFire)
		{
			underFire(iCurrentTime);
		}
	}
	else
	{
		pMovingObject->pGameEngine->removeDisplayableObject(pMovingObject);
	}
	

}

void EnemyMovingController::anticlockwiseMovement(int iCurrentTime)
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


