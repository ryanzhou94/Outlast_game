#include "PlayerMovingController.h"
#include "GameEngine.h"


PlayerMovingController::PlayerMovingController(MovingObject* pMovingObject)
	: MovingController(pMovingObject)
{
	coolingTime = 700;
}

PlayerMovingController::~PlayerMovingController()
{
}

void PlayerMovingController::handleMovement(int iCurrentTime)
{
	// Default parameters
	int imageSwitchingInterval = walkingInterval;
	int movingDistance = walkingDistance;
	isRunning = false;
	if (pMovingObject->getEngine()->isKeyPressed(SDLK_UP))
	{
		isMoving = true;
		if (pMovingObject->getEngine()->isKeyPressed(SDLK_SPACE) && pMovingObject->MP > 2)
		{
			isRunning = true;
			movingDistance = runningDistance;
			imageSwitchingInterval = runningInterval;
			pMovingObject->MP -= 2;
		}
		if (iCurrentTime - walkingUpTimer >= imageSwitchingInterval)
		{
			if (walkingUpImageIndex == 2)
			{
				walkingUpImageIndex = 0;
			}
			walkingUpTimer = iCurrentTime;
			walkingUpImageIndex += 1;
		}
		toward = 1;

		// validate borders
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, toward, -movingDistance) && isPositionValid(movingDistance))
		{

			
			pMovingObject->moveCurrentScreenY(-movingDistance);
		}
	}
	else if (pMovingObject->getEngine()->isKeyPressed(SDLK_DOWN))
	{
		isMoving = true;
		if (pMovingObject->getEngine()->isKeyPressed(SDLK_SPACE) && pMovingObject->MP > 2)
		{
			isRunning = true;
			movingDistance = runningDistance;
			imageSwitchingInterval = runningInterval;
			pMovingObject->MP -= 2;
		}
		if (iCurrentTime - walkingDownTimer >= imageSwitchingInterval)
		{
			if (walkingDownImageIndex == 2)
			{
				walkingDownImageIndex = 0;
			}
			walkingDownTimer = iCurrentTime;
			walkingDownImageIndex += 1;
		}
		toward = 2;

		// validate borders
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, toward, +movingDistance) && isPositionValid(movingDistance))
		{
			pMovingObject->moveCurrentScreenY(+movingDistance);
		}
	}
	else if (pMovingObject->getEngine()->isKeyPressed(SDLK_LEFT))
	{
		isMoving = true;
		if (pMovingObject->getEngine()->isKeyPressed(SDLK_SPACE) && pMovingObject->MP > 2)
		{
			isRunning = true;
			movingDistance = runningDistance;
			imageSwitchingInterval = runningInterval;
			pMovingObject->MP -= 2;
		}
		if (iCurrentTime - walkingLeftTimer >= imageSwitchingInterval)
		{
			if (walkingLeftImageIndex == 2)
			{
				walkingLeftImageIndex = 0;
			}
			walkingLeftTimer = iCurrentTime;
			walkingLeftImageIndex += 1;
		}
		toward = 3;

		// validate borders
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, toward, -movingDistance) && isPositionValid(movingDistance))
		{
			pMovingObject->moveCurrentScreenX(-movingDistance);
		}
	}
	else if (pMovingObject->getEngine()->isKeyPressed(SDLK_RIGHT))
	{
		isMoving = true;
		if (pMovingObject->getEngine()->isKeyPressed(SDLK_SPACE) && pMovingObject->MP > 2)
		{
			isRunning = true;
			movingDistance = runningDistance;
			imageSwitchingInterval = runningInterval;
			pMovingObject->MP -= 2;
		}
		if (iCurrentTime - walkingRightTimer >= imageSwitchingInterval)
		{
			if (walkingRightImageIndex == 2)
			{
				walkingRightImageIndex = 0;
			}
			walkingRightTimer = iCurrentTime;
			walkingRightImageIndex += 1;
		}
		toward = 4;

		// validate borders
		if (pMovingObject->pGameTileManager->validateTile(pMovingObject, toward, +movingDistance) && isPositionValid(movingDistance))
		{
			pMovingObject->moveCurrentScreenX(+movingDistance);
		}
	}
	else
	{
		isMoving = false;
		walkingDownImageIndex = 0;
		walkingUpImageIndex = 0;
		walkingLeftImageIndex = 0;
		walkingRightImageIndex = 0;
	}



	if (pMovingObject->getEngine()->isKeyPressed(SDLK_a) && (iCurrentTime - attackTimer >= coolingTime) || isAttacking)
	{
		attack(iCurrentTime);
	}

	if (/*pMovingObject->getEngine()->isKeyPressed(SDLK_s) && (iCurrentTime - underAttackTimer >= underAttackCoolingTime) ||*/ isUnderAttack)
	{
		underAttack(iCurrentTime);
	}

	if (pMovingObject->getEngine()->isKeyPressed(SDLK_d) && (iCurrentTime - fireTimer >= fireCoolingTime) && pMovingObject->MP > 50)
	{
		pMovingObject->pGameEngine->pAudioManager->PlaySFX("fire.wav");
		fire(iCurrentTime);
	}

	if (iCurrentTime - trapTimer >= trapCoolingTime)
	{
		if (pMovingObject->pGameTileManager->validateTrap(pMovingObject))
		{
			trapTimer = iCurrentTime;
			isUnderAttack = true;
		}
	}

	if (pMovingObject->pGameTileManager->isPlayerAroundFountain(pMovingObject) && pMovingObject->MP + healMPValue < pMovingObject->maxMP)
	{
		pMovingObject->MP += healMPValue;
	}

	playWalk(iCurrentTime);
	playRun(iCurrentTime);
	playAttack(iCurrentTime);
	//stopPlay();
	
	selfHealHP(iCurrentTime);
	selfHealMP(iCurrentTime);

}

