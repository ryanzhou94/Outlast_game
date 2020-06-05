#include "header.h"
#include "GameTileManager.h"
#include "MovingObject.h"

GameTileManager::GameTileManager(int topLeftX, int topLeftY, bool isLoad)
	: TileManager(50, 50, 20, 15)
	, wall(ImageManager::get()->getImagebyURL("images/wall.png", true, true))
	, floor(ImageManager::get()->getImagebyURL("images/floor.png", true, true))
	, unlockedDoor(ImageManager::get()->getImagebyURL("images/unlockedDoor.png", true, true))
	, lockedDoor(ImageManager::get()->getImagebyURL("images/lockedDoor.png", true, true))
	, trap(ImageManager::get()->getImagebyURL("images/trap.png", true, true))
	, fountain(ImageManager::get()->getImagebyURL("images/fountain.png", true, true))
	, bucket(ImageManager::get()->getImagebyURL("images/bucket.png", true, true))
	, key(ImageManager::get()->getImagebyURL("images/key.png", true, true))
	, hp(ImageManager::get()->getImagebyURL("images/hp.png", true, true))
	, mp(ImageManager::get()->getImagebyURL("images/mp.png", true, true))
	, noOpenedDoor(ImageManager::get()->getImagebyURL("images/noOpenedDoor.png", true, true))
	, bucketBroken(ImageManager::get()->getImagebyURL("images/bucket_broken.png", true, true))
{
	setTopLeftPositionOnScreen(topLeftX, topLeftY);
	wall = wall.resizeTo(getTileWidth(), getTileHeight());
	floor = floor.resizeTo(getTileWidth(), getTileHeight());
	unlockedDoor = unlockedDoor.resizeTo(getTileWidth(), getTileHeight());
	lockedDoor = lockedDoor.resizeTo(getTileWidth(), getTileHeight());
	trap = trap.resizeTo(getTileWidth(), getTileHeight());
	fountain = fountain.resizeTo(getTileWidth(), getTileHeight());
	bucket = bucket.resizeTo(getTileWidth() , getTileHeight());
	key = key.resizeTo(getTileWidth()-15, getTileHeight()-15);
	hp = hp.resizeTo(getTileWidth() - 10, getTileHeight() - 10);
	mp = mp.resizeTo(getTileWidth() - 10, getTileHeight() - 10);
	noOpenedDoor = noOpenedDoor.resizeTo(getTileWidth(), getTileHeight());
	bucketBroken = bucketBroken.resizeTo(getTileWidth(), getTileHeight() -12);

	if (isLoad == false)
	{
		updateMapValues();	// 1 -> level 1
	}
}

GameTileManager::~GameTileManager()
{
}

void GameTileManager::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
{
	// swtich 'tile value'
	// 1. wall
	// 2. floor
	// 3. unlocked door
	// 4. locked door
	// 5. trap
	// 6. fountain
	// 7. bucket
	// 8. key
	// 9. hp
	// 10. mp

	drawFloor(pEngine, pSurface, iMapX, iMapY);

	switch (getMapValue(iMapX, iMapY)) {
		case 1:
			drawWall(pEngine, pSurface, iMapX, iMapY);
			break;
		case 2:
			drawFloor(pEngine, pSurface, iMapX, iMapY);
			break;
		case 3:
			drawUnlockedDoor(pEngine, pSurface, iMapX, iMapY);
			break;
		case 4:
			drawLockedDoor(pEngine, pSurface, iMapX, iMapY);
			break;
		case 5:
			drawTrap(pEngine, pSurface, iMapX, iMapY);
			break;
		case 6:
			drawFountain(pEngine, pSurface, iMapX, iMapY);
			break;
		case 7:
			drawBucket(pEngine, pSurface, iMapX, iMapY);
			break;
		case 8:
			drawKey(pEngine, pSurface, iMapX, iMapY);
			break;
		case 9:
			drawHP(pEngine, pSurface, iMapX, iMapY);
			break;
		case 0:
			drawMP(pEngine, pSurface, iMapX, iMapY);
			break;
		case 10:
			drawNoOpenedDoor(pEngine, pSurface, iMapX, iMapY);
			break;
		case 11:
			drawBucketBroken(pEngine, pSurface, iMapX, iMapY);
			break;
	}
}

