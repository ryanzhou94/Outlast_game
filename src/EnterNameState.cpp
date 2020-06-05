#include "EnterNameState.h"
#include "GameEngine.h"

EnterNameState::EnterNameState(GameEngine* pGameEngine)
	: GameState(pGameEngine)
	, background(this->getPGameEngine()->loadImage("images/EnterName_Background.png", false/*don't keep it loaded*/))
	, button(this->getPGameEngine()->loadImage("images/button.png", false/*don't keep it loaded*/))
{
	button = button.resizeTo(200, 80);
}

EnterNameState::~EnterNameState()
{
}

void EnterNameState::virtSetupBackgroundBuffer() 
{
	getPGameEngine()->fillBackground(0x000000);
	this->getPGameEngine()->redrawDisplay();

	std::cout << "Enter Name state..." << std::endl;

	// Background
	background.renderImageBlit(this->getPGameEngine(),
		this->getPGameEngine()->getBackgroundSurface(),
		0, 0,
		this->getPGameEngine()->getWindowWidth(), this->getPGameEngine()->getWindowHeight(),
		0, 0,
		background.getWidth(), background.getHeight());

	button.renderImageWithMask(getPGameEngine()->getBackgroundSurface(), 0, 0, 420, 420, button.getWidth(), button.getHeight());

	button.renderImageWithMask(getPGameEngine()->getBackgroundSurface(), 0, 0, 700, 420, button.getWidth(), button.getHeight());

	// Input Area
	this->getPGameEngine()->drawBackgroundRectangle(
		455, 300,
		855, 370,
		0xFFFFFF
		);
}

void EnterNameState::virtDrawStringsOnTop()
{
	// State title
	this->getPGameEngine()->drawForegroundString(365, 200,
		"Enter your name", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 60));

	// Return Button
	this->getPGameEngine()->drawForegroundString(420 + 22, 420 + 15,
		"Return", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 35));

	// Confirm Button
	this->getPGameEngine()->drawForegroundString(700 + 22, 420 + 15,
		"Confirm", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 35));

	// Player name (Dynamically changes)
	std::string playerNameString = "";
	for (std::vector<char>::iterator iter = playerName.begin(); iter != playerName.end(); iter++)
	{
		playerNameString += *iter;
	}
	// Convert 'string' to 'const char*'
	const char* name = playerNameString.c_str();
	if (!playerName.empty())
	{
		this->getPGameEngine()->drawForegroundString(460, 305, name, 0x000000, this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 50));
	}
}

void EnterNameState::virtKeyDown(int iKeyCode)
{
	if ((iKeyCode >= 48 && iKeyCode <= 57) || (iKeyCode >= 97 && iKeyCode <= 122) || iKeyCode == 32)
	{
		if (playerName.size() <= 11)
		{
			playerName.push_back(iKeyCode);
		}
	}
	else if (iKeyCode == 8 && !playerName.empty())
	{
		playerName.pop_back();
	}
	this->getPGameEngine()->redrawDisplay();
}

void EnterNameState::virtMouseDown(int iButton, int iX, int iY)
{
	// Return Button: goes to Initial State
	if (iX >= 420
		&& iX <= 420 + button.getWidth()
		&& iY >= 420
		&& iY <= 420 + button.getHeight())
	{
		getPGameEngine()->pSSP.switchState(new InitialState(this->getPGameEngine()));
	}
	
	// Confirm Button: saves the name and starts a new game
	if (iX >= 700
		&& iX <= 700 + button.getWidth()
		&& iY >= 420
		&& iY <= 420 + button.getHeight())
	{
		std::string playerNameString = "";
		for (std::vector<char>::iterator iter = playerName.begin(); iter != playerName.end(); iter++)
		{
			playerNameString += *iter;
		}
		std::cout << "Player name: " << playerNameString << std::endl;
		GameTileManager* pGameTileManager = new GameTileManager(20, 20);
		PlayerObject* pPlayerObject = new PlayerObject(this->getPGameEngine(), pGameTileManager, playerNameString);
		std::vector<EnemyObject*> enemyObjects;
		std::vector<Fire*> fireObjects;
		getPGameEngine()->pSSP.switchState(new RunLevelOneState(this->getPGameEngine(), pPlayerObject, pGameTileManager, enemyObjects, fireObjects, false));
	}
}