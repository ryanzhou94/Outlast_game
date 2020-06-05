#include "MovingController.h"
#include "GameEngine.h"
#include "MovingObject.h"

MovingController::MovingController(MovingObject* pMovingObject, int totalDistance)
	: pMovingObject(pMovingObject)
	, totalDistance(totalDistance)
{

}

MovingController::~MovingController()
{

}

void MovingController::drawMovingImages()
{
	if (pMovingObject->isVisible())
	{
		switch (toward)
		{
		case 0:
			pMovingObject->mainImage.renderImageWithMask(pMovingObject->getEngine()->getForegroundSurface(), 0, 0, pMovingObject->getCurrentScreenX(), pMovingObject->getCurrentScreenY(), pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight(), -1);
			break;
		case 1:
			walkingUp[walkingUpImageIndex].renderImageWithMask(pMovingObject->getEngine()->getForegroundSurface(), 0, 0, pMovingObject->getCurrentScreenX(), pMovingObject->getCurrentScreenY(), pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight(), -1);
			break;
		case 2:
			walkingDown[walkingDownImageIndex].renderImageWithMask(pMovingObject->getEngine()->getForegroundSurface(), 0, 0, pMovingObject->getCurrentScreenX(), pMovingObject->getCurrentScreenY(), pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight(), -1);
			break;
		case 3:
			walkingLeft[walkingLeftImageIndex].renderImageWithMask(pMovingObject->getEngine()->getForegroundSurface(), 0, 0, pMovingObject->getCurrentScreenX(), pMovingObject->getCurrentScreenY(), pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight(), -1);
			break;
		case 4:
			walkingRight[walkingRightImageIndex].renderImageWithMask(pMovingObject->getEngine()->getForegroundSurface(), 0, 0, pMovingObject->getCurrentScreenX(), pMovingObject->getCurrentScreenY(), pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight(), -1);
			break;
		default:
			break;
		}
	}
	if (isUnderFire)
	{
		explode[underFireImageIndex].renderImageWithMask(pMovingObject->getEngine()->getForegroundSurface(), 0, 0, pMovingObject->getCurrentScreenX(), pMovingObject->getCurrentScreenY(), pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight(), -1);
	}
}

