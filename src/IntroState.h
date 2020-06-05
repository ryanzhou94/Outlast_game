#pragma once
#include "header.h"
#include "GameState.h"
#include "SimpleImage.h"
//#include "AudioManager.h"
//#include "AssetManager.h"

class GameEngine;

class IntroState :
	public GameState
{
public:
	IntroState(GameEngine* pGameEngine);
	~IntroState();

	void virtSetupBackgroundBuffer() override;
	void virtDrawStringsOnTop() override;
	void virtMouseDown(int iButton, int X, int Y) override;

private:
	SimpleImage background;
	SimpleImage button;
	//AudioManager* mAudiomgr;
};

