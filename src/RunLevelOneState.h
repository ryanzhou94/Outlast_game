#pragma once
#include "header.h"
#include "RunState.h"

class GameEngine;

class RunLevelOneState :
	public RunState
{
public:
	RunLevelOneState(GameEngine* pGameEngine, PlayerObject* pPlayerObject, GameTileManager* pGameTileManager, std::vector<EnemyObject*> pEnemyObjects, std::vector<Fire*> pFire, bool isLoad);
	~RunLevelOneState();

	void virtSetupBackgroundBuffer() override;
	void virtInitialiseObjects() override;
	void virtDrawStringsOnTop() override;

};

