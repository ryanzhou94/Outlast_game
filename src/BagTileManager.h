#pragma once
#include "header.h"
#include "TileManager.h"
#include "SimpleImage.h"

class BagController;

class GameEngine;

class BagTileManager :
	public TileManager
{
public:
	BagTileManager(BagController* pBagController);
	~BagTileManager();

	void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;

	void updateValues();

	void setAndRedrawMapValueAtIndex(int index, int iValue, BaseEngine* pEngine, DrawingSurface* pSurface);

	void drawSpace(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawKey(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawHP(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawMP(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;

public:
	BagController* pBagController;

	SimpleImage space;	// 0
	SimpleImage key;	// 1
	SimpleImage hp;		// 2
	SimpleImage mp;		// 3
	
};

