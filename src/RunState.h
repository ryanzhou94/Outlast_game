#pragma once
#include "header.h"
#include <fstream>
#include <iostream>
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
#include "DrawingFilters.h" 

class GameEngine;

class RunState :
	public GameState
{
public:
	RunState(GameEngine* pGameEngine, PlayerObject* pPlayerObject, GameTileManager* pGameTileManager, std::vector<EnemyObject*> pEnemyObjects, std::vector<Fire*> pFire, bool isLoad = false);
	~RunState();
	void drawBagBorders();
	void drawHPBox();
	void drawMPBox();
	void drawSaveButton();
	void pauseGame();
	void saveGame();
	void saveMap(std::ofstream* file);
	void savePlayerData(std::ofstream* file);
	void saveEnemyData(std::ofstream* file, EnemyObject* pEnemyObject);
	void saveFireData(std::ofstream* file, Fire* pFire);
	void addObjects();
	//int virtInitialise() override;
	void virtRealMouseDown(int iButton, int iX, int iY) override;
	void virtKeyDown(int iKeyCode) override;
	void virtMouseDown(int iButton, int iX, int iY) override;
	void getCurrentTime(char* currentTime);
	void virtMouseWheel(int x, int y, int which, int timestamp) override;
	void virtMouseUp(int iButton, int iX, int iY) override;
	void virtMouseMoved(int iX, int iY) override;
	void virtBackgroundMouseDown(int iButton, int iRealX, int iRealY, int iVirtualX, int iVirtualY) override;

	void virtPostDraw() override;

	void zoomOut();

	void zoomIn();

public:
	PlayerObject* pPlayerObject;
	GameTileManager* pGameTileManager;
	std::vector<EnemyObject*> enemyObjects;
	std::vector<Fire*> fireObjects;
	SimpleImage saveButton;
	int saveTimer = 0;
	bool isSaving = false;
	bool isLoad;
	bool m_bDragging;
	int m_iClickedX;
	int m_iClickedY;

	FilterPointsScaling m_filterScaling;
	FilterPointsTranslation m_filterTranslation;
};

