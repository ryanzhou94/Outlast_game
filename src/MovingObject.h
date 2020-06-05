#pragma once
#include "header.h"
#include "GameObject.h"
#include "MovingController.h"
#include "GameTileManager.h"

class GameEngine;

class MovingObject :
	public GameObject
{
public:
	MovingObject(GameEngine* pGameEngine, GameTileManager* pGameTileManager, int xStart, int yStart);
	~MovingObject();

	void moveCurrentScreenX(int diffX) { m_iCurrentScreenX += diffX; }
	void moveCurrentScreenY(int diffY) { m_iCurrentScreenY += diffY; }
	void setCurrenrtScreenPosition(int XPosition, int YPosition) { m_iCurrentScreenX = XPosition, m_iCurrentScreenY = YPosition; }

	void setDrawWidth(int newDrawWidth) { m_iDrawWidth = newDrawWidth; }
	void setDrawHeight(int newDrawHeight) { m_iDrawHeight = newDrawHeight; }
	int getDrawWidth() { return this->m_iDrawWidth; }
	int getDrawHeight() { return this->m_iDrawHeight; }

	void loadMovingImages();

	virtual void virtInitializeUncrossable() = 0;
	virtual void virtInitializeAttackable() {};

public:
	MovingController* pMovingController;
	GameTileManager* pGameTileManager;
	std::vector<int> uncrossable;
	std::vector<int> unattackble;


	int maxHP = 100;
	int maxMP = 1500;
	int HP = maxHP;
	int MP = maxMP;
};

