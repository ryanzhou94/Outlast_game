#include "FireMovingController.h"
#include "GameEngine.h"

FireMovingController::FireMovingController(MovingObject* pMovingObject, int distance)
	: MovingController(pMovingObject)
{
	totalDistance = distance;
	loadImage();
	loadFireImages();
}

FireMovingController::~FireMovingController()
{
}


void FireMovingController::disapper()
{
	pMovingObject->pGameEngine->removeDisplayableObject(pMovingObject);
}

void FireMovingController::loadImage()
{
	if (!pMovingObject->mainImageURL.empty())
	{
		pMovingObject->mainImage = pMovingObject->getEngine()->loadImage("images/fire_main.png", true);
		pMovingObject->setDrawWidth(pMovingObject->actual_width);
		pMovingObject->setDrawHeight(pMovingObject->actual_height);
		pMovingObject->mainImage = pMovingObject->mainImage.resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
	}
}

void FireMovingController::handleMovement(int iCurrentTime)
{
	if (totalDistance < flyingDistance)
	{
		fly(iCurrentTime);
	}
	else
	{
		disapper();
	}
}

void FireMovingController::fly(int iCurrentTime)
{
	switch (toward)
	{
	case 1:
		// Moving up
		if (iCurrentTime - walkingUpTimer >= flyInterval)
		{
			if (walkingUpImageIndex == 6)
			{
				walkingUpImageIndex = 0;
			}
			walkingUpTimer = iCurrentTime;
			walkingUpImageIndex += 1;
		}
		// validate borders
		if (pMovingObject->pGameTileManager->validateAttackTile(pMovingObject, toward, -flyingSpeed))
		{
			if (pMovingObject->pGameTileManager->validateWall(pMovingObject))
			{
				disapper();
			}
			else
			{
				pMovingObject->moveCurrentScreenY(-flyingSpeed);
				totalDistance += flyingSpeed;
				pMovingObject->pGameTileManager->tryBreakBucket(pMovingObject, pMovingObject->getEngine(), pMovingObject->getEngine()->getBackgroundSurface());
			}
		}
		else
		{
			disapper();
		}
		break;
	case 2:
		// Moving down
		if (iCurrentTime - walkingDownTimer >= flyInterval)
		{
			if (walkingDownImageIndex == 6)
			{
				walkingDownImageIndex = 0;
			}
			walkingDownTimer = iCurrentTime;
			walkingDownImageIndex += 1;
		}
		// validate borders
		if (pMovingObject->pGameTileManager->validateAttackTile(pMovingObject, toward, +flyingSpeed))
		{
			if (pMovingObject->pGameTileManager->validateWall(pMovingObject))
			{
				disapper();
			}
			else
			{
				pMovingObject->moveCurrentScreenY(+flyingSpeed);
				totalDistance += flyingSpeed;
				pMovingObject->pGameTileManager->tryBreakBucket(pMovingObject, pMovingObject->getEngine(), pMovingObject->getEngine()->getBackgroundSurface());
			}
		}
		else
		{
			disapper();
		}
		break;
	case 3:
		// Moving left
		if (iCurrentTime - walkingLeftTimer >= flyInterval)
		{
			if (walkingLeftImageIndex == 6)
			{
				walkingLeftImageIndex = 0;
			}
			walkingLeftTimer = iCurrentTime;
			walkingLeftImageIndex += 1;
		}
		// validate borders
		if (pMovingObject->pGameTileManager->validateAttackTile(pMovingObject, toward, -flyingSpeed))
		{
			if (pMovingObject->pGameTileManager->validateWall(pMovingObject))
			{
				disapper();
			}
			else
			{
				pMovingObject->moveCurrentScreenX(-flyingSpeed);
				totalDistance += flyingSpeed;
				pMovingObject->pGameTileManager->tryBreakBucket(pMovingObject, pMovingObject->getEngine(), pMovingObject->getEngine()->getBackgroundSurface());
			}
		}
		else
		{
			disapper();
		}
		break;
	case 4:
		// Moving right
		if (iCurrentTime - walkingRightTimer >= flyInterval)
		{
			if (walkingRightImageIndex == 6)
			{
				walkingRightImageIndex = 0;
			}
			walkingRightTimer = iCurrentTime;
			walkingRightImageIndex += 1;
		}
		// validate borders
		if (pMovingObject->pGameTileManager->validateAttackTile(pMovingObject, toward, +flyingSpeed))
		{
			if (pMovingObject->pGameTileManager->validateWall(pMovingObject))
			{
				disapper();
			}
			else
			{
				pMovingObject->moveCurrentScreenX(+flyingSpeed);
				totalDistance += flyingSpeed;
				pMovingObject->pGameTileManager->tryBreakBucket(pMovingObject, pMovingObject->getEngine(), pMovingObject->getEngine()->getBackgroundSurface());
			}
		}
		else
		{
			disapper();
		}
		break;
	default:
		break;
	}
	setUnderFire();
}

void FireMovingController::loadFireImages()
{
	for (int i = 0; i < 7; i++)
	{
		walkingDown[i] = pMovingObject->getEngine()->loadImage("images/fire_walking_down_" + std::to_string(i) + ".png", true);
		walkingLeft[i] = pMovingObject->getEngine()->loadImage("images/fire_walking_left_" + std::to_string(i) + ".png", true);
		walkingRight[i] = pMovingObject->getEngine()->loadImage("images/fire_walking_right_" + std::to_string(i) + ".png", true);
		walkingUp[i] = pMovingObject->getEngine()->loadImage("images/fire_walking_up_" + std::to_string(i) + ".png", true);

		walkingDown[i] = walkingDown[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
		walkingLeft[i] = walkingLeft[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
		walkingRight[i] = walkingRight[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
		walkingUp[i] = walkingUp[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
	}
}

void FireMovingController::setUnderFire()
{
	MovingObject* pObject = getObjectCollided();
	if (pObject != nullptr)
	{
		pObject->pMovingController->isUnderFire = true;
		pObject->HP -= fireDamage;
		disapper();
	}

}
