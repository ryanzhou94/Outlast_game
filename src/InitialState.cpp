#include "InitialState.h"
#include "GameEngine.h"

InitialState::InitialState(GameEngine* pGameEngine)
	: GameState(pGameEngine)
	, background(this->getPGameEngine()->loadImage("images/Initial_Background.jpg", false/*don't keep it loaded*/))
	, button(this->getPGameEngine()->loadImage("images/button.png", false/*don't keep it loaded*/))
{
	button = button.resizeTo(190, 80);
}

InitialState::~InitialState()
{
}

void InitialState::virtSetupBackgroundBuffer()
{
	this->getPGameEngine()->redrawDisplay();

	std::cout << "Initial state..." << std::endl;

	// Background
	background.renderImageBlit(this->getPGameEngine(),
		this->getPGameEngine()->getBackgroundSurface(),
		0, 0,
		this->getPGameEngine()->getWindowWidth(), this->getPGameEngine()->getWindowHeight(),
		0, 0,
		background.getWidth(), background.getHeight());

	// Buttons:
	// start button
	button.renderImageWithMask(getPGameEngine()->getBackgroundSurface(), 0, 0, this->getPGameEngine()->getWindowWidth() / 2 - 100, this->getPGameEngine()->getWindowHeight() / 3, button.getWidth(), button.getHeight());	//button.renderImage(	this->getPGameEngine()->getBackgroundSurface(),

	button.renderImageWithMask(getPGameEngine()->getBackgroundSurface(), 0, 0, this->getPGameEngine()->getWindowWidth() / 2 - 100, this->getPGameEngine()->getWindowHeight() / 3 + 150, button.getWidth(), button.getHeight());

	button.renderImageWithMask(getPGameEngine()->getBackgroundSurface(), 0, 0, this->getPGameEngine()->getWindowWidth() / 2 - 100, this->getPGameEngine()->getWindowHeight() / 3 + 300, button.getWidth(), button.getHeight());
}

void InitialState::virtDrawStringsOnTop()
{
	// Game Name
	this->getPGameEngine()->drawForegroundString(	this->getPGameEngine()->getWindowWidth()/2 -205, this->getPGameEngine()->getWindowHeight() / 6,
													"Outlast", 0xFFFFFF, 
													this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 80));
	// Button Label:
	// Start Button Label
	this->getPGameEngine()->drawForegroundString(	this->getPGameEngine()->getWindowWidth() / 2 - 75, this->getPGameEngine()->getWindowHeight() / 3+15,
													"Start", 0xFFFFFF,
													this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 40));
	// Archive Button Label
	this->getPGameEngine()->drawForegroundString(	this->getPGameEngine()->getWindowWidth() / 2 - 58, this->getPGameEngine()->getWindowHeight() / 3 + 165,
													"Load", 0xFFFFFF,
													this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 40));
	// Introduction Button Label
	this->getPGameEngine()->drawForegroundString(	this->getPGameEngine()->getWindowWidth() / 2 - 65, this->getPGameEngine()->getWindowHeight() / 3 + 315,
													"Intro", 0xFFFFFF,
													this->getPGameEngine()->getFont("Cornerstone Regular.ttf", 42));
}

void InitialState::virtMouseDown(int iButton, int X, int Y)
{
	// Start Game Button
	if (X >= this->getPGameEngine()->getWindowWidth() / 2 - 100
		&& X <= getPGameEngine()->getWindowWidth() / 2 - 100 + button.getWidth()
		&& Y >= this->getPGameEngine()->getWindowHeight() / 3
		&& Y <= this->getPGameEngine()->getWindowHeight() / 3 + button.getHeight())
	{
		getPGameEngine()->pSSP.switchState(new EnterNameState(getPGameEngine()));
		return;
	}

	// Introduction Button
	if (X >= this->getPGameEngine()->getWindowWidth() / 2 - 100 
		&& X <= getPGameEngine()->getWindowWidth() / 2 - 100 + button.getWidth()
		&& Y >= this->getPGameEngine()->getWindowHeight() / 3 + 300 
		&& Y <= this->getPGameEngine()->getWindowHeight() / 3 + 300 + button.getHeight())
	{
		getPGameEngine()->pSSP.switchState(new IntroState(this->getPGameEngine()));
		return;
	}
	// Archive Button
	if (X >= this->getPGameEngine()->getWindowWidth() / 2 - 100
		&& X <= getPGameEngine()->getWindowWidth() / 2 - 100 + button.getWidth()
		&& Y >= this->getPGameEngine()->getWindowHeight() / 3 + 150
		&& Y <= this->getPGameEngine()->getWindowHeight() / 3 + + 150 + button.getHeight())
	{
		getPGameEngine()->pSSP.switchState(new ArchiveState(this->getPGameEngine()));
		return;
	}
}