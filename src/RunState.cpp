#include "RunState.h"
#include "GameEngine.h"

RunState::RunState(GameEngine* pGameEngine, PlayerObject* pPlayerObject, GameTileManager* pGameTileManager, std::vector<EnemyObject*> pEnemyObjects, std::vector<Fire*> pFire, bool isLoad)
	: GameState(pGameEngine)
	, m_filterScaling(0, 0, getPGameEngine()), m_filterTranslation(0, 0, &m_filterScaling)
	, pPlayerObject(pPlayerObject)
	, pGameTileManager(pGameTileManager)
	, saveButton(getPGameEngine()->loadImage("images/button.png", false))
	, enemyObjects(pEnemyObjects)
	, fireObjects(pFire)
	, isLoad(isLoad)
	, m_bDragging(false)
{
	saveButton = saveButton.resizeTo(150, 55);
	getPGameEngine()->getBackgroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	getPGameEngine()->getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	getPGameEngine()->pAudioManager->PauseMusic();
}

RunState::~RunState()
{
}

void RunState::drawBagBorders()
{
	getPGameEngine()->drawBackgroundThickLine(1030, 530, 1270, 530, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1030, 690, 1270, 690, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1030, 530, 1030, 690, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1270, 530, 1270, 690, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1030, 610, 1270, 610, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1110, 530, 1110, 690, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1190, 530, 1190, 690, 0xFFFFFF, 2);
}

void RunState::drawHPBox()
{
	getPGameEngine()->drawBackgroundThickLine(1030, 220, 1230, 220, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1030, 220, 1030, 270, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1030, 270, 1230, 270, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1230, 220, 1230, 270, 0xFFFFFF, 2);
}

void RunState::drawMPBox()
{
	getPGameEngine()->drawBackgroundThickLine(1030, 370, 1230, 370, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1030, 370, 1030, 420, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1030, 420, 1230, 420, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1230, 370, 1230, 420, 0xFFFFFF, 2);
}

void RunState::drawSaveButton()
{
	saveButton.renderImageWithMask(getPGameEngine()->getBackgroundSurface(), 0, 0, 1030, 715, saveButton.getWidth(), saveButton.getHeight());
}

void RunState::pauseGame()
{
	std::vector<EnemyObject*> enemyObjects;
	std::vector<Fire*> fireObjects;

	getPGameEngine()->pGameState = getPGameEngine()->pSSP.getRawPointer();
	if (getPGameEngine()->pPauseState == nullptr)
	{
		getPGameEngine()->pPauseState = new PauseState(getPGameEngine(), pPlayerObject, pGameTileManager, enemyObjects, fireObjects);
	}
	getPGameEngine()->pSSP.pauseState(getPGameEngine()->pPauseState);
}

void RunState::saveGame()
{
	std::ofstream outfile;
	outfile.open("archive.txt");
	
	// Save the map
	saveMap(&outfile);

	// Save player's data
	savePlayerData(&outfile);

	// Save enemy's data
	// Get all alive enemy objects
	for (int index = 0; index < getPGameEngine()->getContentCount(); index++)
	{
		if (getPGameEngine()->getContentItem(index) != nullptr)
		{
			MovingObject* pMovingObject = (MovingObject*)getPGameEngine()->getContentItem(index);
			if (pMovingObject->typeName.compare("player") != 0 && pMovingObject->typeName.compare("fire") != 0)
			{
				saveEnemyData(&outfile, (EnemyObject*)pMovingObject);
			}
		}
	}
	outfile << "fire" << std::endl;
	for (int index = 0; index < getPGameEngine()->getContentCount(); index++)
	{
		if (getPGameEngine()->getContentItem(index) != nullptr)
		{
			MovingObject* pMovingObject = (MovingObject*)getPGameEngine()->getContentItem(index);

			if (pMovingObject->typeName.compare("fire") == 0)
			{
				saveFireData(&outfile, (Fire*)pMovingObject);
			}
		}
	}



	outfile.close();
}

void RunState::saveMap(std::ofstream* file)
{
	*file << pGameTileManager->levelController.currentLevel << std::endl;
	for (int i = 0; i < pGameTileManager->getMapHeight(); i++)
	{
		for (int j = 0; j < pGameTileManager->getMapWidth(); j++)
		{
			if (pGameTileManager->getMapValue(j, i) < 10)
			{
				*file << pGameTileManager->getMapValue(j, i);
			}
			else
			{
				char c = pGameTileManager->getMapValue(j, i) - 10 + 'a';
				*file << c;
			}
		}
		*file << std::endl;
	}
}