void GameTileManager::updateMapValues()
{
	if (levelController.currentLevel == 1)
	{
		for (int i = 0; i < getMapHeight(); i++)
		{
			for (int j = 0; j < getMapWidth(); j++)
			{
				if (levelController.level1[i][j] >= 48 && levelController.level1[i][j] <= 57)
				{
					setMapValue(j, i, levelController.level1[i][j] - 48);
				}
				else if (levelController.level1[i][j] >= 97 && levelController.level1[i][j] <= 122)
				{
					setMapValue(j, i, levelController.level1[i][j] - 87);
				}
			}
		}
	}
	else if (levelController.currentLevel == 2)
	{
		for (int i = 0; i < getMapHeight(); i++)
		{
			for (int j = 0; j < getMapWidth(); j++)
			{
				if (levelController.level2[i][j] >= 48 && levelController.level2[i][j] <= 57)
				{
					setMapValue(j, i, levelController.level2[i][j] - 48);
				}
				else if (levelController.level2[i][j] >= 97 && levelController.level2[i][j] <= 122)
				{
					setMapValue(j, i, levelController.level2[i][j] - 87);
				}
			}
		}
	}
}

bool GameTileManager::is_tile_crossable(std::vector<int> uncrossable, int tileValueTopLeft, int tileValueTopRight, int tileValueBottomLeft, int tileValueBottomRight)
{
	std::vector<int>::iterator it1, it2, it3, it4;
	it1 = find(uncrossable.begin(), uncrossable.end(), tileValueTopLeft);
	it2 = find(uncrossable.begin(), uncrossable.end(), tileValueBottomRight);
	it3 = find(uncrossable.begin(), uncrossable.end(), tileValueTopRight);
	it4 = find(uncrossable.begin(), uncrossable.end(), tileValueBottomLeft);
	if (it1 != uncrossable.end() || it2 != uncrossable.end() || it3 != uncrossable.end() || it4 != uncrossable.end())
		// Yes, it's uncrossable
		// As long as there is one value is in the uncrossable array, it's uncrossable
		return false;
	else
		// No, it's not uncrossable (crossable)
		return true;
}

bool GameTileManager::isOneTileCrossable(MovingObject* pMovingObject, int mapX, int mapY)
{
	bool isCrossable = true;
	std::vector<int>::iterator it;
	int tileValue = getMapValue(mapX, mapY);
	it = find(pMovingObject->uncrossable.begin(), pMovingObject->uncrossable.end(), tileValue);
	if (it != pMovingObject->uncrossable.end())
	{
		isCrossable = false;
	}
	return isCrossable;
}