void PlayerMovingController::loadFireImages()
{
	for (int i = 0; i < 3; i++)
	{
		fireDown[i] = pMovingObject->getEngine()->loadImage("images/" + pMovingObject->typeName + "_walking_down_" + std::to_string(i) + ".png", true);
		fireLeft[i] = pMovingObject->getEngine()->loadImage("images/" + pMovingObject->typeName + "_walking_left_" + std::to_string(i) + ".png", true);
		fireRight[i] = pMovingObject->getEngine()->loadImage("images/" + pMovingObject->typeName + "_walking_right_" + std::to_string(i) + ".png", true);
		fireUp[i] = pMovingObject->getEngine()->loadImage("images/" + pMovingObject->typeName + "_walking_up_" + std::to_string(i) + ".png", true);

		fireDown[i] = fireDown[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
		fireLeft[i] = fireLeft[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
		fireRight[i] = fireRight[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
		fireUp[i] = fireUp[i].resizeTo(pMovingObject->getDrawWidth(), pMovingObject->getDrawHeight());
	}
}

void PlayerMovingController::selfHealHP(int iCurrentTime)
{
	if (iCurrentTime - healHPTimer >= healHPCoolingTime && pMovingObject->HP + healHPValue <= pMovingObject->maxHP)
	{
		pMovingObject->HP += healHPValue;
		healHPTimer = iCurrentTime;
	}
}

void PlayerMovingController::selfHealMP(int iCurrentTime)
{
	if (iCurrentTime - healMPTimer >= healMPCoolingTime && pMovingObject->MP + healMPValue <= pMovingObject->maxMP)
	{
		pMovingObject->MP += healMPValue;
		healMPTimer = iCurrentTime;
	}
}

void PlayerMovingController::playWalk(int iCurrentTime)
{
	if (!isWalkPlaying && isMoving && !isRunning)
	{
		pMovingObject->pGameEngine->pAudioManager->PlaySFX("walk.wav");
		walkPlayTimer = iCurrentTime;
		isWalkPlaying = true;
	}
	else if (iCurrentTime - walkPlayTimer >= walkPlayInterval)
	{
		isWalkPlaying = false;
	}
}

void PlayerMovingController::playRun(int iCurrentTime)
{
	if (!isRunningPlaying && isRunning)
	{
		pMovingObject->pGameEngine->pAudioManager->PlaySFX("run.wav");
		runPlayTimer = iCurrentTime;
		isRunningPlaying = true;
	}
	else if (iCurrentTime - runPlayTimer >= runPlayInterval)
	{
		isRunningPlaying = false;
	}
}

void PlayerMovingController::playAttack(int iCurrentTime)
{
	if (!isAttackPlaying && isAttacking)
	{
		pMovingObject->pGameEngine->pAudioManager->PlaySFX("attack.wav");
		attackPlayTimer = iCurrentTime;
		isAttackPlaying = true;
	}
	else if (iCurrentTime - attackPlayTimer >= attackPlayInterval)
	{
		isAttackPlaying = false;
	}
}

void PlayerMovingController::stopPlay()
{
	if (!isAttacking && !isMoving && !isRunning)
	{
		pMovingObject->pGameEngine->pAudioManager->PauseMusic();
	}
}

void PlayerMovingController::fire(int iCurrentTime)
{
	pMovingObject->MP -= 50;
	fireTimer = iCurrentTime;
	switch (toward)
	{
	case 1:
		pMovingObject->getEngine()->appendObjectToArray(new Fire(pMovingObject->pGameEngine, pMovingObject->pGameTileManager, pMovingObject->getCurrentScreenX() + 5, pMovingObject->getCurrentScreenY() - 25, toward));
		break;
	case 2:
		pMovingObject->getEngine()->appendObjectToArray(new Fire(pMovingObject->pGameEngine, pMovingObject->pGameTileManager, pMovingObject->getCurrentScreenX() + 5, pMovingObject->getCurrentScreenY() + 40, toward));
		break;
	case 3:
		pMovingObject->getEngine()->appendObjectToArray(new Fire(pMovingObject->pGameEngine, pMovingObject->pGameTileManager, pMovingObject->getCurrentScreenX() - 20, pMovingObject->getCurrentScreenY() + 10, toward));
		break;
	case 4:
		pMovingObject->getEngine()->appendObjectToArray(new Fire(pMovingObject->pGameEngine, pMovingObject->pGameTileManager, pMovingObject->getCurrentScreenX() + 30, pMovingObject->getCurrentScreenY() + 10, toward));
		break;
	default:
		break;
	}
}









