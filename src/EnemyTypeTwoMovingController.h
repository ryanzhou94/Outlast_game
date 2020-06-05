#pragma once
#include "header.h"
#include "EnemyMovingController.h"

class GameEngine;

class EnemyTypeTwoMovingController :
	public EnemyMovingController
{
public:
	EnemyTypeTwoMovingController(MovingObject* pMovingObject, MovingObject* pPlayerObject);
	~EnemyTypeTwoMovingController();

	void handleMovement(int iCurrentTime) override;

	void staticMovement(int iCurrentTime);

private:
	int watchTimer = 0;
	int watchInterval = 1500;
};

