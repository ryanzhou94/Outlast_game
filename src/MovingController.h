#pragma once
#include "header.h"
#include "SimpleImage.h"
#include "MovementPosition.h"

class GameEngine;

class MovingObject;

class MovingController
{
public:
	MovingController(MovingObject* pMovingObject, int totalDistance = 0);
	~MovingController();

	virtual void handleMovement(int iCurrentTime) = 0;

	virtual void drawMovingImages();

	virtual void attack(int iCurrentTime);
	virtual void stopAttack();
	virtual bool isPositionValid(int distance);
	virtual MovingObject* getObjectCollided();
	virtual void setUnderAttack();
	virtual void underAttack(int iCurrentTime);

	virtual void underFire(int iCurrentTime);

	virtual void loadMovingImages();

public:
	MovingObject* pMovingObject;
	int totalDistance = 0;


	/* Movement */
	// The direction the player is facing to: 0.Down 1.Up 2.Down 3.Left 4.Right
	int toward = 0;
	bool isMoving = false;
	// Moving Images
	SimpleImage walkingLeft[7];
	SimpleImage walkingRight[7];
	SimpleImage walkingUp[7];
	SimpleImage walkingDown[7];

	// Moving Distance (Changable)
	int walkingDistance = 1;
	int runningDistance = 3;

	// Image Switching period (Changable)
	int walkingInterval = 200;
	int runningInterval = 100;

	// Moving Timer
	int walkingLeftTimer = 0;
	int walkingRightTimer = 0;
	int walkingUpTimer = 0;
	int walkingDownTimer = 0;

	// Moving Images Index
	int walkingLeftImageIndex = 0;
	int walkingRightImageIndex = 0;
	int walkingUpImageIndex = 0;
	int walkingDownImageIndex = 0;
	/* end of Movement */



	/* Attack */
	int attackDamage = 20;
	bool isAttacking = false;
	int attackStatus = 0;	// 0.no attack	1.attack forward	2.attack backward
	int backwardDistance = 30;
	int attackDistance = 30;
	int attackTimer = 0;
	int attackBackInterval = 40;
	int attackForwardInterval = 40;
	int coolingTime = 400;
	MovementPosition movementPosition;
	/* end of Attack */



	/* under attack */
	bool isUnderAttack = false;
	int underAttackStatus = 0;
	int underAttackMissingInterval = 80;
	int underAttackShowingInterval = 120;
	int underAttackTimer = 0;
	int underAttackCoolingTime = 400;
	/* under attack */


	/* under fire */
	bool isUnderFire = false;
	SimpleImage explode[5];
	int underFireCoolingTime = 1000;
	int underFireImageInterval = 100;
	int underFireTimer = 0;
	int underFireImageIndex = 0;
	/* under fire */

	bool isUnderFirePlaying = false;
};

