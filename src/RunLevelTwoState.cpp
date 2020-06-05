#include "RunLevelTwoState.h"
#include "GameEngine.h"

RunLevelTwoState::RunLevelTwoState(GameEngine* pGameEngine, PlayerObject* pPlayerObject, GameTileManager* pGameTileManager, std::vector<EnemyObject*> pEnemyObjects, std::vector<Fire*> pFire, bool isLoad)
	: RunState(pGameEngine, pPlayerObject, pGameTileManager, pEnemyObjects, pFire, isLoad)
{
}

RunLevelTwoState::~RunLevelTwoState()
{
}

void RunLevelTwoState::virtSetupBackgroundBuffer()
{
	getPGameEngine()->redrawDisplay();

	getPGameEngine()->fillBackground(0x000000);

	pGameTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());	// Draw all tiles to the background

	// Player HP
	drawHPBox();

	// Player MP
	drawMPBox();

	// draw Bag
	drawBagBorders();
	pPlayerObject->pBagController->pBagTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());

	// save button
	drawSaveButton();
}

void RunLevelTwoState::virtInitialiseObjects()
{
	this->getPGameEngine()->drawableObjectsChanged();
	this->getPGameEngine()->destroyOldObjects(true);
	this->getPGameEngine()->createObjectArray(10);
	this->getPGameEngine()->storeObjectInArray(0, pPlayerObject);
	if (isLoad)
	{
		addObjects();
	}
	else
	{
		this->getPGameEngine()->storeObjectInArray(1, new EnemyTypeOne(this->getPGameEngine(), pGameTileManager, 900, 90, pPlayerObject));
		this->getPGameEngine()->storeObjectInArray(2, new EnemyTypeSix(this->getPGameEngine(), pGameTileManager, 100, 100, pPlayerObject));
		this->getPGameEngine()->storeObjectInArray(3, new EnemyTypeThree(this->getPGameEngine(), pGameTileManager, 770, 100, pPlayerObject));
		this->getPGameEngine()->storeObjectInArray(6, new EnemyTypeFive(this->getPGameEngine(), pGameTileManager, 200, 100, pPlayerObject));
		this->getPGameEngine()->storeObjectInArray(4, new EnemyTypeFour(this->getPGameEngine(), pGameTileManager, 520, 100, pPlayerObject));
		this->getPGameEngine()->storeObjectInArray(5, new EnemyTypeFive(this->getPGameEngine(), pGameTileManager, 680, 420, pPlayerObject));
	}
	this->getPGameEngine()->setAllObjectsVisible(true);
}

void RunLevelTwoState::virtDrawStringsOnTop()
{
	if (pPlayerObject->isSuccessful)
	{
		getPGameEngine()->drawForegroundString(350, 323,
			"You made it!", 0xFFFFFF,
			getPGameEngine()->getFont("Cornerstone Regular.ttf", 60));
		getPGameEngine()->pause();
	}

	if (isSaving && getPGameEngine()->getRawTime() - saveTimer <= 750)
	{
		getPGameEngine()->lockBackgroundForDrawing();
		getPGameEngine()->drawBackgroundString(330, 320,
			"Saving the game...", 0xFFFFFF,
			getPGameEngine()->getFont("Cornerstone Regular.ttf", 60));
		getPGameEngine()->unlockBackgroundForDrawing();
	}
	else if (isSaving && getPGameEngine()->getRawTime() - saveTimer > 750)
	{
		isSaving = false;
		getPGameEngine()->lockAndSetupBackground();
	}

	// Level
	this->getPGameEngine()->drawForegroundString(1030, 50,
		"Level 2", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 45));

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
