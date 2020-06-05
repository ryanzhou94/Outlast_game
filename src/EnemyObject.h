#pragma once
#include "header.h"
#include "MovingObject.h"
#include "EnemyTypeOneMovingController.h"
#include "EnemyTypeTwoMovingController.h"

class GameEngine;

class EnemyObject :
	public MovingObject
{
public:
	EnemyObject(GameEngine* pGameEngine, GameTileManager* pGameTileManager, int xStart, int yStart, MovingObject* pPlayerObject);
	~EnemyObject();

	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;

	void virtInitializeUncrossable() override;
	void virtInitializeAttackable() override;

public:
	MovingObject* pPlayerObject;
};

