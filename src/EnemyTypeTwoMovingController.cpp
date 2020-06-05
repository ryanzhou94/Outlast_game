#include "EnemyTypeTwoMovingController.h"

EnemyTypeTwoMovingController::EnemyTypeTwoMovingController(MovingObject* pMovingObject, MovingObject* pPlayerObject)
	: EnemyMovingController(pMovingObject, pPlayerObject)
{
	toward = rand() % 4 + 1;
	coolingTime = 600;
}

EnemyTypeTwoMovingController::~EnemyTypeTwoMovingController()
{
}

void EnemyTypeTwoMovingController::handleMovement(int iCurrentTime)
{
	if (!isAttacking)
	{
		if (isPlayerVisiable())
		{
			chasePlayer(iCurrentTime);
		}
		else
		{
			staticMovement(iCurrentTime);
		}
	}

	if (isPlayerAttackable() && (iCurrentTime - attackTimer >= coolingTime) || isAttacking)
	{
		attack(iCurrentTime);
	}

	if (isUnderAttack && (iCurrentTime - underAttackTimer >= underAttackCoolingTime))
	{
		underAttack(iCurrentTime);
	}

	if (isUnderFire)
	{
		underFire(iCurrentTime);
	}
}

void EnemyTypeTwoMovingController::staticMovement(int iCurrentTime)
{
	if (iCurrentTime - watchTimer >= watchInterval)
	{
		switch (toward)
		{
		case 1:
			toward = 4;
			break;
		case 2:
			toward = 3;
			break;
		case 3:
			toward = 1;
			break;
		case 4:
			toward = 2;
			break;
		default:
			break;
		}
		watchTimer = iCurrentTime;
	}
}
