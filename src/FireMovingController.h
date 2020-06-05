#pragma once
#include "header.h"
#include "MovingController.h"
#include "MovementPosition.h"
#include "GameTileManager.h"

class GameEngine;

class FireMovingController :
	public MovingController
{
public:
	FireMovingController(MovingObject* pMovingObject, int distance);
	~FireMovingController();
	void disapper();
	void loadImage();
	void handleMovement(int iCurrentTime) override;
	void setUnderFire();
	void fly(int iCurrentTime);
	void loadFireImages();

public:
	int flyingDistance = 200;
	//int totalDistance = 0;
	int fireDamage = 50;
	int flyingSpeed = 3;
	int flyInterval = 80;
};

