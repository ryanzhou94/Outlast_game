#pragma once
#include "header.h"
#include "GameObject.h"
#include "PlayerObject.h"

class GameEngine;

class PropsObject :
	public GameObject
{
public:
	PropsObject(GameEngine* pGameEngine, int xStart, int yStart, PlayerObject* pPlayerObject);
	~PropsObject();

	bool isPlayerCollided();
	

public:
	PlayerObject* pPlayerObject;
};

