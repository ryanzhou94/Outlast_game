#pragma once
#include "header.h"
#include "EnemyObject.h"
#include "SimpleImage.h"
#include "MovingController.h"

class GameEngine;

class EnemyTypeFive :
	public EnemyObject
{
public:
	EnemyTypeFive(GameEngine* pGameEngine, GameTileManager* pGameTileManager, int xStart, int yStart, MovingObject* pPlayerObject);
	~EnemyTypeFive();

};

