#pragma once
#include "header.h"
#include "MovingController.h"
#include "MovementPosition.h"
#include "GameTileManager.h"
#include "Fire.h"

class GameEngine;

class PlayerMovingController :
	public MovingController
{
public:
	PlayerMovingController(MovingObject* pMovingObject);
	~PlayerMovingController();

	void fire(int iCurrentTime);

	void handleMovement(int iCurrentTime) override;

	void loadFireImages();

	void selfHealHP(int iCurrentTime);

	void selfHealMP(int iCurrentTime);
	
	void playWalk(int iCurrentTime);
	void playRun(int iCurrentTime);
	void playAttack(int iCurrentTime);
	void stopPlay();

public:

	int trapTimer = 0;
	int trapCoolingTime = 1100;

	int fireTimer = 0;
	int fireCoolingTime = 1000;

	int healHPTimer = 0;
	int healHPValue = 1;
	int healHPCoolingTime = 4000;

	int healMPTimer = 0;
	int healMPValue = 1;
	int healMPCoolingTime = 500;

	SimpleImage fireLeft[7];
	SimpleImage fireRight[7];
	SimpleImage fireUp[7];
	SimpleImage fireDown[7];

	bool isRunning = false;
	bool isWalkPlaying = false;
	bool isAttackPlaying = false;
	bool isRunningPlaying = false;
	int walkPlayTimer = 0;
	int attackPlayTimer = 0;
	int runPlayTimer = 0;
	int walkPlayInterval = 800;
	int attackPlayInterval = 500;
	int runPlayInterval = 500;
};