void MovingController::loadMovingImages()
{
	for (int i = 0; i < 3; i++)
	{
		walkingDown[i] = pMovingObject->getEngine()->loadImage("images/" + pMovingObject->typeName + "_walking_down_" + std::to_string(i) + ".png", true);
		walkingLeft[i] = pMovingObject->getEngine()->loadImage("images/" + pMovingObject->typeName + "_walking_left_" + std::to_string(i) + ".png", true);
		walkingRight[i] = pMovingObject->getEngine()->loadImage("images/" + pMovingObject->typeName + "_walking_right_" + std::to_string(i) + ".png", true);
		walkingUp[i] = pMovingObject->getEngine()->loadImage("images/" + pMovingObject->typeName + "_walking_up_" + std::to_string(i) + ".png", true);

		walkingDown[i] = walkingDown[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
		walkingLeft[i] = walkingLeft[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
		walkingRight[i] = walkingRight[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
		walkingUp[i] = walkingUp[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
	}

	for (int i = 0; i < 5; i++)
	{
		explode[i] = pMovingObject->getEngine()->loadImage("images/explode_" + std::to_string(i) + ".png", false);
		explode[i] = explode[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
	}

}

void MovingController::attack(int iCurrentTime)
{
	if (attackStatus == 0)
	{
		switch (toward)
		{
		case 1:	// towards up
			movementPosition.setup(pMovingObject->getXCentre(), pMovingObject->getYCentre(), pMovingObject->getXCentre(), pMovingObject->getYCentre() - attackDistance, iCurrentTime, iCurrentTime + attackForwardInterval);
			break;
		case 2:
			movementPosition.setup(pMovingObject->getXCentre(), pMovingObject->getYCentre(), pMovingObject->getXCentre(), pMovingObject->getYCentre() + attackDistance, iCurrentTime, iCurrentTime + attackForwardInterval);
			break;
		case 3:
			movementPosition.setup(pMovingObject->getXCentre(), pMovingObject->getYCentre(), pMovingObject->getXCentre() - attackDistance, pMovingObject->getYCentre(), iCurrentTime, iCurrentTime + attackForwardInterval);
			break;
		case 4:
			movementPosition.setup(pMovingObject->getXCentre(), pMovingObject->getYCentre(), pMovingObject->getXCentre() + attackDistance, pMovingObject->getYCentre(), iCurrentTime, iCurrentTime + attackForwardInterval);
			break;
		default:
			break;
		}
		attackStatus = 1;
		attackTimer = iCurrentTime;
		isAttacking = true;
	}
	else if (attackStatus == 1)
	{
		if (movementPosition.hasMovementFinished(iCurrentTime))
		{
			switch (toward)
			{
			case 1:	// towards up
				movementPosition.setup(pMovingObject->getXCentre(), pMovingObject->getYCentre(), pMovingObject->getXCentre(), pMovingObject->getYCentre() + backwardDistance, iCurrentTime, iCurrentTime + attackBackInterval);
				break;
			case 2:
				movementPosition.setup(pMovingObject->getXCentre(), pMovingObject->getYCentre(), pMovingObject->getXCentre(), pMovingObject->getYCentre() - backwardDistance, iCurrentTime, iCurrentTime + attackBackInterval);
				break;
			case 3:
				movementPosition.setup(pMovingObject->getXCentre(), pMovingObject->getYCentre(), pMovingObject->getXCentre() + backwardDistance, pMovingObject->getYCentre(), iCurrentTime, iCurrentTime + attackBackInterval);
				break;
			case 4:
				movementPosition.setup(pMovingObject->getXCentre(), pMovingObject->getYCentre(), pMovingObject->getXCentre() - backwardDistance, pMovingObject->getYCentre(), iCurrentTime, iCurrentTime + attackBackInterval);
				break;
			default:
				break;
			}
			attackStatus = 2;
		}
		else
		{
			movementPosition.calculate(iCurrentTime);
			int newX = movementPosition.getX();
			int newY = movementPosition.getY();
			int deltX = newX - pMovingObject->getXCentre();
			int deltY = newY - pMovingObject->getYCentre();
			if (deltX != 0)
			{
				if (pMovingObject->pGameTileManager->validateAttackTile(pMovingObject, toward, deltX))
				{
					pMovingObject->moveCurrentScreenX(deltX);
					setUnderAttack();
					pMovingObject->pGameTileManager->tryBreakBucket(pMovingObject, pMovingObject->getEngine(), pMovingObject->getEngine()->getBackgroundSurface());
				}
				else
				{
					stopAttack();
				}
			}
			else
			{
				if (pMovingObject->pGameTileManager->validateAttackTile(pMovingObject, toward, deltY))
				{
					pMovingObject->moveCurrentScreenY(deltY);
					setUnderAttack();
					pMovingObject->pGameTileManager->tryBreakBucket(pMovingObject, pMovingObject->getEngine(), pMovingObject->getEngine()->getBackgroundSurface());
				}
				else
				{
					stopAttack();
				}
			}
		}
	}
	else	// attackStatus == 2
	{
		if (movementPosition.hasMovementFinished(iCurrentTime))
		{
			stopAttack();
		}
		else
		{
			movementPosition.calculate(iCurrentTime);
			int newX = movementPosition.getX();
			int newY = movementPosition.getY();
			int deltX = newX - pMovingObject->getXCentre();
			int deltY = newY - pMovingObject->getYCentre();
			if (deltX != 0)
			{
				if (pMovingObject->pGameTileManager->validateAttackTile(pMovingObject, toward, deltX))
				{
					pMovingObject->moveCurrentScreenX(deltX);
					setUnderAttack();
					pMovingObject->pGameTileManager->tryBreakBucket(pMovingObject, pMovingObject->getEngine(), pMovingObject->getEngine()->getBackgroundSurface());
				}
				else
				{
					stopAttack();
				}
			}
			else
			{
				if (pMovingObject->pGameTileManager->validateAttackTile(pMovingObject, toward, deltY))
				{
					pMovingObject->moveCurrentScreenY(deltY);
					setUnderAttack();
					pMovingObject->pGameTileManager->tryBreakBucket(pMovingObject, pMovingObject->getEngine(), pMovingObject->getEngine()->getBackgroundSurface());
				}
				else
				{
					stopAttack();
				}
			}
		}
	}
}

void MovingController::stopAttack()
{
	isAttacking = false;
	attackStatus = 0;
}

bool MovingController::isPositionValid(int distance)
{
	bool isValid = true;
	DisplayableObject* pObject;
	// 1. toward
	// 2. distance: enemy=walking distance;		player=walking/running distance
	switch (toward)
	{
	case 1:
		
		for (int iObject = 0; (pObject = pMovingObject->getEngine()->getDisplayableObject(iObject)) != NULL; iObject++)
		{
			
			if (pObject == (DisplayableObject*)this->pMovingObject)	// This is us, skip it
				continue;
			if (pObject == nullptr) // Object does not exist, skip it
				continue;
			if (pMovingObject->getDrawingRegionLeft() <= pObject->getDrawingRegionRight() && 
				pMovingObject->getDrawingRegionRight() >= pObject->getDrawingRegionLeft())
			{
				if (pMovingObject->getDrawingRegionTop() - distance <= pObject->getDrawingRegionBottom() &&
					pMovingObject->getDrawingRegionTop() - distance >= pObject->getDrawingRegionTop())
				{
					isValid = false;
					break;
				}
			}
		}
		break;
	case 2:
		for (int iObject = 0; (pObject = pMovingObject->getEngine()->getDisplayableObject(iObject)) != NULL; iObject++)
		{

			if (pObject == (DisplayableObject*)this->pMovingObject)	// This is us, skip it
				continue;
			if (pObject == nullptr) // Object does not exist, skip it
				continue;

			if (pMovingObject->getDrawingRegionLeft() <= pObject->getDrawingRegionRight() &&
				pMovingObject->getDrawingRegionRight() >= pObject->getDrawingRegionLeft())
			{
				if (pMovingObject->getDrawingRegionBottom() + distance <= pObject->getDrawingRegionBottom() &&
					pMovingObject->getDrawingRegionBottom() + distance >= pObject->getDrawingRegionTop())
				{
					isValid = false;
					break;
				}
			}
		}
		break;
	case 3:
		for (int iObject = 0; (pObject = pMovingObject->getEngine()->getDisplayableObject(iObject)) != NULL; iObject++)
		{

			if (pObject == (DisplayableObject*)this->pMovingObject)	// This is us, skip it
				continue;
			if (pObject == nullptr) // Object does not exist, skip it
				continue;

			if (pMovingObject->getDrawingRegionTop() <= pObject->getDrawingRegionBottom() &&
				pMovingObject->getDrawingRegionBottom() >= pObject->getDrawingRegionTop())
			{
				if (pMovingObject->getDrawingRegionLeft() - distance >= pObject->getDrawingRegionLeft() &&
					pMovingObject->getDrawingRegionLeft() - distance <= pObject->getDrawingRegionRight())
				{
					isValid = false;
					break;
				}
			}
		}
		break;
	case 4:
		for (int iObject = 0; (pObject = pMovingObject->getEngine()->getDisplayableObject(iObject)) != NULL; iObject++)
		{

			if (pObject == (DisplayableObject*)this->pMovingObject)	// This is us, skip it
				continue;
			if (pObject == nullptr) // Object does not exist, skip it
				continue;

			if (pMovingObject->getDrawingRegionTop() <= pObject->getDrawingRegionBottom() &&
				pMovingObject->getDrawingRegionBottom() >= pObject->getDrawingRegionTop())
			{
				if (pMovingObject->getDrawingRegionRight() + distance >= pObject->getDrawingRegionLeft() &&
					pMovingObject->getDrawingRegionRight() + distance <= pObject->getDrawingRegionRight())
				{
					isValid = false;
					break;
				}
			}
		}
		break;
	default:
		break;
	}
	return isValid;
}

MovingObject* MovingController::getObjectCollided()
{
	MovingObject* pObject = nullptr;
	switch (toward)
	{
	case 1:
		for (int iObject = 0; (pObject = (MovingObject*)pMovingObject->getEngine()->getDisplayableObject(iObject)) != nullptr; iObject++)
		{
			if (pObject == this->pMovingObject)	// This is us, skip it
				continue;
			if (pObject == nullptr) // Object does not exist, skip it
				continue;

			if (pMovingObject->getDrawingRegionLeft() <= pObject->getDrawingRegionRight() &&
				pMovingObject->getDrawingRegionRight() >= pObject->getDrawingRegionLeft())
			{
				if (pMovingObject->getDrawingRegionTop() <= pObject->getDrawingRegionBottom() &&
					pMovingObject->getDrawingRegionTop() >= pObject->getDrawingRegionTop())
				{
					break;
				}
			}
		}
		break;
	case 2:

		for (int iObject = 0; (pObject = (MovingObject*)pMovingObject->getEngine()->getDisplayableObject(iObject)) != NULL; iObject++)
		{

			if (pObject == this->pMovingObject)	// This is us, skip it
				continue;
			if (pObject == nullptr) // Object does not exist, skip it
				continue;

			if (pMovingObject->getDrawingRegionLeft() <= pObject->getDrawingRegionRight() &&
				pMovingObject->getDrawingRegionRight() >= pObject->getDrawingRegionLeft())
			{
				if (pMovingObject->getDrawingRegionBottom() <= pObject->getDrawingRegionBottom() &&
					pMovingObject->getDrawingRegionBottom() >= pObject->getDrawingRegionTop())
				{
					break;
				}
			}
		}
		break;
	case 3:
		for (int iObject = 0; (pObject = (MovingObject*)pMovingObject->getEngine()->getDisplayableObject(iObject)) != NULL; iObject++)
		{

			if (pObject == this->pMovingObject)	// This is us, skip it
				continue;
			if (pObject == nullptr) // Object does not exist, skip it
				continue;
			if (pMovingObject->getDrawingRegionTop() <= pObject->getDrawingRegionBottom() &&
				pMovingObject->getDrawingRegionBottom() >= pObject->getDrawingRegionTop())
			{
				if (pMovingObject->getDrawingRegionLeft() >= pObject->getDrawingRegionLeft() &&
					pMovingObject->getDrawingRegionLeft() <= pObject->getDrawingRegionRight())
				{
					break;
				}
			}
		}
		break;
	case 4:
		for (int iObject = 0; (pObject = (MovingObject*)pMovingObject->getEngine()->getDisplayableObject(iObject)) != NULL; iObject++)
		{

			if (pObject == this->pMovingObject)	// This is us, skip it
				continue;
			if (pObject == nullptr) // Object does not exist, skip it
				continue;
			if (pMovingObject->getDrawingRegionTop() <= pObject->getDrawingRegionBottom() &&
				pMovingObject->getDrawingRegionBottom() >= pObject->getDrawingRegionTop())
			{
				if (pMovingObject->getDrawingRegionRight() >= pObject->getDrawingRegionLeft() &&
					pMovingObject->getDrawingRegionRight() <= pObject->getDrawingRegionRight())
				{
					break;
				}
			}
		}
		break;
	default:
		break;
	}
	return pObject;
}

void MovingController::setUnderAttack()
{
	MovingObject* pObject = getObjectCollided();
	if (pObject != nullptr)
	{
		pObject->pMovingController->isUnderAttack = true;
	}
}

void MovingController::underAttack(int iCurrentTime)
{
	if (underAttackStatus == 0)
	{
		pMovingObject->pGameEngine->pAudioManager->PlaySFX("underattack.wav");
		isUnderAttack = true;
		underAttackStatus = 1;
		underAttackTimer = iCurrentTime;
		pMovingObject->setVisible(false);

		if (pMovingObject->HP - attackDamage >= 0)
		{
			pMovingObject->HP -= attackDamage;
		}
		else
		{
			pMovingObject->HP = 0;
		}
		
		std::cout << "HP = " << pMovingObject->HP << std::endl;
	}
	else if (underAttackStatus == 1)
	{
		if (iCurrentTime - underAttackTimer >= underAttackMissingInterval)
		{
			underAttackStatus = 2;
			underAttackTimer = iCurrentTime;
			pMovingObject->setVisible(true);
		}
	}
	else if (underAttackStatus == 2)
	{
		if (iCurrentTime - underAttackTimer >= underAttackShowingInterval)
		{
			underAttackStatus = 3;
			underAttackTimer = iCurrentTime;
			pMovingObject->setVisible(false);
		}
	}
	else
	{
		if (iCurrentTime - underAttackTimer >= underAttackMissingInterval)
		{
			isUnderAttack = false;
			underAttackStatus = 0;
			underAttackTimer = iCurrentTime;
			pMovingObject->setVisible(true);
		}
	}
}

void MovingController::underFire(int iCurrentTime)
{
	isUnderFire = true;
	if (iCurrentTime - underFireTimer >= underFireImageInterval)
	{
		underFireImageIndex++;
		underFireTimer = iCurrentTime;
	}

	if (underFireImageIndex >= 5)
	{
		isUnderFire = false;
		underFireImageIndex = 0;
		isUnderFirePlaying = false;
	}

	if (isUnderFire && !isUnderFirePlaying)
	{
		pMovingObject->pGameEngine->pAudioManager->PlaySFX("explode.wav");
		isUnderFirePlaying = true;
	}
}
