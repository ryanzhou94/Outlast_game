#pragma once
#include "header.h"
#include "EnemyMovingController.h"

class GameEngine;

class EnemyTypeOneMovingController :
	public EnemyMovingController
{
public:
	EnemyTypeOneMovingController(MovingObject* pMovingObject, MovingObject* pPlayerObject);
	~EnemyTypeOneMovingController();

	void handleMovement(int iCurrentTime) override;
	void anticlockwiseMovement(int iCurrentTime);
};

