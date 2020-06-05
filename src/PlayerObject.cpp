#include "PlayerObject.h"
#include "GameEngine.h"

PlayerObject::PlayerObject(GameEngine* pGameEngine, GameTileManager* pGameTileManager, std::string name, int xStart, int yStart, int HP, int MP, int toward, int isUnderAttack, std::string theBag)
	: MovingObject(pGameEngine, pGameTileManager, xStart, yStart)
	, name(name)
{
	if (xStart == 0 && yStart == 0)
	{
		pGameTileManager->setBornPlace(&m_iCurrentScreenX, &m_iCurrentScreenY);
	}
	pMovingController = new PlayerMovingController(this);
	pMovingController->toward = toward;
	pMovingController->isUnderAttack = isUnderAttack;
	pBagController = new BagController(this, theBag);
	int test[5] = { 1, 2, 3, 4, 5 };
	this->HP = HP;
	this->MP = MP;
	typeName = "player";
	actual_height = 45;
	actual_width = 44;

	loadImage();
	loadMovingImages();

	virtInitializeUncrossable();
	virtInitializeAttackable();
	
}

PlayerObject::~PlayerObject()
{
	delete pBagController;
}

void PlayerObject::virtDraw()
{
	pMovingController->drawMovingImages();

	drawHP();

	drawMP();
}

void PlayerObject::virtDoUpdate(int iCurrentTime)
{
	if (!pGameEngine->isPaused())
	{
		if (isNextLevel())
		{
			if (pGameTileManager->levelController.currentLevel == 2)
			{
				isSuccessful = true;
				if (!isWinPlaying)
				{
					pGameEngine->pAudioManager->PlaySFX("win.wav");
					isWinPlaying = true;
					pGameEngine->redrawDisplay();
				}
			}
			else
			{
				pGameTileManager->levelController.nextLevel();
				pGameTileManager->updateMapValues();
				getEngine()->removeDisplayableObject(this);
				pGameTileManager->setBornPlace(&m_iCurrentScreenX, &m_iCurrentScreenY);
				std::vector<EnemyObject*> enemyObjects;
				std::vector<Fire*> fireObjects;
				pGameEngine->pSSP.switchState(new RunLevelTwoState(pGameEngine, this, this->pGameTileManager, enemyObjects, fireObjects, false));
			}
		}
		else
		{
			if (!isDead())
			{
				pMovingController->handleMovement(iCurrentTime);
				updateBag();
				pBagController->useProps();
				redrawDisplay();
			}
			else
			{
				if (!isDiePlaying)
				{
					pGameEngine->pAudioManager->PlaySFX("die.wav");
					isDiePlaying = true;
				}
				printDie();
				getEngine()->removeDisplayableObject(this);
				setCurrenrtScreenPosition(9999, 9999);
				redrawDisplay();
			}
		}
	}
}

void PlayerObject::virtInitializeUncrossable()
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
	uncrossable.push_back(6);
	uncrossable.push_back(7);
	uncrossable.push_back(10);
}

void PlayerObject::virtInitializeAttackable()
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
	unattackble.push_back(6);
	unattackble.push_back(10);
}

bool PlayerObject::isNextLevel()
{
	bool isNext = false;
	int topY, bottomY, leftX, rightX;
	pGameTileManager->getFinalArea(&topY, &bottomY, &leftX, &rightX);
	if (getXCentre() < rightX && getXCentre() > leftX && getYCentre() < bottomY && getYCentre() > topY)
	{
		isNext = true;
	}
	return isNext;
}

bool PlayerObject::isDead()
{
	bool isDead = false;
	if (HP <= 0)
	{
		isDead = true;
	}
	return isDead;
}

void PlayerObject::printDie()
{
	getEngine()->lockBackgroundForDrawing();
	getEngine()->drawBackgroundString(400, 300,
		"You are dead!", 0xFF0000,
		getEngine()->getFont("Cornerstone Regular.ttf", 60));
	getEngine()->drawBackgroundString(460, 380, 
		"Game Over!", 0xFF0000,
		getEngine()->getFont("Cornerstone Regular.ttf", 60));
	getEngine()->unlockBackgroundForDrawing();
}

void PlayerObject::updateBag()
{
	if (pBagController->isBagFull() != -1)
	{
		int keys = pGameTileManager->validateKey(this, pGameEngine, pGameEngine->getBackgroundSurface());
		int hps = pGameTileManager->validateHP(this, pGameEngine, pGameEngine->getBackgroundSurface());
		int mps = pGameTileManager->validateMP(this, pGameEngine, pGameEngine->getBackgroundSurface());
		for (int i = 0; i < keys; i++)
		{
			pBagController->addProps(1);
		}
		for (int j = 0; j < hps; j++)
		{
			pBagController->addProps(2);
		}
		for (int k = 0; k < mps; k++)
		{
			pBagController->addProps(3);
		}
		if (keys || hps || mps)
		{
			pBagController->printBag();
		}
	}
}

void PlayerObject::drawHP()
{
	if (HP >= 0)
	{
		int HP_X = (int)(HP / 100.0 * (1225 - 1035) + 1035);
		getEngine()->lockForegroundForDrawing();
		getEngine()->drawForegroundRectangle(1035, 225, HP_X, 265, 0xDC143C);
		getEngine()->unlockForegroundForDrawing();
	}
}

void PlayerObject::drawMP()
{
	if (MP >= 0)
	{
		int MP_X = (int)(MP / 1500.0 * (1225 - 1035) + 1035);
		getEngine()->lockForegroundForDrawing();
		getEngine()->drawForegroundRectangle(1035, 375, MP_X, 415, 0x0000FF);
		getEngine()->unlockForegroundForDrawing();
	}
}

