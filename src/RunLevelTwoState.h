#pragma once
#include "header.h"
#include "RunState.h"

class GameEngine;

class RunLevelTwoState :
	public RunState
{
public:
	RunLevelTwoState(GameEngine* pGameEngine, PlayerObject* pPlayerObject, GameTileManager* pGameTileManager, std::vector<EnemyObject*> pEnemyObjects, std::vector<Fire*> pFire, bool isLoad);
	~RunLevelTwoState();

	void virtSetupBackgroundBuffer() override;
	void virtInitialiseObjects() override;
	void virtDrawStringsOnTop() override;

};

