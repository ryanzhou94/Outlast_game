#pragma once
#include "header.h"
#include "MovingController.h"
#include "PlayerObject.h"

class GameEngine;

class EnemyMovingController :
	public MovingController
{
public:
	EnemyMovingController(MovingObject* pMovingObject, MovingObject* pPlayerObject);
	~EnemyMovingController();

	bool isPlayerVisiable();
	double getDistance();
	int getChasingPlayerDirection(int iCurrentTime);
	void chasePlayer(int iCurrentTime);
	bool isPlayerAttackable();
	bool checkEnemyStop(int iCurrentTime);
	void setRealToward();
	bool isUpLeftMovable();
	bool isUpRightMovable();
	bool isDownLeftMovable();
	bool isDownRightMovable();
	bool isLeftUpMovable();
	bool isLeftDownMovable();
	bool isRightUpMovable();
	bool isRightDownMovable();

	void handleMovement(int iCurrentTime) override;
	void anticlockwiseMovement(int iCurrentTime);

public:
	MovingObject* pPlayerObject;
	bool isStop = false;
	bool isSearching = false;
	bool isChecking = true;
	int searchTimer = 0;
	int searchInterval = 2000;
	int stopTimer = 0;
	int stopInterval = 150;
	int updateTimer = 0;
	int lastX;
	int lastY;

	int realToward = 1;
};

