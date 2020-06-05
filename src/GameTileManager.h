#pragma once
#include "TileManager.h"
#include "SimpleImage.h"
#include "ImageManager.h"
#include "LevelController.h"
#include "AudioManager.h"

class MovingObject;

class GameTileManager :
	public TileManager
{
public:
	GameTileManager(int topLeftX = 20, int topLeftY = 20, bool isLoad = false);
	~GameTileManager();

	void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;

	void updateMapValues();

	bool is_tile_crossable(std::vector<int> uncrossable, int tileValueTopLeft, int tileValueTopRight, int tileValueBottomLeft, int tileValueBottomRight);

	bool isOneTileCrossable(MovingObject* pMovingObject, int mapX, int mapY);

	bool validateTile(MovingObject* movingObject, int toward, int distance);
	bool validateWall(MovingObject* movingObject);
	bool validateAttackTile(MovingObject* movingObject, int toward, int distance);

	int validateHP(MovingObject* movingObject, BaseEngine* pEngine, DrawingSurface* pSurface);

	int validateMP(MovingObject* movingObject, BaseEngine* pEngine, DrawingSurface* pSurface);

	int validateKey(MovingObject* movingObject, BaseEngine* pEngine, DrawingSurface* pSurface);

	bool validateTrap(MovingObject* movingObject);

	void tryBreakBucket(MovingObject* pMovingObject, BaseEngine* pEngine, DrawingSurface* pSurface);

	bool isTileWall(int mapX, int mapY);
	bool isTileHP(int mapX, int mapY);
	bool isTileMP(int mapX, int mapY);
	bool isTileKey(int mapX, int mapY);
	bool isTileBucket(int mapX, int mapY);
	bool isTileTrap(int mapX, int mapY);

	void openLockedDoor(MovingObject* pMovingObject, BaseEngine* pEngine, DrawingSurface* pSurface);
	bool isPlayerAroundDoor(MovingObject* pMovingObject);
	bool isPlayerAroundFountain(MovingObject* pMovingObject);
	void getFinalArea(int* topY, int* bottomY, int* leftX, int* rightX);
	bool isPositionCrossable(std::vector<int> uncrossable, int XPosition, int YPosition);
	void setBornPlace(int* XPosition, int* YPosition);

	void drawWall(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawFloor(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawUnlockedDoor(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawLockedDoor(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawTrap(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawFountain(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawBucket(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawKey(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawHP(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawMP(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawNoOpenedDoor(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;
	void drawBucketBroken(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const;

public:
	LevelController levelController;

	SimpleImage wall;			// 1
	SimpleImage floor;			// 2
	SimpleImage unlockedDoor;	// 3
	SimpleImage lockedDoor;		// 4
	SimpleImage trap;			// 5
	SimpleImage fountain;		// 6
	SimpleImage bucket;			// 7
	SimpleImage key;			// 8
	SimpleImage hp;				// 9
	SimpleImage mp;				// 0
	SimpleImage noOpenedDoor;	// a (10)
	SimpleImage bucketBroken;	// b (11)
};

