#pragma once
#include "header.h"
#include "EnemyObject.h"
#include "SimpleImage.h"
#include "MovingController.h"

class GameEngine;

class EnemyTypeFour :
	public EnemyObject
{
public:
	EnemyTypeFour(GameEngine* pGameEngine, GameTileManager* pGameTileManager, int xStart, int yStart, MovingObject* pPlayerObject);
	~EnemyTypeFour();

};