bool GameTileManager::validateTile(MovingObject* movingObject, int toward, int distance)
{
	int tileValueTopLeft = 0;
	int tileValueBottomRight = 0;
	int tileValueTopRight = 0;
	int tileValueBottomLeft = 0;
	int leftX = movingObject->getCurrentScreenX() + 5;
	int topY = movingObject->getCurrentScreenY() + 5;
	int rightX = movingObject->getCurrentScreenX() + movingObject->getDrawWidth() - 5;
	int bottomY = movingObject->getCurrentScreenY() + movingObject->getDrawHeight() - 5;
	switch (toward)
	{
	case 1:
		tileValueTopLeft = getMapValue(getMapXForScreenX(leftX), getMapYForScreenY(topY + distance));
		tileValueTopRight = getMapValue(getMapXForScreenX(rightX), getMapYForScreenY(topY + distance));
		tileValueBottomLeft = getMapValue(getMapXForScreenX(leftX), getMapYForScreenY(bottomY + distance));
		tileValueBottomRight = getMapValue(getMapXForScreenX(rightX), getMapYForScreenY(bottomY + distance));
		break;
	case 2:
		tileValueTopLeft = getMapValue(getMapXForScreenX(leftX), getMapYForScreenY(topY + distance));
		tileValueTopRight = getMapValue(getMapXForScreenX(rightX), getMapYForScreenY(topY + distance));
		tileValueBottomLeft = getMapValue(getMapXForScreenX(leftX), getMapYForScreenY(bottomY + distance));
		tileValueBottomRight = getMapValue(getMapXForScreenX(rightX), getMapYForScreenY(bottomY + distance));
		break;
	case 3:
		tileValueTopLeft = getMapValue(getMapXForScreenX(leftX + distance), getMapYForScreenY(topY));
		tileValueTopRight = getMapValue(getMapXForScreenX(rightX + distance), getMapYForScreenY(topY));
		tileValueBottomLeft = getMapValue(getMapXForScreenX(leftX + distance), getMapYForScreenY(bottomY));
		tileValueBottomRight = getMapValue(getMapXForScreenX(rightX + distance), getMapYForScreenY(bottomY));
		break;
	case 4:
		tileValueTopLeft = getMapValue(getMapXForScreenX(leftX + distance), getMapYForScreenY(topY));
		tileValueTopRight = getMapValue(getMapXForScreenX(rightX + distance), getMapYForScreenY(topY));
		tileValueBottomLeft = getMapValue(getMapXForScreenX(leftX + distance), getMapYForScreenY(bottomY));
		tileValueBottomRight = getMapValue(getMapXForScreenX(rightX + distance), getMapYForScreenY(bottomY));
		break;
	}

	if (is_tile_crossable(movingObject->uncrossable, tileValueTopLeft, tileValueTopRight, tileValueBottomLeft, tileValueBottomRight))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool GameTileManager::validateWall(MovingObject* movingObject)
{
	int X = movingObject->getXCentre();
	int Y = movingObject->getYCentre();
	int mapX = getMapXForScreenX(X);
	int mapY = getMapYForScreenY(Y);
	if (isTileWall(mapX, mapY))
	{
		return true;
	}
	return false;
}

bool GameTileManager::validateAttackTile(MovingObject* movingObject, int toward, int distance)
{
	int tileValueTopLeft = 0;
	int tileValueBottomRight = 0;
	int tileValueTopRight = 0;
	int tileValueBottomLeft = 0;
	int leftX = movingObject->getCurrentScreenX() + 5;
	int topY = movingObject->getCurrentScreenY() + 5;
	int rightX = movingObject->getCurrentScreenX() + movingObject->getDrawWidth() - 5;
	int bottomY = movingObject->getCurrentScreenY() + movingObject->getDrawHeight() - 5;
	switch (toward)
	{
	case 1:
		tileValueTopLeft = getMapValue(getMapXForScreenX(leftX), getMapYForScreenY(topY + distance));
		tileValueTopRight = getMapValue(getMapXForScreenX(rightX), getMapYForScreenY(topY + distance));
		tileValueBottomLeft = getMapValue(getMapXForScreenX(leftX), getMapYForScreenY(bottomY + distance));
		tileValueBottomRight = getMapValue(getMapXForScreenX(rightX), getMapYForScreenY(bottomY + distance));
		break;
	case 2:
		tileValueTopLeft = getMapValue(getMapXForScreenX(leftX), getMapYForScreenY(topY + distance));
		tileValueTopRight = getMapValue(getMapXForScreenX(rightX), getMapYForScreenY(topY + distance));
		tileValueBottomLeft = getMapValue(getMapXForScreenX(leftX), getMapYForScreenY(bottomY + distance));
		tileValueBottomRight = getMapValue(getMapXForScreenX(rightX), getMapYForScreenY(bottomY + distance));
		break;
	case 3:
		tileValueTopLeft = getMapValue(getMapXForScreenX(leftX + distance), getMapYForScreenY(topY));
		tileValueTopRight = getMapValue(getMapXForScreenX(rightX + distance), getMapYForScreenY(topY));
		tileValueBottomLeft = getMapValue(getMapXForScreenX(leftX + distance), getMapYForScreenY(bottomY));
		tileValueBottomRight = getMapValue(getMapXForScreenX(rightX + distance), getMapYForScreenY(bottomY));
		break;
	case 4:
		tileValueTopLeft = getMapValue(getMapXForScreenX(leftX + distance), getMapYForScreenY(topY));
		tileValueTopRight = getMapValue(getMapXForScreenX(rightX + distance), getMapYForScreenY(topY));
		tileValueBottomLeft = getMapValue(getMapXForScreenX(leftX + distance), getMapYForScreenY(bottomY));
		tileValueBottomRight = getMapValue(getMapXForScreenX(rightX + distance), getMapYForScreenY(bottomY));
		break;
	}
	
	if (is_tile_crossable(movingObject->unattackble, tileValueTopLeft, tileValueTopRight, tileValueBottomLeft, tileValueBottomRight))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int GameTileManager::validateHP(MovingObject* movingObject, BaseEngine* pEngine, DrawingSurface* pSurface)
{
	int count = 0;
	int leftX = getMapXForScreenX(movingObject->getCurrentScreenX() + 8);
	int topY = getMapYForScreenY(movingObject->getCurrentScreenY() + 8);
	int rightX = getMapXForScreenX(movingObject->getCurrentScreenX() + movingObject->getDrawWidth() - 8);
	int bottomY = getMapYForScreenY(movingObject->getCurrentScreenY() + movingObject->getDrawHeight() - 8);
	if (isTileHP(leftX, topY))
	{
		count++;
		setAndRedrawMapValueAt(leftX, topY, 2, pEngine, pSurface);
	}
	if (isTileHP(leftX, bottomY))
	{
		count++;
		setAndRedrawMapValueAt(leftX, bottomY, 2, pEngine, pSurface);
	}
	if (isTileHP(rightX, topY))
	{
		count++;
		setAndRedrawMapValueAt(rightX, topY, 2, pEngine, pSurface);
	}
	if (isTileHP(rightX, bottomY))
	{
		count++;
		setAndRedrawMapValueAt(rightX, bottomY, 2, pEngine, pSurface);
	}
	return count;
}

int GameTileManager::validateMP(MovingObject* movingObject, BaseEngine* pEngine, DrawingSurface* pSurface)
{
	int count = 0;
	int leftX = getMapXForScreenX(movingObject->getCurrentScreenX() + 8);
	int topY = getMapYForScreenY(movingObject->getCurrentScreenY() + 8);
	int rightX = getMapXForScreenX(movingObject->getCurrentScreenX() + movingObject->getDrawWidth() - 8);
	int bottomY = getMapYForScreenY(movingObject->getCurrentScreenY() + movingObject->getDrawHeight() - 8);
	if (isTileMP(leftX, topY))
	{
		count++;
		setAndRedrawMapValueAt(leftX, topY, 2, pEngine, pSurface);
	}
	if (isTileMP(leftX, bottomY))
	{
		count++;
		setAndRedrawMapValueAt(leftX, bottomY, 2, pEngine, pSurface);
	}
	if (isTileMP(rightX, topY))
	{
		count++;
		setAndRedrawMapValueAt(rightX, topY, 2, pEngine, pSurface);
	}
	if (isTileMP(rightX, bottomY))
	{
		count++;
		setAndRedrawMapValueAt(rightX, bottomY, 2, pEngine, pSurface);
	}
	return count;
}

int GameTileManager::validateKey(MovingObject* movingObject, BaseEngine* pEngine, DrawingSurface* pSurface)
{
	int count = 0;
	int leftX = getMapXForScreenX(movingObject->getCurrentScreenX() + 8);
	int topY = getMapYForScreenY(movingObject->getCurrentScreenY() + 8);
	int rightX = getMapXForScreenX(movingObject->getCurrentScreenX() + movingObject->getDrawWidth() - 8);
	int bottomY = getMapYForScreenY(movingObject->getCurrentScreenY() + movingObject->getDrawHeight() - 8);
	if (isTileKey(leftX, topY))
	{
		count++;
		setAndRedrawMapValueAt(leftX, topY, 2, pEngine, pSurface);
	}
	if (isTileKey(leftX, bottomY))
	{
		count++;
		setAndRedrawMapValueAt(leftX, bottomY, 2, pEngine, pSurface);
	}
	if (isTileKey(rightX, topY))
	{
		count++;
		setAndRedrawMapValueAt(rightX, topY, 2, pEngine, pSurface);
	}
	if (isTileKey(rightX, bottomY))
	{
		count++;
		setAndRedrawMapValueAt(rightX, bottomY, 2, pEngine, pSurface);
	}
	return count;
}

bool GameTileManager::validateTrap(MovingObject* movingObject)
{
	bool isTrap = false;
	int leftX = getMapXForScreenX(movingObject->getCurrentScreenX() + 8);
	int topY = getMapYForScreenY(movingObject->getCurrentScreenY() + 8);
	int rightX = getMapXForScreenX(movingObject->getCurrentScreenX() + movingObject->getDrawWidth() - 8);
	int bottomY = getMapYForScreenY(movingObject->getCurrentScreenY() + movingObject->getDrawHeight() - 8);
	if (isTileTrap(leftX, topY))
	{
		isTrap = true;
	}
	if (isTileTrap(leftX, bottomY))
	{
		isTrap = true;
	}
	if (isTileTrap(rightX, topY))
	{
		isTrap = true;
	}
	if (isTileTrap(rightX, bottomY))
	{
		isTrap = true;
	}
	return isTrap;
}

void GameTileManager::tryBreakBucket(MovingObject* pMovingObject, BaseEngine* pEngine, DrawingSurface* pSurface)
{
	int leftX = getMapXForScreenX(pMovingObject->getCurrentScreenX() + 8);
	int topY = getMapYForScreenY(pMovingObject->getCurrentScreenY() + 8);
	int rightX = getMapXForScreenX(pMovingObject->getCurrentScreenX() + pMovingObject->getDrawWidth() - 8);
	int bottomY = getMapYForScreenY(pMovingObject->getCurrentScreenY() + pMovingObject->getDrawHeight() - 8);
	if (isTileBucket(leftX, topY))
	{
		AudioManager::Instance()->PlaySFX("breakBucket.wav");
		setAndRedrawMapValueAt(leftX, topY, 11, pEngine, pSurface);
	}
	if (isTileBucket(leftX, bottomY))
	{
		AudioManager::Instance()->PlaySFX("breakBucket.wav");
		setAndRedrawMapValueAt(leftX, bottomY, 11, pEngine, pSurface);
	}
	if (isTileBucket(rightX, topY))
	{
		AudioManager::Instance()->PlaySFX("breakBucket.wav");
		setAndRedrawMapValueAt(rightX, topY, 11, pEngine, pSurface);
	}
	if (isTileBucket(rightX, bottomY))
	{
		AudioManager::Instance()->PlaySFX("breakBucket.wav");
		setAndRedrawMapValueAt(rightX, bottomY, 11, pEngine, pSurface);
	}
}

bool GameTileManager::isTileWall(int mapX, int mapY)
{
	bool isWall = false;
	int tileValue = getMapValue(mapX, mapY);
	if (tileValue == 1)
	{
		isWall = true;
	}
	return isWall;
}

bool GameTileManager::isTileHP(int mapX, int mapY)
{
	bool isHP = false;
	int tileValue = getMapValue(mapX, mapY);
	if (tileValue == 9)
	{
		isHP = true;
	}
	return isHP;
}

bool GameTileManager::isTileMP(int mapX, int mapY)
{
	bool isMP = false;
	int tileValue = getMapValue(mapX, mapY);
	if (tileValue == 0)
	{
		isMP = true;
	}
	return isMP;
}

bool GameTileManager::isTileKey(int mapX, int mapY)
{
	bool isKey = false;
	int tileValue = getMapValue(mapX, mapY);
	if (tileValue == 8)
	{
		isKey = true;
	}
	return isKey;
}

bool GameTileManager::isTileBucket(int mapX, int mapY)
{
	bool isKey = false;
	int tileValue = getMapValue(mapX, mapY);
	if (tileValue == 7)
	{
		isKey = true;
	}
	return isKey;
}

bool GameTileManager::isTileTrap(int mapX, int mapY)
{
	bool isKey = false;
	int tileValue = getMapValue(mapX, mapY);
	if (tileValue == 5)
	{
		isKey = true;
	}
	return isKey;
}

void GameTileManager::openLockedDoor(MovingObject* pMovingObject, BaseEngine* pEngine, DrawingSurface* pSurface)
{
	int mapX;
	int mapY;
	levelController.getLockedDoorPosition(&mapX, &mapY);
	setAndRedrawMapValueAt(mapX, mapY, 3, pEngine, pSurface);
}

bool GameTileManager::isPlayerAroundDoor(MovingObject* pMovingObject)
{
	bool isAround = false;
	
	// get the locked door position
	int mapX;
	int mapY;
	levelController.getLockedDoorPosition(&mapX, &mapY);
	int validTileMapX = mapX;
	int validTileMapY = mapY + 1;

	// Check if the player is within the specific area
	int tileLeftX = m_iBaseScreenX + validTileMapX * getTileWidth();
	int tileRightX = m_iBaseScreenX + (validTileMapX + 1) * getTileWidth();
	int tileTopY = m_iBaseScreenY + validTileMapY * getTileHeight();
	int tileBottomY = m_iBaseScreenY + (validTileMapY + 1) * getTileHeight();
	if (	pMovingObject->getXCentre() < tileRightX && pMovingObject->getXCentre() > tileLeftX
		&&	pMovingObject->getYCentre() < tileBottomY && pMovingObject->getYCentre() > tileTopY)
	{
		isAround = true;
	}
	return isAround;
}

bool GameTileManager::isPlayerAroundFountain(MovingObject* pMovingObject)
{
	bool isAround = false;
	int mapX;
	int mapY;
	levelController.getFountainPosition(&mapX, &mapY);

	int tileLeftX = m_iBaseScreenX + (mapX - 1) * getTileWidth();
	int tileRightX = m_iBaseScreenX + (mapX + 2) * getTileWidth();
	int tileTopY = m_iBaseScreenY + (mapY - 1) * getTileHeight();
	int tileBottomY = m_iBaseScreenY + (mapY + 2) * getTileHeight();
	if (pMovingObject->getXCentre() < tileRightX && pMovingObject->getXCentre() > tileLeftX
		&& pMovingObject->getYCentre() < tileBottomY && pMovingObject->getYCentre() > tileTopY)
	{
		isAround = true;
	}
	return isAround;
}

void GameTileManager::getFinalArea(int* topY, int* bottomY, int* leftX, int* rightX)
{
	int mapX;
	int mapY;
	levelController.getLockedDoorPosition(&mapX, &mapY);
	*leftX = m_iBaseScreenX + mapX * getTileWidth();
	*rightX = m_iBaseScreenX + (mapX + 1) * getTileWidth();
	*topY = m_iBaseScreenY + mapY * getTileHeight();
	*bottomY = m_iBaseScreenY + (mapY + 1) * getTileHeight();
}

bool GameTileManager::isPositionCrossable(std::vector<int> uncrossable, int XPosition, int YPosition)
{
	std::vector<int>::iterator it;
	int tileValue = getMapValue(getMapXForScreenX(XPosition), getMapYForScreenY(YPosition));
	it = find(uncrossable.begin(), uncrossable.end(), tileValue);
	if (it != uncrossable.end())
		// Yes, it's not crossable
		// As long as there is one value is in the uncrossable array, it's uncrossable
		return false;
	else
		// No, it's crossable
		return true;
}

void GameTileManager::setBornPlace(int* XPosition, int* YPosition)
{
	int mapX;
	int mapY;
	levelController.getNoOpenedDoorPosition(&mapX, &mapY);
	*XPosition = m_iBaseScreenX + mapX * getTileWidth();
	*YPosition = m_iBaseScreenY + (mapY - 1) * getTileHeight();
}


void GameTileManager::drawWall(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	wall.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth(), m_iBaseScreenY + iMapY * getTileHeight(), wall.getWidth(), wall.getHeight(), 0);
}

void GameTileManager::drawFloor(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	floor.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth(), m_iBaseScreenY + iMapY * getTileHeight(), floor.getWidth(), floor.getHeight());
}

