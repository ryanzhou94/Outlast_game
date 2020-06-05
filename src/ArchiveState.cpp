#include "ArchiveState.h"
#include "GameEngine.h"

ArchiveState::ArchiveState(GameEngine* pGameEngine)
	: GameState(pGameEngine)
	, background(this->getPGameEngine()->loadImage("images/Archive_Background.BMP", false/*don't keep it loaded*/))
	, button(this->getPGameEngine()->loadImage("images/button.png", false/*don't keep it loaded*/))
	, bar(this->getPGameEngine()->loadImage("images/bar.png", false/*don't keep it loaded*/))
{
	button = button.resizeTo(200, 70);
	bar = bar.resizeTo(650, 110);
}

ArchiveState::~ArchiveState()
{
}

void ArchiveState::virtSetupBackgroundBuffer()
{
	this->getPGameEngine()->redrawDisplay();

	std::cout << "Archive state..." << std::endl;

	// Background
	background.renderImageBlit(this->getPGameEngine(),
		this->getPGameEngine()->getBackgroundSurface(),
		0, 0,
		this->getPGameEngine()->getWindowWidth(), this->getPGameEngine()->getWindowHeight(),
		0, 0,
		background.getWidth(), background.getHeight());

	// archive 1
	bar.renderImageWithMask(getPGameEngine()->getBackgroundSurface(), 0, 0, 330, 260, bar.getWidth(), bar.getHeight());

	// archive 2
	bar.renderImageWithMask(getPGameEngine()->getBackgroundSurface(), 0, 0, 330, 440, bar.getWidth(), bar.getHeight());

	// Return Button
	button.renderImageWithMask(getPGameEngine()->getBackgroundSurface(), 0, 0, 550, 640, button.getWidth(), button.getHeight());
}

void ArchiveState::virtDrawStringsOnTop()
{
	getPGameEngine()->drawForegroundString(580, 653,
		"Return", 0xFFFFFF,
		getPGameEngine()->getFont("Cornerstone Regular.ttf", 35));

	getPGameEngine()->drawForegroundString(555, 290,
		"Archive 1", 0xFFFFFF,
		getPGameEngine()->getFont("Cornerstone Regular.ttf", 35));

	getPGameEngine()->drawForegroundString(470, 468,
		"Not available now", 0xFFFFFF,
		getPGameEngine()->getFont("Cornerstone Regular.ttf", 35));

	getPGameEngine()->drawForegroundString(520, 100,
		"Archive", 0xFFFFFF,
		getPGameEngine()->getFont("Cornerstone Regular.ttf", 60));

	getPGameEngine()->drawForegroundString(565, 170,
		"Click to load", 0xFFFFFF,
		getPGameEngine()->getFont("Cornerstone Regular.ttf", 22));

}

void ArchiveState::virtMouseDown(int iButton, int X, int Y)
{
	// load archive
	if (X >= 330 
		&& X <= 330 + +bar.getWidth()
		&& Y >= 260
		&& Y <= 260 + bar.getHeight())
	{
		std::ifstream file;
		file.open("archive.txt");
		if (!file)
		{
			std::cout << "The 'archive.txt' doesn't exist, cannot load game" << std::endl;
			file.close();
			return;
		}
		GameTileManager* tile = nullptr;
		PlayerObject* player = nullptr;
		std::vector<EnemyObject*> enemyObjects;
		std::vector<Fire*> fireObjects;
		loadGame(&file, &tile, &player, &enemyObjects, &fireObjects);
		file.close();
		switch (tile->levelController.currentLevel)
		{
		case 1:
			getPGameEngine()->pSSP.switchState(new RunLevelOneState(getPGameEngine(), player, tile, enemyObjects, fireObjects, true));
			break;
		case 2:
			getPGameEngine()->pSSP.switchState(new RunLevelTwoState(getPGameEngine(), player, tile, enemyObjects, fireObjects, true));
			break;
		default:
			break;
		}
		return;
	}
	
	// return 
	if (X >= 550
		&& X <= 550 + +button.getWidth()
		&& Y >= 650
		&& Y <= 650 + button.getHeight())
	{
		getPGameEngine()->pSSP.switchState(new InitialState(this->getPGameEngine()));
		return;
	}
}

void ArchiveState::loadGame(std::ifstream* file, GameTileManager** pGameTileManager, PlayerObject** pPlayerObject, std::vector<EnemyObject*>* pEnemyObjects, std::vector<Fire*>* pFire)
{
	loadMap(file, pGameTileManager);
	loadPlayer(file, pPlayerObject, *pGameTileManager);
	loadEnemy(file, pEnemyObjects, *pGameTileManager, *pPlayerObject);
	loadFire(file, pFire, *pGameTileManager);
}

