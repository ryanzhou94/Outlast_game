#pragma once
#include "header.h"
#include "MovingObject.h"
#include "SimpleImage.h"
#include "MovingController.h"
#include "FireMovingController.h"

class GameEngine;

class Fire :
	public MovingObject
{
public:
	Fire(GameEngine* pGameEngine, GameTileManager* pGameTileManager, int xStart, int yStart, int toward, int totalDistance = 0);
	~Fire();

	void virtDraw() override;

	void virtDoUpdate(int iCurrentTime) override;

	void virtInitializeUncrossable() override;




};

