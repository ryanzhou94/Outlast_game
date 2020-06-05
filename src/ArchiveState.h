#pragma once
#include "header.h"
#include "GameState.h"
#include "SimpleImage.h"
#include "GameTileManager.h"
#include "GameTileManager.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "EnemyTypeOne.h"
#include "EnemyTypeTwo.h"
#include "EnemyTypeThree.h"
#include "EnemyTypeFour.h"
#include "EnemyTypeFive.h"
#include "EnemyTypeSix.h"
#include "Fire.h"
#include <fstream>
#include <iostream>

class GameEngine;

class ArchiveState :
	public GameState
{
public:
	ArchiveState(GameEngine* pGameEngine);
	~ArchiveState();

	void virtSetupBackgroundBuffer() override;
	void virtDrawStringsOnTop() override;
	//void virtInitialiseObjects() override;
	void virtMouseDown(int iButton, int X, int Y) override;

	void loadGame(std::ifstream* file, GameTileManager** pGameTileManager, PlayerObject** pPlayerObject, std::vector<EnemyObject*>* pEnemyObjects, std::vector<Fire*>* pFire);
	void loadMap(std::ifstream* file, GameTileManager** pGameTileManager);
	void loadPlayer(std::ifstream* file, PlayerObject** pPlayerObject, GameTileManager* pGameTileManager);
	void loadEnemy(std::ifstream* file, std::vector<EnemyObject*>* pEnemyObjects, GameTileManager* pGameTileManager, MovingObject* pPlayerObject);
	void loadFire(std::ifstream* file, std::vector<Fire*>* pFire, GameTileManager* pGameTileManager);

private:
	SimpleImage background;
	SimpleImage button;
	SimpleImage bar;
};

