#include "IntroState.h"
#include "GameEngine.h"

IntroState::IntroState(GameEngine* pGameEngine)
	: GameState(pGameEngine)
	, background(this->getPGameEngine()->loadImage("images/Intro_Background.jpg", false/*don't keep it loaded*/))
	, button(this->getPGameEngine()->loadImage("images/button.png", false/*don't keep it loaded*/))
{
	//mAudiomgr = AudioManager::Instance();
}

IntroState::~IntroState()
{
	//AudioManager::Release();
}

void IntroState::virtSetupBackgroundBuffer()
{
	this->getPGameEngine()->redrawDisplay();

	std::cout << "Introduction state..." << std::endl;

	// Background
	background.renderImageBlit(this->getPGameEngine(),
		this->getPGameEngine()->getBackgroundSurface(),
		0, 0,
		this->getPGameEngine()->getWindowWidth(), this->getPGameEngine()->getWindowHeight(),
		0, 0,
		background.getWidth(), background.getHeight());

	// Return Button
	button.renderImage(this->getPGameEngine()->getBackgroundSurface(),
		0, 0,
		545, 650,
		button.getWidth(), button.getHeight());
}

void IntroState::virtDrawStringsOnTop()
{
	// Title
	this->getPGameEngine()->drawForegroundString(350, 100,
		"How to play", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 80));

	this->getPGameEngine()->drawForegroundString(250, 250,
		"Press direction keys to walk", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 30));
	this->getPGameEngine()->drawForegroundString(250, 330,
		"Press 'A' to attack", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 30));
	this->getPGameEngine()->drawForegroundString(250, 400,
		"Press 'D' to shoot fireball", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 30));
	this->getPGameEngine()->drawForegroundString(250, 480,
		"Press 'space' to run while walking", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 30));
	this->getPGameEngine()->drawForegroundString(250, 560,
		"Press 'p' to pause the game", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 30));

	// Button Label:
	// Return Button Label
	this->getPGameEngine()->drawForegroundString(560,663,
		"Return", 0xFFFFFF,
		this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 40));
}

void IntroState::virtMouseDown(int iButton, int X, int Y)
{
	if (X >= 545
		&& X <= 545 + button.getWidth()
		&& Y >= 650
		&& Y <= 650 + button.getHeight())
	{
		//if (this->getPGameEngine()->initialState == nullptr)
		//{
		//	this->getPGameEngine()->initialState = new InitialState(this->getPGameEngine());
		//}
		//this->getPGameEngine()->pGameState = this->getPGameEngine()->initialState;
		//getPGameEngine()->lockAndSetupBackground();
		getPGameEngine()->pSSP.switchState(new InitialState(getPGameEngine()));
		//mAudiomgr->PlayMusic("openDoor.wav");
	}
}