void GameTileManager::drawUnlockedDoor(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	unlockedDoor.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth(), m_iBaseScreenY + iMapY * getTileHeight(), unlockedDoor.getWidth(), unlockedDoor.getHeight());
}

void GameTileManager::drawLockedDoor(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	lockedDoor.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth(), m_iBaseScreenY + iMapY * getTileHeight(), lockedDoor.getWidth(), lockedDoor.getHeight());
}

void GameTileManager::drawTrap(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	trap.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth(), m_iBaseScreenY + iMapY * getTileHeight(), trap.getWidth(), trap.getHeight());
}

void GameTileManager::drawFountain(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	fountain.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth(), m_iBaseScreenY + iMapY * getTileHeight(), fountain.getWidth(), fountain.getHeight());
}

void GameTileManager::drawBucket(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	bucket.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth(), m_iBaseScreenY + iMapY * getTileHeight(), bucket.getWidth(), bucket.getHeight());
}

void GameTileManager::drawKey(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	key.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth()+7, m_iBaseScreenY + iMapY * getTileHeight() + 5, key.getWidth(), key.getHeight());
}

void GameTileManager::drawHP(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	hp.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth() + 5, m_iBaseScreenY + iMapY * getTileHeight() + 3, hp.getWidth(), hp.getHeight());
}

void GameTileManager::drawMP(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	mp.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth() + 5, m_iBaseScreenY + iMapY * getTileHeight() + 3, mp.getWidth(), mp.getHeight());
}

void GameTileManager::drawNoOpenedDoor(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	noOpenedDoor.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth(), m_iBaseScreenY + iMapY * getTileHeight(), noOpenedDoor.getWidth(), noOpenedDoor.getHeight());
}

void GameTileManager::drawBucketBroken(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	bucketBroken.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth(), m_iBaseScreenY + iMapY * getTileHeight() + 12, bucketBroken.getWidth(), bucketBroken.getHeight());
}