void RunState::savePlayerData(std::ofstream* file)
{
	if (pPlayerObject->name.empty())
	{
		*file << "(null)" << std::endl;
	}
	else
	{
		*file << pPlayerObject->name << std::endl;	// name
	}
	*file << pPlayerObject->HP << std::endl;	// hp
	*file << pPlayerObject->MP << std::endl;	// mp
	*file << pPlayerObject->getCurrentScreenX() << std::endl;	// X
	*file << pPlayerObject->getCurrentScreenY() << std::endl;	// Y
	*file << pPlayerObject->pMovingController->toward << std::endl;	// toward
	*file << pPlayerObject->pMovingController->isUnderAttack << std::endl;	// isUnderAttack
	char bagArray[10];
	pPlayerObject->pBagController->getBagArray(bagArray);
	*file << bagArray << std::endl;	// bag array
}

void RunState::saveEnemyData(std::ofstream* file, EnemyObject* pEnemyObject)
{
	*file << pEnemyObject->typeName << std::endl;	// type name
	*file << pEnemyObject->HP << std::endl;				// hp
	*file << pEnemyObject->getCurrentScreenX() << std::endl;	// X
	*file << pEnemyObject->getCurrentScreenY() << std::endl;	// Y
	*file << pEnemyObject->pMovingController->toward << std::endl;	// toward
	*file << pEnemyObject->pMovingController->isUnderAttack << std::endl;	// isUnderAttack
	*file << pEnemyObject->pMovingController->isUnderFire << std::endl;		// isUnderFire
}

void RunState::saveFireData(std::ofstream* file, Fire* pFire)
{
	*file << pFire->typeName << std::endl;		// type name
	*file << pFire->getCurrentScreenX() << std::endl;	// X
	*file << pFire->getCurrentScreenY() << std::endl;	// Y
	*file << pFire->pMovingController->toward << std::endl;	// toward
	*file << pFire->pMovingController->totalDistance << std::endl;	// total distance
}

void RunState::addObjects()
{
	int index = 1;
	for (std::vector<EnemyObject*>::iterator iter = enemyObjects.begin(); iter != enemyObjects.end(); iter++, index++)
	{
		std::cout << "loading enemy" << std::endl;
		this->getPGameEngine()->storeObjectInArray(index, *iter);
	}
	for (std::vector<Fire*>::iterator iter = fireObjects.begin(); iter != fireObjects.end(); iter++, index++)
	{
		std::cout << "loading fire" << std::endl;
		this->getPGameEngine()->storeObjectInArray(index, *iter);
	}
}

void RunState::virtRealMouseDown(int iButton, int iX, int iY)
{
	if (!pPlayerObject->isDead())
	{
		int width = getPGameEngine()->getWindowWidth();
		int height = getPGameEngine()->getWindowHeight();
		if (iX < 50 && iY > height - 50)
		{
			getPGameEngine()->fillBackground(0);
			zoomIn();
			getPGameEngine()->lockBackgroundForDrawing();
			drawBagBorders();
			drawHPBox();
			drawMPBox();
			drawSaveButton();
			getPGameEngine()->unlockBackgroundForDrawing();
			pGameTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
			pPlayerObject->pBagController->pBagTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
		}
		if (iX > width - 50 && iY > height - 50)
		{
			getPGameEngine()->fillBackground(0);
			zoomOut();
			getPGameEngine()->lockBackgroundForDrawing();
			drawBagBorders();
			drawHPBox();
			drawMPBox();
			drawSaveButton();
			getPGameEngine()->unlockBackgroundForDrawing();
			pGameTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
			pPlayerObject->pBagController->pBagTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
		}
		getPGameEngine()->redrawDisplay();
	}
}

void RunState::virtKeyDown(int iKeyCode)
{
	if (iKeyCode == SDLK_p && !pPlayerObject->isDead() && !pPlayerObject->isDead())
	{
		pauseGame();
	}
}

void RunState::virtMouseDown(int iButton, int iX, int iY)
{
	if (	iX >= 1030 && iX <= 1030 + saveButton.getWidth() 
		&&	iY >= 715 && iY <= 715 + saveButton.getHeight())
	{
		std::cout << "Saving the game..." << std::endl;
		isSaving = true;
		saveTimer = getPGameEngine()->getRawTime();
		saveGame();
	}
	getPGameEngine()->redrawDisplay();
}

