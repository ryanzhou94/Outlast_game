#pragma once
#include "header.h"
#include "EnemyObject.h"
#include "SimpleImage.h"
#include "MovingController.h"

class GameEngine;

class EnemyTypeTwo :
	public EnemyObject
{
public:
	EnemyTypeTwo(GameEngine* pGameEngine, GameTileManager* pGameTileManager, int xStart, int yStart, MovingObject* pPlayerObject);
	~EnemyTypeTwo();
};

