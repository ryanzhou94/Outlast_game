#pragma once
#include "header.h"
#include "EnemyObject.h"
#include "SimpleImage.h"
#include "MovingController.h"

class GameEngine;

class EnemyTypeThree :
	public EnemyObject
{
public:
	EnemyTypeThree(GameEngine* pGameEngine, GameTileManager* pGameTileManager, int xStart, int yStart, MovingObject* pPlayerObject);
	~EnemyTypeThree();
};