void RunState::getCurrentTime(char* currentTime)
{
	time_t timep;
	time(&timep);
	strftime(currentTime, sizeof(20 * sizeof(char)), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	std::cout << currentTime << std::endl;
}

void RunState::virtMouseWheel(int x, int y, int which, int timestamp)
{
	if (!pPlayerObject->isDead())
	{
		int iOldCentreX = getPGameEngine()->convertClickedToVirtualPixelXPosition(getPGameEngine()->getWindowWidth() / 2);
		int iOldCentreY = getPGameEngine()->convertClickedToVirtualPixelYPosition(getPGameEngine()->getWindowHeight() / 2);

		if (y < 0)
		{
			getPGameEngine()->fillBackground(0);
			zoomOut();
			getPGameEngine()->lockBackgroundForDrawing();
			drawBagBorders();
			drawHPBox();
			drawMPBox();
			drawSaveButton();
			getPGameEngine()->unlockBackgroundForDrawing();
			pGameTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
			pPlayerObject->pBagController->pBagTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
		}

		else if (y > 0)
		{
			getPGameEngine()->fillBackground(0);
			zoomIn();
			getPGameEngine()->lockBackgroundForDrawing();
			drawBagBorders();
			drawHPBox();
			drawMPBox();
			drawSaveButton();
			getPGameEngine()->unlockBackgroundForDrawing();
			pGameTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
			pPlayerObject->pBagController->pBagTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
		}

		int iNewCentreX = getPGameEngine()->convertClickedToVirtualPixelXPosition(getPGameEngine()->getWindowWidth() / 2);
		int iNewCentreY = getPGameEngine()->convertClickedToVirtualPixelYPosition(getPGameEngine()->getWindowHeight() / 2);

		m_filterTranslation.changeOffset(iNewCentreX - iOldCentreX, iNewCentreY - iOldCentreY);

		getPGameEngine()->redrawDisplay();
	}
}

void RunState::virtMouseUp(int iButton, int iX, int iY)
{
	if (!pPlayerObject->isDead())
	{
		if (m_bDragging)
		{
			m_filterTranslation.changeOffset(iX - m_iClickedX, iY - m_iClickedY);
			m_bDragging = false;
			getPGameEngine()->fillBackground(0);
			getPGameEngine()->lockBackgroundForDrawing();
			drawBagBorders();
			drawHPBox();
			drawMPBox();
			drawSaveButton();
			getPGameEngine()->unlockBackgroundForDrawing();
			pGameTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
			pPlayerObject->pBagController->pBagTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
			getPGameEngine()->redrawDisplay();
		}
	}
}

void RunState::virtMouseMoved(int iX, int iY)
{
	if (!pPlayerObject->isDead())
	{
		if (m_bDragging)
		{
			getPGameEngine()->fillBackground(0);
			m_filterTranslation.changeOffset(iX - m_iClickedX, iY - m_iClickedY);
			getPGameEngine()->lockBackgroundForDrawing();
			drawBagBorders();
			drawHPBox();
			drawMPBox();
			drawSaveButton();
			getPGameEngine()->unlockBackgroundForDrawing();
			pGameTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
			pPlayerObject->pBagController->pBagTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
			getPGameEngine()->redrawDisplay();
		}
	}
	
}

void RunState::virtBackgroundMouseDown(int iButton, int iRealX, int iRealY, int iVirtualX, int iVirtualY)
{
	if (!pPlayerObject->isDead())
	{
		m_bDragging = true;
		m_iClickedX = iVirtualX;
		m_iClickedY = iVirtualY;
	}
}

void RunState::virtPostDraw()
{
	int width = getPGameEngine()->getWindowWidth();
	int height = getPGameEngine()->getWindowHeight();

	getPGameEngine()->getForegroundSurface()->rawDrawOval(5, height - 5, 45, height - 45, 0x000000);
	getPGameEngine()->getForegroundSurface()->rawDrawOval(20, height - 20, 30, height - 30, 0xffffff);
	getPGameEngine()->getForegroundSurface()->rawDrawOval(width - 5, height - 5, width - 45, height - 45, 0x000000);
	getPGameEngine()->getForegroundSurface()->rawDrawOval(width - 10, height - 10, width - 40, height - 40, 0xffffff);
}

void RunState::zoomOut()
{
	int iOldCentreX = getPGameEngine()->convertClickedToVirtualPixelXPosition(getPGameEngine()->getWindowWidth() / 2);
	int iOldCentreY = getPGameEngine()->convertClickedToVirtualPixelYPosition(getPGameEngine()->getWindowHeight() / 2);
	m_filterScaling.compress();
	int iNewCentreX = getPGameEngine()->convertClickedToVirtualPixelXPosition(getPGameEngine()->getWindowWidth() / 2);
	int iNewCentreY = getPGameEngine()->convertClickedToVirtualPixelYPosition(getPGameEngine()->getWindowHeight() / 2);
	m_filterTranslation.changeOffset(iNewCentreX - iOldCentreX, iNewCentreY - iOldCentreY);
	getPGameEngine()->redrawDisplay();
}

void RunState::zoomIn()
{
	int iOldCentreX = getPGameEngine()->convertClickedToVirtualPixelXPosition(getPGameEngine()->getWindowWidth() / 2);
	int iOldCentreY = getPGameEngine()->convertClickedToVirtualPixelYPosition(getPGameEngine()->getWindowHeight() / 2);
	m_filterScaling.stretch();
	int iNewCentreX = getPGameEngine()->convertClickedToVirtualPixelXPosition(getPGameEngine()->getWindowWidth() / 2);
	int iNewCentreY = getPGameEngine()->convertClickedToVirtualPixelYPosition(getPGameEngine()->getWindowHeight() / 2);
	m_filterTranslation.changeOffset(iNewCentreX - iOldCentreX, iNewCentreY - iOldCentreY);
	getPGameEngine()->redrawDisplay();
}
