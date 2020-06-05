#include "header.h"
#include "GameEngine.h"

GameEngine::GameEngine()
	: pSSP(new InitialState(this))
	, pAudioManager(AudioManager::Instance())
{
	srand((unsigned int)time(NULL));
	pAudioManager->PlaySFX("background.wav");
}

GameEngine::~GameEngine()
{
	AudioManager::Release();
	destroyOldObjects(true);

}

void GameEngine::virtSetupBackgroundBuffer()
{
	pSSP->virtSetupBackgroundBuffer();
}

void GameEngine::virtDrawStringsOnTop()
{
	pSSP->virtDrawStringsOnTop();
}

int GameEngine::virtInitialiseObjects()
{
	pSSP->virtInitialiseObjects();
	return 0;
}

void GameEngine::virtRealMouseDown(int iButton, int iX, int iY)
{
	pSSP->virtRealMouseDown(iButton, iX, iY);
}

void GameEngine::virtMouseDown(int iButton, int iX, int iY)
{
	pSSP->virtMouseDown(iButton, iX, iY);
}

void GameEngine::virtKeyDown(int iKeyCode)
{
	pSSP->virtKeyDown(iKeyCode);
}

void GameEngine::virtPostDraw()
{
	pSSP->virtPostDraw();
}

void GameEngine::virtBackgroundMouseDown(int iButton, int iRealX, int iRealY, int iVirtualX, int iVirtualY)
{
	pSSP->virtBackgroundMouseDown(iButton, iRealX, iRealY, iVirtualX, iVirtualY);
}

void GameEngine::virtMouseMoved(int iX, int iY)
{
	pSSP->virtMouseMoved(iX, iY);
}

void GameEngine::virtMouseUp(int iButton, int iX, int iY)
{
	pSSP->virtMouseUp(iButton, iX, iY);
}

void GameEngine::virtMouseWheel(int x, int y, int which, int timestamp)
{
	pSSP->virtMouseWheel(x, y, which, timestamp);
}