void ArchiveState::loadMap(std::ifstream* file, GameTileManager** pGameTileManager)
{
	std::string tempStr;
	*file >> tempStr;
	int level = atoi(tempStr.c_str());
	*pGameTileManager = new GameTileManager(20, 20, true);
	(*pGameTileManager)->levelController.currentLevel = level;
	for (int Y = 0; Y < 15; Y++)
	{
		*file >> tempStr;
		for (int X = 0; X < 20; X++)
		{
			if (tempStr[X] >= 97 && tempStr[X] <= 122)
			{
				(*pGameTileManager)->setMapValue(X, Y, tempStr[X] - 97 + 10);
			}
			else if (tempStr[X] >= 48 && tempStr[X] <= 57)
			{
				(*pGameTileManager)->setMapValue(X, Y, tempStr[X] - 48);
			}
		}
	}
}

void ArchiveState::loadPlayer(std::ifstream* file, PlayerObject** pPlayerObject, GameTileManager* pGameTileManager)
{
	std::string tempStr;
	*file >> tempStr;
	std::string name = "";
	if (!tempStr.empty())
	{
		name = tempStr;
	}
	std::cout << "Name: " << name << std::endl;
	*file >> tempStr;
	int HP = atoi(tempStr.c_str());
	std::cout << "HP: " << HP << std::endl;
	*file >> tempStr;
	int MP = atoi(tempStr.c_str());
	std::cout << "MP: " << MP << std::endl;
	*file >> tempStr;
	int X = atoi(tempStr.c_str());
	std::cout << "X: " << X << std::endl;
	*file >> tempStr;
	int Y = atoi(tempStr.c_str());
	std::cout << "Y: " << Y << std::endl;
	*file >> tempStr;
	int toward = atoi(tempStr.c_str());
	std::cout << "toward : " << toward << std::endl;
	*file >> tempStr;
	bool isUnderAttack = atoi(tempStr.c_str());
	std::cout << "isUnderAttack : " << isUnderAttack << std::endl;
	*file >> tempStr;
	std::string bag = tempStr;
	std::cout << "Bag: " << bag << std::endl;
	*pPlayerObject = new PlayerObject(getPGameEngine(), pGameTileManager, name, X, Y, HP, MP, toward, isUnderAttack, bag);
}

void ArchiveState::loadEnemy(std::ifstream* file, std::vector<EnemyObject*>* pEnemyObjects, GameTileManager* pGameTileManager, MovingObject* pPlayerObject)
{
	std::string tempStr;
	*file >> tempStr;
	while (tempStr.compare("fire"))
	{
		EnemyObject* enemy = nullptr;
		std::string typeName = tempStr;
		*file >> tempStr;
		int HP = atoi(tempStr.c_str());
		*file >> tempStr;
		int X = atoi(tempStr.c_str());
		*file >> tempStr;
		int Y = atoi(tempStr.c_str());
		*file >> tempStr;
		int toward = atoi(tempStr.c_str());
		*file >> tempStr;
		bool isUnderAttack = atoi(tempStr.c_str());
		*file >> tempStr;
		bool isUnderFire = atoi(tempStr.c_str());
		if (typeName.compare("enemy_one") == 0)
		{
			enemy = new EnemyTypeOne(getPGameEngine(), pGameTileManager, X, Y, pPlayerObject);
		}
		else if (typeName.compare("enemy_two") == 0)
		{
			enemy = new EnemyTypeTwo(getPGameEngine(), pGameTileManager, X, Y, pPlayerObject);
		}
		else if (typeName.compare("enemy_three") == 0)
		{
			enemy = new EnemyTypeThree(getPGameEngine(), pGameTileManager, X, Y, pPlayerObject);
		}
		else if (typeName.compare("enemy_four") == 0)
		{
			enemy = new EnemyTypeFour(getPGameEngine(), pGameTileManager, X, Y, pPlayerObject);
		}
		else if (typeName.compare("enemy_five") == 0)
		{
			enemy = new EnemyTypeFive(getPGameEngine(), pGameTileManager, X, Y, pPlayerObject);
		}
		else if (typeName.compare("enemy_six") == 0)
		{
			enemy = new EnemyTypeSix(getPGameEngine(), pGameTileManager, X, Y, pPlayerObject);
		}
		(*pEnemyObjects).push_back(enemy);
		*file >> tempStr;
	}
}

void ArchiveState::loadFire(std::ifstream* file, std::vector<Fire*>* pFire, GameTileManager* pGameTileManager)
{
	std::string tempStr;
	*file >> tempStr;
	while (tempStr.compare("fire") == 0)
	{
		Fire* fire = nullptr;
		std::string typeName = tempStr;
		*file >> tempStr;
		int X = atoi(tempStr.c_str());
		*file >> tempStr;
		int Y = atoi(tempStr.c_str());
		*file >> tempStr;
		int toward = atoi(tempStr.c_str());
		*file >> tempStr;
		int totalDistance = atoi(tempStr.c_str());
		fire = new Fire(getPGameEngine(), pGameTileManager, X, Y, toward, totalDistance);
		(*pFire).push_back(fire);
		*file >> tempStr;
	}
}

