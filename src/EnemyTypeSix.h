#pragma once
#include "header.h"
#include "EnemyObject.h"
#include "SimpleImage.h"
#include "MovingController.h"

class GameEngine;

class EnemyTypeSix :
	public EnemyObject
{
public:
	EnemyTypeSix(GameEngine* pGameEngine, GameTileManager* pGameTileManager, int xStart, int yStart, MovingObject* pPlayerObject);
	~EnemyTypeSix();
};

