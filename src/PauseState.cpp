#include "PauseState.h"
#include "GameEngine.h"

PauseState::PauseState(GameEngine* pGameEngine, PlayerObject* pPlayerObject, GameTileManager* pGameTileManager, std::vector<EnemyObject*> pEnemyObjects, std::vector<Fire*> pFire)
	: RunState(pGameEngine, pPlayerObject, pGameTileManager, pEnemyObjects, pFire)
{
}

PauseState::~PauseState()
{
}

void PauseState::virtSetupBackgroundBuffer()
{
	drawSaveButton();
}

void PauseState::virtDrawStringsOnTop()
{
	getPGameEngine()->drawForegroundString(400, 320,
		"Pausing...", 0xFFFFFF,
		getPGameEngine()->getFont("Cornerstone Regular.ttf", 60));
	getPGameEngine()->drawForegroundString(300, 420,
		"Press space to continue", 0xFFFFFF,
		getPGameEngine()->getFont("Cornerstone Regular.ttf", 32));

	// Level
	if (pPlayerObject->pGameTileManager->levelController.currentLevel == 1)
	{
		this->getPGameEngine()->drawForegroundString(1030, 50,
			"Level 1", 0xFFFFFF,
			this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 45));
	} 
	else if (pPlayerObject->pGameTileManager->levelController.currentLevel == 2)
	{
		this->getPGameEngine()->drawForegroundString(1030, 50,
			"Level 2", 0xFFFFFF,
			this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 45));
	}

	// HP
	this->getPGameEngine()->drawForegroundString(1030, 170,
		"HP", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 45));

	// MP
	this->getPGameEngine()->drawForegroundString(1030, 320,
		"MP", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 45));

	// bag
	this->getPGameEngine()->drawForegroundString(1030, 470,
		"Bag", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 45));

	this->getPGameEngine()->drawForegroundString(1035, 535,
		"1", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 16));
	this->getPGameEngine()->drawForegroundString(1115, 535,
		"2", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 16));
	this->getPGameEngine()->drawForegroundString(1195, 535,
		"3", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 16));
	this->getPGameEngine()->drawForegroundString(1035, 615,
		"4", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 16));
	this->getPGameEngine()->drawForegroundString(1115, 615,
		"5", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 16));
	this->getPGameEngine()->drawForegroundString(1195, 615,
		"6", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 16));

	getPGameEngine()->drawForegroundString(1065, 723,
		"Save", 0xFFFFFF,
		getPGameEngine()->getFont("Cornerstone Regular.ttf", 28));
}

void PauseState::virtKeyDown(int iKeyCode)
{
	if (getPGameEngine()->isKeyPressed(SDLK_SPACE))
	{
		//switch (pGameTileManager->levelController.currentLevel)
		//{
		//case 1:
		//	getPGameEngine()->pGameState = getPGameEngine()->runLevelOneState;
		//	break;
		//case 2:
		//	getPGameEngine()->pGameState = getPGameEngine()->runLevelTwoState;
		//	break;
		//default:
		//	break;
		//}
		getPGameEngine()->pPauseState = getPGameEngine()->pSSP.getRawPointer();
		getPGameEngine()->pSSP.unPauseState(getPGameEngine()->pGameState);
		//getPGameEngine()->unpause();
		//getPGameEngine()->setAllObjectsVisible(true);
		//getPGameEngine()->lockAndSetupBackground();
	}
}
