#pragma once
#include "header.h"
#include "MovingObject.h"
#include "SimpleImage.h"
#include "MovingController.h"
#include "PlayerMovingController.h"
#include "BagController.h"

class GameEngine;

class PlayerObject :
	public MovingObject
{
public:
	PlayerObject(GameEngine* pGameEngine, GameTileManager* pGameTileManager, std::string name, int xStart = 0, int yStart = 0, int HP = 100, int MP = 1500, int toward = 2, int isUnderAttack = false, std::string theBag = "000000");
	~PlayerObject();

	void virtDraw() override;

	void virtDoUpdate(int iCurrentTime) override;

	void virtInitializeUncrossable() override;
	void virtInitializeAttackable() override;
	bool isNextLevel();
	bool isDead();
	void printDie();

	void updateBag();
	void drawHP();
	void drawMP();

public:
	BagController* pBagController;

	std::string name;

	bool isSuccessful = false;
	bool isDiePlaying = false;
	bool isWinPlaying = false;
};

