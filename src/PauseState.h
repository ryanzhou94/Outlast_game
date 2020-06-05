#pragma once
#include "header.h"
#include "RunState.h"

class GameEngine;

class PauseState :
	public RunState
{
public:
	PauseState(GameEngine* pGameEngine, PlayerObject* pPlayerObject, GameTileManager* pGameTileManager, std::vector<EnemyObject*> pEnemyObjects, std::vector<Fire*> pFire);
	~PauseState();

	void virtSetupBackgroundBuffer() override;
	void virtDrawStringsOnTop() override;
	void virtKeyDown(int iKeyCode) override;
};

