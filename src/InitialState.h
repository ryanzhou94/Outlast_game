#pragma once
#include "header.h"
#include "GameState.h"
#include "SimpleImage.h"
#include <ctime>

class GameEngine;

class InitialState :
	public GameState
{
public:
	InitialState(GameEngine* pGameEngine);
	~InitialState();

	void virtSetupBackgroundBuffer() override;
	void virtDrawStringsOnTop() override;
	void virtMouseDown(int iButton, int X, int Y) override;

private:
	SimpleImage background;
	SimpleImage button;
};

