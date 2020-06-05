#pragma once
#include "header.h"
#include "GameState.h"
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

class GameEngine;

class LevelOneState :
	public GameState
{
public:
	LevelOneState(GameEngine* pGameEngine, std::string name);
	~LevelOneState();

	void virtSetupBackgroundBuffer() override;
	void virtInitialiseObjects() override;
	void virtDrawStringsOnTop() override;
	void drawBagBorders();


public:
	PlayerObject* pPlayerObject;
	GameTileManager gameTileManager;
};

