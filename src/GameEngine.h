#pragma once
#include "BaseEngine.h"
#include "GameState.h"
#include "InitialState.h"
#include "IntroState.h"
#include "ArchiveState.h"
#include "EnterNameState.h"
#include "RunState.h"
#include "RunLevelOneState.h"
#include "RunLevelTwoState.h"
#include "PauseState.h"
#include <ctime> 
#include "State_SmartPointer.h"
#include "AudioManager.h"


class GameEngine :
	public BaseEngine
{
public:
	GameEngine();
	~GameEngine();
	void virtSetupBackgroundBuffer() override;
	void virtDrawStringsOnTop() override;
	int virtInitialiseObjects() override;
	void virtRealMouseDown(int iButton, int iX, int iY) override;
	void virtMouseDown(int iButton, int iX, int iY) override;
	void virtKeyDown(int iKeyCode) override;
	void virtPostDraw() override;
	void virtBackgroundMouseDown(int iButton, int iRealX, int iRealY, int iVirtualX, int iVirtualY) override;
	void virtMouseMoved(int iX, int iY) override;
	void virtMouseUp(int iButton, int iX, int iY) override;
	void virtMouseWheel(int x, int y, int which, int timestamp) override;

public:
	State_SmartPointer pSSP;

	GameState* pGameState = nullptr;
	GameState* pPauseState = nullptr;

	AudioManager* pAudioManager;

};

