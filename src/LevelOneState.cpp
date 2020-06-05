#include "LevelOneState.h"
#include "GameEngine.h"

LevelOneState::LevelOneState(GameEngine* pGameEngine, std::string name)
	: GameState(pGameEngine)
	, gameTileManager(20, 20)
	, pPlayerObject(new PlayerObject(getPGameEngine(), &gameTileManager, name))
{
	
}

LevelOneState::~LevelOneState()
{
}

void LevelOneState::virtSetupBackgroundBuffer()
{
	std::cout << "Level One..." << std::endl;

	this->getPGameEngine()->fillBackground(0x000000);

	gameTileManager.drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());	// Draw all tiles to the background
	pPlayerObject->pBagController->pBagTileManager->drawAllTiles(getPGameEngine(), getPGameEngine()->getBackgroundSurface());
	// Player HP
	this->getPGameEngine()->drawBackgroundThickLine(1030, 220, 1230, 220, 0xFFFFFF, 2);
	this->getPGameEngine()->drawBackgroundThickLine(1030, 220, 1030, 270, 0xFFFFFF, 2);
	this->getPGameEngine()->drawBackgroundThickLine(1030, 270, 1230, 270, 0xFFFFFF, 2);
	this->getPGameEngine()->drawBackgroundThickLine(1230, 220, 1230, 270, 0xFFFFFF, 2);

	// Player MP
	this->getPGameEngine()->drawBackgroundThickLine(1030, 370, 1230, 370, 0xFFFFFF, 2);
	this->getPGameEngine()->drawBackgroundThickLine(1030, 370, 1030, 420, 0xFFFFFF, 2);
	this->getPGameEngine()->drawBackgroundThickLine(1030, 420, 1230, 420, 0xFFFFFF, 2);
	this->getPGameEngine()->drawBackgroundThickLine(1230, 370, 1230, 420, 0xFFFFFF, 2);

	drawBagBorders();
}

void LevelOneState::virtInitialiseObjects()
{
	this->getPGameEngine()->drawableObjectsChanged();
	this->getPGameEngine()->destroyOldObjects(true);
	this->getPGameEngine()->createObjectArray(10);
	this->getPGameEngine()->storeObjectInArray(0, pPlayerObject);
	this->getPGameEngine()->storeObjectInArray(1, new EnemyTypeOne(this->getPGameEngine(), &gameTileManager, 150, 90, pPlayerObject));
	this->getPGameEngine()->storeObjectInArray(2, new EnemyTypeTwo(this->getPGameEngine(), &gameTileManager, 300, 100, pPlayerObject));
	this->getPGameEngine()->storeObjectInArray(3, new EnemyTypeThree(this->getPGameEngine(), &gameTileManager, 400, 100, pPlayerObject));
	this->getPGameEngine()->storeObjectInArray(4, new EnemyTypeFour(this->getPGameEngine(), &gameTileManager, 520, 100, pPlayerObject));
	this->getPGameEngine()->storeObjectInArray(5, new EnemyTypeFive(this->getPGameEngine(), &gameTileManager, 580, 100, pPlayerObject));
	this->getPGameEngine()->storeObjectInArray(6, new EnemyTypeSix(this->getPGameEngine(), &gameTileManager, 580, 160, pPlayerObject));
	this->getPGameEngine()->setAllObjectsVisible(true);
}

void LevelOneState::virtDrawStringsOnTop()
{
	// Level
	this->getPGameEngine()->drawForegroundString(1030, 50,
		"Level 1", 0xFFFFFF,
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
}

void LevelOneState::drawBagBorders()
{
	getPGameEngine()->drawBackgroundThickLine(1030, 530, 1270, 530, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1030, 690, 1270, 690, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1030, 530, 1030, 690, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1270, 530, 1270, 690, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1030, 610, 1270, 610, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1110, 530, 1110, 690, 0xFFFFFF, 2);
	getPGameEngine()->drawBackgroundThickLine(1190, 530, 1190, 690, 0xFFFFFF, 2);
}
