#pragma once
#include "header.h"
#include "GameState.h"
#include "SimpleImage.h"
#include <vector>
#include <ctime>

class GameEngine;

class EnterNameState :
	public GameState
{
public:
	EnterNameState(GameEngine* pGameEngine);
	~EnterNameState();

	void virtSetupBackgroundBuffer() override;
	void virtDrawStringsOnTop() override;
	void virtKeyDown(int iKeyCode) override;
	void virtMouseDown(int iButton, int iX, int iY) override;

private:
	SimpleImage background;
	SimpleImage button;
	std::vector<char> playerName;
};

